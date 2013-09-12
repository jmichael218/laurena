///
/// \file     iarchive_json.cpp
/// \brief    Class for a JSON input archive i.e a class to serialize a class from a JSON file format.
/// \author   Frederic Manisse
/// \version  1.0
///
/// Class for a JSON input archive i.e a class to serialize a class from a JSON file format.
///

#include <laurena/json/iarchive_json.hpp>
#include <laurena/json/language_json.hpp>

using namespace laurena;
using namespace json;

iarchive_json::iarchive_json() : iarchive() , _depth(0)
{
}
iarchive_json::~iarchive_json()
{
}


void iarchive_json::readToken(token& tk, boost::dynamic_bitset<>& allowed_tokens)
{
    while (true)
    {
        int32 res = this->_tokenizer.readExpected(tk,JSON::units(),allowed_tokens);

        if (res == -1)
        {
            std::ostringstream stream;
            this->_tokenizer.prefixErrorMessage(stream);
            stream << " syntax error." ;
            stream.flush();
            std::string msg = stream.str();
            throw LAURENA_FAILED_PARSING_EXCEPTION(msg.c_str(),this->_tokenizer._ptr) ;  
        }

        tk._token_id = res;

        if ( !JSON::mask_tab_tokens().test (res))
            return;
    }
}

void iarchive_json::readExpected(token& token, word8 tokenId)
{
boost::dynamic_bitset<> allowed;

    allowed.resize(JSON::TOKEN_MAX);
    allowed |= JSON::mask_tab_tokens();
    allowed.set(tokenId);

    this->readToken(token,allowed);
}

void iarchive_json::readExpected(token& token, word8 tokenId1, word8 tokenId2)
{
boost::dynamic_bitset<> allowed;

    allowed.resize(JSON::TOKEN_MAX);
    allowed |= JSON::mask_tab_tokens();
    allowed.set(tokenId1);
	allowed.set(tokenId2);

    this->readToken(token,allowed);
}

void iarchive_json::readExpected(token& token, word8 tokenId1, word8 tokenId2, word8 tokenId3)
{
boost::dynamic_bitset<> allowed;

    allowed.resize(JSON::TOKEN_MAX);
    allowed |= JSON::mask_tab_tokens();
    allowed.set(tokenId1);
	allowed.set(tokenId2);
	allowed.set(tokenId3);

    this->readToken(token,allowed);
}

void iarchive_json::readExpected(token& token, word8 tokenId1, word8 tokenId2, word8 tokenId3, word8 tokenId4)
{
boost::dynamic_bitset<> allowed;

    allowed.resize(JSON::TOKEN_MAX);
    allowed |= JSON::mask_tab_tokens();
    allowed.set(tokenId1);
	allowed.set(tokenId2);
	allowed.set(tokenId3);
	allowed.set(tokenId4);

    this->readToken(token,allowed);
}

any& iarchive_json::parse (const std::string& name, any& destination)
{
token t;
std::string keyword;

	this->readExpected(t,JSON::TOKEN_BRACKET_OPEN);
	this->readExpected(t,JSON::TOKEN_SINGLE_STRING);
	keyword=anycast<std::string>(t);
	if (!boost::equals(name,keyword))
		throw LAURENA_FAILED_PARSING_EXCEPTION("object names doesn't match", this->_tokenizer._ptr);
	
	this->readExpected(t,JSON::TOKEN_DPOINTS);
	this->parseValue(destination);
	this->readExpected(t,JSON::TOKEN_BRACKET_CLOSE);

	return destination;
}

