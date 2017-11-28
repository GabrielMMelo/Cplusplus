/*
*********************************************************************************************************************************
												_____
											   |  __ \
											   | |  | | ___ _   _ ___  ___ ___
											   | |  | |/ _ | | | / __|/ _ / __|
											   | |__| |  __| |_| \__ |  __\__ \
											   |_____/ \___|\__,_|___/\___|___/
					______      __           _                 _       _   _   __          _ _
				   |  ____|    /_/          (_)             /\| |/\   | \ | | /_/         | (_)
				   | |__   __ _ _ _ __   ___ _  ___  ___    \ ` ' /   |  \| | ___  _ __ __| |_  ___ ___  ___
				   |  __| / _` | | '_ \ / __| |/ _ \/ __|  |_     _|  | . ` |/ _ \| '__/ _` | |/ __/ _ \/ __|
				   | |___| (_| | | |_) | (__| | (_) \__ \   / , . \   | |\  | (_) | | | (_| | | (_| (_) \__ \
				   |______\__, |_| .__/ \___|_|\___/|___/   \/|_|\/   |_| \_|\___/|_|  \__,_|_|\___\___/|___/
						   __/ | |_|
						   |___|

									Trabalho de Estruturas de Dados - GCC 216
									DEUSES - Egípcios & Nórdicos - "deus.hpp"
									Copyright 2017 by Gabriel Marques de Melo & Murilo Carmagnani Lopes
									Arquivo com declaração dos métodos e atributos da classe "deuses"

*********************************************************************************************************************************
																														*/
#ifndef DEUSES_HPP
#define DEUSES_HPP 1

#include <iostream>
#include <fstream>
#include <cstring>
#include <ctype.h>
#include <cstdlib>
#include <sstream>
#include "arquivo.hpp"

#define TAM_NOME 30
#define TAM_DOM 40
#define TAM_BIO 200
#define TAM_CLASS sizeof(Dado)

using namespace std;

class arquivo;

class deus{
friend class arquivo;
private:
	//  **** ATRIBUTOS ****
	bool disponivel; 					// Define se o Deus está disponível para sobrescrita no arquivo binário
	char nome[TAM_NOME];
	char dominio [TAM_DOM];
	char serAssociado [TAM_DOM];
	char mitologia [TAM_NOME];
	char biografia [TAM_BIO];

	//  **** MÉTODOS ****
	deus(string, string, string, string, string);  // Construtor da classe para receber todos os campos
	void clear();
public:
    //  **** MÉTODOS ****
	deus();  // Construtor da classe sem nenhum parametro, apenas ocupa o espaço de memória
};

#endif
