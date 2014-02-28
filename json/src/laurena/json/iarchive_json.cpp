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

/********************************************************************************/
/*      implementation of virtual functions from iarchive class                 */ 
/********************************************************************************/ 
const class language& iarchive_json::language() const
{
return JSON::language();
}

 bool iarchive_json::read_custom_field_format(const field& f, any& object)
 {
    const format* fieldFormat	= dynamic_cast<const format*>(f.annotations().get(this->language().format_annotations()));

	if ( fieldFormat )
    {
        this->read_token(JSON::TOKEN_DQUOTE);
        bool res = this->iarchive::read_custom_field_format(f, object);
        this->read_token(JSON::TOKEN_DQUOTE);
        return res;
	}
    else
        return false;
 }

bool iarchive_json::readMaybeToken (token& tk, bitfield& allowed_tokens)
{
    this->skip_tabs();
    int32 res = this->_tokenizer.read(tk,JSON::language().tokens_parsers(),allowed_tokens);
    tk._token_id = res;   

    return (res != -1);
}

bool iarchive_json::readMaybe(token& tk, word8 tokenId1, word8 tokenId2, word8 tokenId3)
{
    bitfield mask;
    mask.resize(this->language().tokens_parsers().size());
    mask.set(tokenId1);
    mask.set(tokenId2);
    mask.set(tokenId3);
    return this->readMaybeToken(tk, mask);
}


any& iarchive_json::parse (const std::string& name, any& destination)
{
token t;
std::string keyword;

	this->read_token(JSON::TOKEN_BRACKET_OPEN);
	t = std::move(this->read_token(JSON::TOKEN_SINGLE_STRING));
	keyword=anycast<std::string>(t);
	if (!boost::equals(name,keyword))
		throw LAURENA_FAILED_PARSING_EXCEPTION("object names doesn't match", this->_tokenizer._ptr);
	
	this->read_token(JSON::TOKEN_DPOINTS);
	this->parseValue(destination);
	this->read_token(JSON::TOKEN_BRACKET_CLOSE);

	return destination;
}

void iarchive_json::parseValue(any& object,const field* fdesc)
{
token t;
any a;
static const descriptor* desc_int64 = classes::byType(typeid(int64));

	if (fdesc)
	{
		bool isAtomic					= fdesc->desc().has(descriptor::Flags::ATOMIC);
		const format* fieldFormat	= dynamic_cast<const format*>(fdesc->annotations().get(JSON::ANNOTATION_NAME, ANNOTATION_FORMAT_ALL));

        if (this->read_custom_field_format(*fdesc, object))
            return;


		const format* typeFormat = dynamic_cast<const format*>(fdesc->desc().annotations().get(JSON::ANNOTATION_NAME, ANNOTATION_FORMAT_ALL));
		if (typeFormat)
		{  
			this->read_token(JSON::TOKEN_DQUOTE);
			if (isAtomic)
			{
				typeFormat->read(this->_tokenizer,a,true);
				fdesc->set(object, a);
			}
			else
				typeFormat->read(this->_tokenizer,fdesc->get(object, a),true);
			this->read_token(JSON::TOKEN_DQUOTE);
			return;
		}
	}

	t = std::move(this->read_token(JSON::TOKEN_SINGLE_STRING, JSON::TOKEN_INTEGER, JSON::TOKEN_ARRAY_BRACKET_OPEN, JSON::TOKEN_BRACKET_OPEN));

	switch (t._token_id)
	{
		case JSON::TOKEN_SINGLE_STRING :
			fdesc->set(object,t);
			break;

		case JSON::TOKEN_INTEGER :
			if (fdesc->desc().feature(Feature::ANY))
				fdesc->set(object,desc_int64->cast(t));
			else
				fdesc->set(object,t);
			break;

		case JSON::TOKEN_BRACKET_OPEN:
			if (!fdesc)
				this->parseObject(object);
			else 
			if (fdesc->is_pointer())
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
			if (fdesc->is_pointer())
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

	bool isAtomic = ecd->has(descriptor::Flags::ATOMIC);
	while (true)
	{
		bool ok = this->readMaybe(t,JSON::TOKEN_ARRAY_BRACKET_CLOSE, JSON::TOKEN_BRACKET_OPEN, JSON::TOKEN_COLON);

		if (ok)
		{
			if ( t._token_id == JSON::TOKEN_ARRAY_BRACKET_CLOSE)
				return ;

			if (t._token_id == JSON::TOKEN_COLON && !isAtomic)
				this->read_token(JSON::TOKEN_BRACKET_OPEN);
		}

		if (isAtomic)
		{
			t = std::move(this->read_token(JSON::TOKEN_SINGLE_STRING, JSON::TOKEN_INTEGER));
			element = ecd->cast(t);
		}
		else
		{
			element = std::move(ecd->create());
			this->parseObject(element);
		}

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
		t = std::move(this->read_token(JSON::TOKEN_SINGLE_STRING,JSON::TOKEN_BRACKET_CLOSE));

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

		this->read_token(JSON::TOKEN_DPOINTS);

		this->parseValue(object,f);

		t = std::move(this->read_token(JSON::TOKEN_BRACKET_CLOSE, JSON::TOKEN_COLON));

		if (t._token_id == JSON::TOKEN_BRACKET_CLOSE)
			break;
	}

}


//end of file
