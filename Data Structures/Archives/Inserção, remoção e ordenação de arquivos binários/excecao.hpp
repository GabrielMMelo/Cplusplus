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
									DEUSES - Egípcios & Nórdicos - "excecao.hpp"
									Copyright 2017 by Gabriel Marques de Melo & Murilo Carmagnani Lopes
									Arquivo com declaração dos métodos e atributos da classe "excecao"

*********************************************************************************************************************************
																														*/
#ifndef EXCECAO_HPP
#define EXCECAO_HPP

#include <sstream>

using namespace std;

enum tipoExcecao {digitoInvalido, dadoRepetido, arquivoProblema, excedeTamanho};  // Usado para melhorar a legibilidade do código, associando a cada numero de excecao, uma palavra.

class excecao {
public:
	excecao(tipoExcecao tipo, int linha);   //Construtor da classe
	string mensagem();

private:
	int linha;             // Linha do código onde foi chamada a excecao
	tipoExcecao tipo;     // Numero da exceção para tratamento
};

#endif
