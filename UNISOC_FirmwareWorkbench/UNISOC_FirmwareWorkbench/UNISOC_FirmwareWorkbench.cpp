/*
	Desenvolvido por Keowu(João Vitor)
*/
#include <iostream>
#include "CXangaiUNISOC.h"


int main(int argc, char* argv[], char* envp[])
{
    std::cout << "Hello World!\n";
    
    auto* xangaiFunFW = new CXangaiUNISOC();
    xangaiFunFW->startUnpackingProcedure(std::string(argv[1]).c_str());
}