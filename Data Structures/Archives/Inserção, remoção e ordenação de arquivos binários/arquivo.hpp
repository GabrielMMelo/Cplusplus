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
									DEUSES - Egípcios & Nórdicos - "arquivo.hpp"
									Copyright 2017 by Gabriel Marques de Melo & Murilo Carmagnani Lopes
									Arquivo com declaração dos métodos e atributos da classe "arquivo"

*********************************************************************************************************************************
																														*/
#ifndef ARQUIVOS_HPP
#define ARQUIVOS_HPP 1

#include "deus.hpp"
#include "excecao.hpp"

#define NOME_ARQUIVO "deuses.txt"

using namespace std;


class deus;

typedef deus Dado;

enum acaoMenu {sair, inserir, remover, procurar, listar, apagarBD};      // Usado no menu() para facilitar a legibilidade do codigo

class arquivo {
friend class deuses;
private:
    //  **** ATRIBUTOS ****
	unsigned int tam;

    //  **** METODOS ****
	unsigned int posicaoOrdenada(string);
	bool procuraInterna(string procurado);
	void atualizarTamanho();
	void tratarString(char*, unsigned short int);	// Função retorna a string passada por parâmetro com os devidos tratamentos
	int tratarInt(char);
	void ordenar( int);
	int tamAux();
public:
    //  **** METODOS ****
	arquivo();
	void escreverArquivo();	      // Abre interface para inserção de Deuses
	void menu();				  // Abre a interface geral do programa
	void removerDeus(string);	  // Pesquisa, pelo nome, se existe algum Deus correspondente e ,em caso afirmativo, o remove (seta sua posição como disponivel para sobrescrita)
	bool procuraDeus(string);	  // Procura, pelo nome, se existe algum Deus correspondente no arquivo
	void lerArquivo();		      // Imprime todos os Deuses do arquivo
	void apagarArquivo();		  // Deleta os dados do arquivo(trunca, sem escrever nada)
};

#endif
