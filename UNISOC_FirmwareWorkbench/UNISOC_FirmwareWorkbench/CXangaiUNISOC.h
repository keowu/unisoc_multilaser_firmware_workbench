/*
    Desenvolvido por Keowu(João Vitor)

    Agradecimentos especiais ao senhor @divinebird(Github) original unix
    Adaptado ao projeto de @Keowu(Github) arm/intel/amd
    (C) Spreadtrum Communications Shanghai Co Ltd
    (C) Multilaser Industrial S.A
*/
#pragma once
#include <iostream>
#include <Windows.h>
#include <filesystem>
#include "CBinary.h"

#ifdef __cpp_lib_filesystem
#include <filesystem>
namespace fs = std::filesystem;
#elif __cpp_lib_experimental_filesystem
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING 1;
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#else
#error "Não é possível incluir um filesystem adequado para essa versão do C++"
#endif

class CXangaiUNISOC
{

    typedef struct {
        int16_t informacoesPlaca[24];
        int32_t versaoPlaca;
        int16_t nomeProduto[256];
        int16_t nomeFirmware[256];
        int32_t quantidadeParticoes;
        int32_t inicioListParticoes;
        int32_t internalRevNumero[5];
        int16_t nomeProdutoVerificacao[50];
        int16_t qualityNumero[6];
        int16_t versaoPAC[2];
	} UNISOCHEAD;

    typedef struct {
        uint32_t tamanho;
        int16_t nomeParticao[256];
        int16_t nomeArquivo[512];
        uint32_t tamanhoParticao;
        int32_t codigoRevisao[2];
        uint32_t enderecoNoArquivoPAC;
        int32_t checkSumNumero[3];
        int32_t dataArray[];
    } UNISOCPART;


public:

    void decript(int16_t* base, char* res = 0);
    bool startUnpackingProcedure(const char* firmwarepath);

};

