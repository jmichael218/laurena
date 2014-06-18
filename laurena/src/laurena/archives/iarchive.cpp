///
/// \file     iarchive.cpp
/// \brief    Base class for an input archive i.e a class to serialize a class from a file format.
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// Base class for an input archive i.e a class to serialize a class from a file format.
///

#include <laurena/archives/iarchive.hpp>
#include <laurena/formatting/format.hpp>
#include <laurena/constants/const_strings.hpp>
#include <laurena/descriptors/field.hpp>
#include <laurena/exceptions/failed_parsing_exception.hpp>

using namespace laurena;

//! Default constructor
iarchive::iarchive () : _logger(nullptr), _source_filename ()
{ }

//! destructor
iarchive::~iarchive()
{ }

iarchive& iarchive::clear ()
{
    this->_source_filename = "";
    this->_tokenizer.str("");
    return *this;
}


void iarchive::skip_tabs()
{
    this->_tokenizer.skip(this->language().tabs_parsers());
}

token iarchive::read_token(const bitfield_t& allowed_tokens)
{
token tk;

    this->skip_tabs();
    int32 res = this->_tokenizer.read(tk, this->language().tokens_parsers(), allowed_tokens);

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
    return tk;
}

token iarchive::read_token(word8 allowed_token_id)
{
    bitfield_t b (this->language().tokens_parsers().size(), false);
    b[allowed_token_id] = true;
    return this->read_token(b);
}

token iarchive::read_token(word8 allowed_token1_id, word8 allowed_token2_id)
{
    bitfield_t b (this->language().tokens_parsers().size(), false);
    b[allowed_token1_id] = true;
    b[allowed_token2_id] = true;
    return this->read_token(b);
}


token iarchive::read_token (word8 allowed_token1_id, word8 allowed_token2_id, word8 allowed_token3_id)
{
    bitfield_t b (this->language().tokens_parsers().size(), false);
    b[allowed_token1_id] = true;
    b[allowed_token2_id] = true;
    b[allowed_token3_id] = true;
    return this->read_token(b);
}

token iarchive::read_token(word8 allowed_token1_id, word8 allowed_token2_id, word8 allowed_token3_id, word8 allowed_token4_id)
{
    bitfield_t b (this->language().tokens_parsers().size(), false);
    b[allowed_token1_id] = true;
    b[allowed_token2_id] = true;
    b[allowed_token3_id] = true;
    b[allowed_token4_id] = true;
    return this->read_token(b);
}

 bool iarchive::read_custom_field_format(const field& f, any& object)
 {

    bool isAtomic               = f.desc().has(descriptor::Flags::ATOMIC);
    const format* fieldFormat	= dynamic_cast<const format*>(f.annotations().get(this->language().format_annotations()));
    any a;

	if ( fieldFormat )
    {
        this->skip_tabs();
	    if (isAtomic)
		{
			fieldFormat->read(this->_tokenizer,a,true);
			f.set(object, a);
		}
		else
			fieldFormat->read(this->_tokenizer,f.get(object, a),true);
		return true;
	}
    else
        return false;
 }
//End of file

