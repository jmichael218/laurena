///
/// \file     variable_descriptor.cpp
/// \brief    descriptors for classes variable and variable_list
/// \author   Frederic Manisse
/// \version  1.0
/// \licence  LGPL. See http://www.gnu.org/copyleft/lesser.html
///
///  descriptors for classes variable and variable_list
///

#include <laurena/descriptors/variable_descriptor.hpp>

using namespace laurena;

/********************************************************************************/ 
/*                                                                              */ 
/*         code for standard_class_descriptor                                   */ 
/*                                                                              */ 
/********************************************************************************/ 

variable_descriptor::variable_descriptor () : standard_class_descriptor<variable>("variable",2,nullptr)
{
    this->init_field(variable,"name",_name);
    this->init_field(variable,"value",_value);
}

/********************************************************************************/ 
/*                                                                              */ 
/*         code for td<variable>                                                */ 
/*                                                                              */ 
/********************************************************************************/ 

const descriptor* td<variable>::desc() 
{
        static const variable_descriptor* res = nullptr;
        if (res == NULL)
        {
            res = new variable_descriptor();
            classes::add(res);
        }

        return res;
}

/********************************************************************************/ 
/*                                                                              */ 
/*         code for variable_list_descriptor                                    */ 
/*                                                                              */ 
/********************************************************************************/ 
variable_list_descriptor::variable_list_descriptor() : list_descriptor<variable_list,variable>("variableList")
{ }

/********************************************************************************/ 
/*                                                                              */ 
/*         code for td<variable_list>                                           */ 
/*                                                                              */ 
/********************************************************************************/ 


const descriptor* td<variable_list>::desc()
{
    static const variable_list_descriptor* res = NULL;
    if (res == NULL)
    {
        res = new variable_list_descriptor();
        classes::add(res);
    }

    return res;
}
//End of file
