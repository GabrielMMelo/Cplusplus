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
									DEUSES - Egípcios & Nórdicos - "main.cpp"
									Copyright 2017 by Gabriel Marques de Melo & Murilo Carmagnani Lopes

*********************************************************************************************************************************
																																*/
#include "sequence.hpp"
#include "arquivo.hpp"
int main() {
	arquivo* Arquivo = new arquivo;
	//Arquivo->menu();

	try{
	Arquivo->inserir(5);
	Arquivo->inserir(4);
	Arquivo->inserir(3);
	Arquivo->inserir(2);
	Arquivo->inserir(1);
	Arquivo->inserir(7);
	Arquivo->inserir(8);
	Arquivo->inserir(6);
	Arquivo->inserir(9);
	Arquivo->inserir(10);
	Arquivo->inserir(11);
	Arquivo->inserir(12);
	Arquivo->inserir(16);
	Arquivo->inserir(14);
	Arquivo->inserir(15);
	Arquivo->inserir(17);
	
	
	}
	catch(excecao e){
			cerr << e.mensagem() << endl;
		}
		
	/*if(Arquivo->busca(15))
		cout << "achou" << endl;
	else
		cout << "nao achou" << endl;*/
	Arquivo->imprime();
	//Arquivo->remover(1);
	//Arquivo->remover(2);
	//Arquivo->remover(3);
	Arquivo->imprime();
	delete Arquivo;
}

// procurar antes de inserir 
// fazer remover 
