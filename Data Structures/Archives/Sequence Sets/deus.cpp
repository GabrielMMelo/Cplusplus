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
									DEUSES - Egípcios & Nórdicos - "deus.cpp"
									Copyright 2017 by Gabriel Marques de Melo & Murilo Carmagnani Lopes
									Arquivo com implementação dos métodos da classe "deuses"

*********************************************************************************************************************************
																														*/
#include "deus.hpp"
#include "arquivo.hpp"

using namespace std;

deus::deus(string nome, string dominio, string serAssociado, string mitologia, string biografia){	/* Construtor que passa os valores através da copia de string
                                                                                                        para as variáveis privadas do objeto */
	strncpy(this->nome, nome.c_str(), sizeof(this->nome));
	strncpy(this->dominio, dominio.c_str(), sizeof(this->dominio));
	strncpy(this->serAssociado, serAssociado.c_str(), sizeof(this->serAssociado));
	strncpy(this->mitologia, mitologia.c_str(), sizeof(this->mitologia));
	strncpy(this->biografia, biografia.c_str(), sizeof(this->biografia));
	this->disponivel = false;
}

deus :: deus() {            // Construtor que apenas ocupa o espaço sem passar nenhum valor
	this->disponivel = false;
}

void deus::clear(){             // Sobreescreve os vetores de caracters de um objeto Deus, preenchendo com 0's
	char *begin = this->nome;
	char *end = begin + sizeof(this->nome);
	std::fill(begin, end, 0);

	begin = this->dominio;
	end = begin + sizeof(this->dominio);
	std::fill(begin, end, 0);

	begin = this->serAssociado;
	end = begin + sizeof(this->serAssociado);
	std::fill(begin, end, 0);

	begin = this->mitologia;
	end = begin + sizeof(this->mitologia);
	std::fill(begin, end, 0);

	begin = this->biografia;
	end = begin + sizeof(this->biografia);
	std::fill(begin, end, 0);
}