void iarchive_json::parseValue(any& object,const field* fdesc)
{
token t;
any a;

	if (fdesc)
	{
		const format* fieldFormat = dynamic_cast<const format*>(fdesc->annotations().get(JSON::ANNOTATION_NAME));
		if ( fieldFormat )
		{
			this->readExpected(t,JSON::TOKEN_DQUOTE);
			fieldFormat->read(this->_tokenizer,fdesc->get(object,a),true);
			this->readExpected(t,JSON::TOKEN_DQUOTE);
			fdesc->set(object,t);
			return;
		}


		const format* typeFormat = dynamic_cast<const format*>(fdesc->desc().annotations().get(JSON::ANNOTATION_NAME));
		if (typeFormat)
		{  
			this->readExpected(t,JSON::TOKEN_DQUOTE);
			typeFormat->read(this->_tokenizer,fdesc ? fdesc->get(object,a) : object,true);
			this->readExpected(t,JSON::TOKEN_DQUOTE);
			fdesc->set(object,t);
			return;
		}
	}

	this->readExpected(t,JSON::TOKEN_SINGLE_STRING, JSON::TOKEN_INTEGER, JSON::TOKEN_ARRAY_BRACKET_OPEN, JSON::TOKEN_BRACKET_OPEN);

	switch (t._token_id)
	{
		case JSON::TOKEN_SINGLE_STRING :
			fdesc->set(object,t);
			break;

		case JSON::TOKEN_INTEGER :
			fdesc->set(object,t);
			break;

		case JSON::TOKEN_BRACKET_OPEN:
			if (!fdesc)
				this->parseObject(object);
			else 
			if (fdesc->isPointer())
			{
				a = std::move(fdesc->desc().create());
				this->parseObject(a);
				fdesc->set(object,a);
			}
			else
			{
				fdesc->get(object,a);
				this->parseObject(a);
			}
			break;

		case JSON::TOKEN_ARRAY_BRACKET_OPEN:
			if (!fdesc)
				this->parseElements(object);
			else 
			if (fdesc->isPointer())
			{
				a = std::move(fdesc->desc().create());
				this->parseElements(a);
				fdesc->set(object,a);
			}
			else
			{

				fdesc->get(object,a);
				this->parseElements(a);
			}
			break;


		default:
			throw LAURENA_FAILED_PARSING_EXCEPTION("error in JSON implementation", this->_tokenizer._ptr);
			break;
	}
}

void iarchive_json::parseElements(any& object)
{
const descriptor& d = *object.desc();
token t;
const container_feature* ccf = dynamic_cast<const container_feature*>(d.feature(Feature::CONTAINER));
bool hasKey = ccf->hasKey();
const descriptor* ecd = ccf->elementDescriptor();
const descriptor* kcd = hasKey ? ccf->keyDescriptor() : NULL;
any element;
bool elems_are_pointers = ccf->areElementsPointers();
literator it = ccf->begin(object);
word32 index = 0;
any key;

	while (true)
	{
		this->readExpected(t,JSON::TOKEN_ARRAY_BRACKET_CLOSE, JSON::TOKEN_BRACKET_OPEN, JSON::TOKEN_COLON);
		if ( t._token_id == JSON::TOKEN_ARRAY_BRACKET_CLOSE)
			return ;

		if (t._token_id == JSON::TOKEN_COLON)
			this->readExpected(t,JSON::TOKEN_BRACKET_OPEN);

		element = std::move(ecd->create());
		
		this->parseObject(element);

		if (hasKey)
		{
			key = index++;
			ccf->set(object,key,element);
		}
		else
			ccf->push(object,element);
	}
}


void iarchive_json::parseObject   (any& object)
{
const descriptor& d = *object.desc();
token t;
std::string keyword;
const field* f;

	while (true)
	{
		this->readExpected(t,JSON::TOKEN_SINGLE_STRING,JSON::TOKEN_BRACKET_CLOSE);

		if (t._token_id == JSON::TOKEN_BRACKET_CLOSE)
			break;
		
		keyword = anycast<std::string>(t);
		f = d.findField(keyword);    
		if (!f)
		{
			std::ostringstream stream;
			(this->_tokenizer.prefixErrorMessage(stream)) << " Field '" << keyword << "' doesn't exist in type '" << d.name() << "'.";
			throw LAURENA_FAILED_PARSING_EXCEPTION(stream.str().c_str(),this->_tokenizer._ptr) ; 
		}

		this->readExpected(t,JSON::TOKEN_DPOINTS);

		this->parseValue(object,f);

		this->readExpected(t,JSON::TOKEN_BRACKET_CLOSE, JSON::TOKEN_COLON);

		if (t._token_id == JSON::TOKEN_BRACKET_CLOSE)
			break;
	}

}


//end of file
