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
									Arquivo com implementação dos métodos da classe "arquivo"

*********************************************************************************************************************************
																																*/
#ifndef ARQUIVO_HPP
#define ARQUIVO_HPP 1
#include "sequence.hpp"

#define TAM_CAB_GER sizeof(int)*3
#define TAM_CAB_SEQ sizeof(int)*2
#define TAM_DADOS_SEQ sizeof(Dado)*5
#define TAM_INT sizeof(int)
#define TAM_DADO sizeof(Dado)
#define NOME_ARQUIVO  "sequence.dat"

enum acaoMenu {sair, inserir, remover, procurar, listar, apagarBD};      // Usado no menu() para facilitar a legibilidade do codigo

using namespace std;

typedef int Dado;

const long tamanhoCabGeral = TAM_CAB_GER;
const long tamanhoCabSeq = TAM_CAB_SEQ;
const long tamanhoInt = TAM_INT;
const long tamanhoDado = TAM_DADO;
const long tamanhoSeq = tamanhoCabSeq + tamanhoDado*5;


class arquivo{
friend class sequence;
	private:
		int qntSeq;
		int firstSeq;
		int nextFreeSeq;
		
	public:
		void inserir(Dado d);
		void insereOrdenado(long, Dado, int);
		void apagarArquivo();
		void atualizaNextFree(int);
		void remover(Dado);
		bool busca(Dado);
		int retornaQntSeq();
		int retornaFirstSeq();
		int retornaNextFreeSeq();	
		void imprime();
		void menu();
		int tratarInt(char);
		void tratarString(char*, unsigned short int);
		arquivo();
		//long moveRead(int pos);
		//long moveReadInicioSeq(int pos);
		//long moveWrite(int pos);
};
#endif
