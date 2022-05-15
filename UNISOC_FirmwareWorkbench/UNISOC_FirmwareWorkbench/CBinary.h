/*
	Desenvolvido por Keowu(João Vitor)
*/
#pragma once
#include <iostream>
#include <fstream>

class CBinary
{

private:
	std::fstream f;
	std::streampos fileSize;
	void calculateFileSZ();

public:
	CBinary(std::string path, std::ios::openmode mode);
	void w(void* buff, std::size_t buffSz);
	void r(void* buff, std::size_t buffSz);
	void mp(std::int64_t offset);
	std::int64_t getFSz();
	~CBinary();

};

