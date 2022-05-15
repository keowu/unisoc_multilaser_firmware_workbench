#include "CXangaiUNISOC.h"

void CXangaiUNISOC::decript(int16_t* base, char* res) {
	if (!*base) return;
	int i = 0;
	do {
		if (i > 256)
			break;
		*res = *base & 0xFF;
		res++;
		base++;
	} while (i++, base > 0);
	*res = 0;
}


bool CXangaiUNISOC::startUnpackingProcedure(const char* firmwarepath) {

	/*
		Classe CBinary
	*/
	auto* cfw = new CBinary(firmwarepath, std::ios::in | std::ios::binary);

	// Obtendo informações do firmware e validando
	if (cfw->getFSz() < sizeof(UNISOCHEAD)) return false;

	/*
		Obtendo informações sobre o projeto do desenvolvedor interno do firmware da engenharia da unissoc
	*/
	UNISOCHEAD socHeader{};
	cfw->r(&socHeader, sizeof(UNISOCHEAD));
	if (!socHeader.informacoesPlaca) return false;

	auto* fwNameBuff = reinterpret_cast<char*>(malloc(256));
	this->decript(socHeader.nomeFirmware, fwNameBuff);
	std::cout << "Nome do firmware: " << fwNameBuff << std::endl;

	/*
		Obtendo as partições do firmware da unissoc
	*/
	auto* auxParticionBuff = reinterpret_cast<char*>(malloc(256));
	uint32_t c = socHeader.inicioListParticoes;
	auto** particoesHeader = reinterpret_cast<UNISOCPART**>(malloc(sizeof(UNISOCPART**) * socHeader.quantidadeParticoes));
	for (auto i = 0; i < socHeader.quantidadeParticoes; i++) {
		cfw->mp(c);
		uint32_t size = 0;
		cfw->r(&size, sizeof(uint32_t));
		*(particoesHeader + i) = reinterpret_cast<UNISOCPART*>(malloc(size));
		cfw->mp(c);
		c += size;
		cfw->r(*(particoesHeader + i), size);
		decript((*(particoesHeader + i))->nomeParticao, fwNameBuff);
		decript((*(particoesHeader + i))->nomeArquivo, auxParticionBuff);
		std::cout << "Nome da particao: " << fwNameBuff << " Nome do arquivo: " << auxParticionBuff << std::endl;
	}

	/*
		Desencriptando e fazendo unpack dos arquivos presentes nas partições do firmware
	*/
	for (int i = 0; i < socHeader.quantidadeParticoes; i++) {

		if (particoesHeader[i]->tamanhoParticao == 0) {
			[&contextoParticao = *(particoesHeader + i)] () {
				if (IsBadReadPtr(contextoParticao, NULL)) {
					free(contextoParticao);
				}
			}; continue;
		}
		
		cfw->mp(particoesHeader[i]->enderecoNoArquivoPAC);
		this->decript(particoesHeader[i]->nomeArquivo, auxParticionBuff);
		auto* outFl = new CBinary(std::string(fs::current_path().u8string()).append("\\muhahaha\\").append(auxParticionBuff), std::ios::out | std::ios::binary);
		while (particoesHeader[i]->tamanhoParticao > 0) {

			auto bufferSize = (particoesHeader[i]->tamanhoParticao > 256) ? 256 : particoesHeader[i]->tamanhoParticao;
			particoesHeader[i]->tamanhoParticao -= bufferSize;
			cfw->r(auxParticionBuff, bufferSize);
			outFl->w(auxParticionBuff, bufferSize);
		}

		outFl->~CBinary();
	}

	cfw->~CBinary();
}