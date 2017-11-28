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
									DEUSES - Egípcios & Nórdicos - "excecao.cpp"
									Copyright 2017 by Gabriel Marques de Melo & Murilo Carmagnani Lopes
									Arquivo com implementação dos métodos da classe "excecao"

*********************************************************************************************************************************
																														*/
#include "excecao.hpp"

using namespace std;

excecao::excecao(tipoExcecao tipo, int linha) { //Construtor da classe excecao
	this->tipo = tipo;
	this->linha = linha;
}

string excecao::mensagem() {                    // Metodo que retorna, para cada numero de excecao, uma mensagem diferente que sera, fora do metodo, impressa ao usuario
	stringstream ss;
	ss.clear();
	ss << "Um erro foi encontrado: ";
	switch (tipo) {
	case digitoInvalido:
		ss << "Dígito de entrada inválido! (Encontrado ";
		break;

	case dadoRepetido:
		ss << "Dado já existente! (Encontrado ";
		break;

	case arquivoProblema:
		ss << "Não foi possível abrir/ler/escrever no arquivo! (Encontrado ";
		break;

	case excedeTamanho:
		ss << "A string excede o tamanho suportado! (Encontrado ";
		break;
	}
	ss  << "na linha " << linha << ").";
	return ss.str();
}
