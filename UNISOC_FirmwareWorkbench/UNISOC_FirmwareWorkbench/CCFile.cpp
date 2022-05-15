#include "CBinary.h"


void CBinary::calculateFileSZ() {
	this->fileSize = this->f.tellg();
	this->f.seekg(0, std::ios::end);
	this->fileSize = this->f.tellg() - this->fileSize;
	this->mp(0x00);
}

std::int64_t CBinary::getFSz() {
	return this->fileSize;
}

CBinary::CBinary(std::string path, std::ios::openmode mode) {
	this->f.open(path, mode);
	this->calculateFileSZ();
}

void CBinary::w(void* buff, std::size_t buffSz) {
	this->f.write(reinterpret_cast<char*>(buff), buffSz);
}

void CBinary::r(void* buff, std::size_t buffSz) {
	this->f.read(reinterpret_cast<char*>(buff), buffSz);
}

void CBinary::mp(std::int64_t offset) {
	//A função limpa o sinalizador eofbit
	this->f.seekg(offset, std::ios::beg);
}

CBinary::~CBinary() {
	this->f.close();
}