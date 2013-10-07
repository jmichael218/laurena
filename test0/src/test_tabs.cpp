#include "test0.hpp"
#include <laurena/types/tabs.hpp>


void testTabs()
{
	laurena::tabs<> t("    ");

	std::cout << "test tabs:<"<<  ++t ;
	std::cout << ">*<" << ++t ;
	std::cout << ">*<" << ++t ;
	std::cout << ">*<" << --t ;
	std::cout << ">-<" << --t ;
	std::cout << ">|" << std::endl;
}

