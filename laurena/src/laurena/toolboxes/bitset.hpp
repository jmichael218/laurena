///
/// \file     bitset.hpp
/// \brief    A toolbox of functions for boost:dynamic_bitset
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
/// A toolbox of functions for boost:dynamic_bitset
///

#ifndef LAURENA_TOOLBOX_BITSET_H
#define LAURENA_TOOLBOX_BITSET_H

/********************************************************************************/
/*                      pragma once support                                     */ 
/********************************************************************************/ 
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/********************************************************************************/ 
/*              dependencies                                                    */ 
/********************************************************************************/ 
#include <laurena/types/charset.hpp>

#include <laurena/includes/includes.hpp>
#include <laurena/includes/types.hpp>
#include <laurena/types/string_array.hpp>
#include <laurena/types/charset.hpp>

/********************************************************************************/ 
/*              opening namespace(s)                                            */ 
/********************************************************************************/ 
namespace laurena {

/********************************************************************************/ 
/*              interface                                                       */ 
/********************************************************************************/ 
class bitset {
    
    public:

    /****************************************************************************/ 
    /*      serialization of bitsets                                            */ 
    /****************************************************************************/ 
    /// \name Serialization
    ///
    /// Here are functions to serialize boost bitsets
    ///@{

    /// \brief serialize a bitset as a stringified list of flags
    ///
    /// \param bits : bitset to serialize
    /// \param flagnames : name of each flags
    /// \param separator : separator characters between each flag. 
    ///
    /// \return The serialized bitset as a string
    static std::string& serialize(const bitfield_t& bits, const string_array& flagnames, std::string& destination, const std::string& separator);

    /// \brief serialize a bitset as a stringified list of flags
    ///
    /// \param bits : bitset to serialize
    /// \param flagnames : name of each flags
    /// \param separator : separator characters between each flag. 
    ///
    /// \return The serialized bitset as a string
    static std::string& serialize(word64 bits, const string_array& bitnames, std::string& destination, const std::string& separator);

    /// \brief serialize a bitset as a stringified list of flags
    ///
    /// \param bits : a string made of 0 and 1
    /// \param flagnames : name of each flags
    /// \param separator : separator characters between each flag. 
    ///
    /// \return The serialized bitset as a string
    static std::string& serialize(const std::string& bits, const string_array& bitnames, std::string& destination, const std::string& separator);

    ///@}
    /****************************************************************************/ 
    /*      parsing of values to build bitsets                                  */ 
    /****************************************************************************/ 
    /// \name Parsing
    ///
    /// Here are functions to parse flags names list to build a boost::dynamic_bitset<>
    ///@{

    /// \brief compute a bitset from stringified list of flags
    ///
    /// \param bits : bitset to be instancied
    /// \param binary : a string made of 0 and 1   
    ///
    /// \return A reference to parameter bits
    static bitfield_t& binary(bitfield_t& bits, const std::string& binary);

    /// \brief compute a word64 as a stringified list of flags
    ///
    /// \param bitnames : array of flag names
    /// \param charset : characters allowed for flag names. Other characters are considered as tabulations
    /// \param value : a string list of flags 
    /// \param separator : a separator character
    ///
    /// \return A computed word64 value
    static word64 parse(const string_array& bitnames, const charset<>& charset, const std::string& value );

    /// \brief compute a bitset as a stringified list of flags
    ///
    /// \param bitnames : array of flag names
    /// \param charset : characters allowed for flag names. Other characters are considered as tabulations
    /// \param value : a string list of flags 
    /// \param separator : a separator character
    ///
    /// \return A computed bitset value
    static bitfield_t& parse(bitfield_t& destination, const string_array& bitnames, const charset<>& charset, const std::string& names);

    /// \brief compute a bitset from a string made of 0 and 1
    static bitfield_t& parse(bitfield_t& destination, const std::string& value);

    static std::string tos(const bitfield_t& bits);
    static word64 toWord64 (const bitfield_t& bits);
    static bitfield_t& fromWord64 (word64 value, bitfield_t& dest);

    ///@}
};

/********************************************************************************/ 
/*          bottom file block                                                   */ 
/********************************************************************************/ 

}
#endif
//end of file
