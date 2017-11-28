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
									DEUSES - Egípcios & Nórdicos - "arquivo.cpp"
									Copyright 2017 by Gabriel Marques de Melo & Murilo Carmagnani Lopes
									Arquivo com implementação dos métodos da classe "arquivo"

*********************************************************************************************************************************
																																*/
#include "arquivo.hpp"

using namespace std;

arquivo::arquivo() {        // Construtor vazio da classe arquivo

}

void arquivo :: apagarArquivo() {					// Função para deleção do banco de Dados
	ofstream arq(NOME_ARQUIVO, ios::trunc);		    /* Inicia o arquivo de modo truncado, ou seja, reinicia o
													   arquivo do ZERO, apagando todos os dados anteriores */
	if(arq==NULL)
		throw excecao(arquivoProblema, __LINE__);
	else {
		arq.close();
		tam = 0;									// Atualiza tamanho;
	}
}

void arquivo :: removerDeus(string procurado) {
	Dado objeto, objetoAux;							// Variável temporaria auxiliar para armazenar os dados do Deus a ser deletado
	long aux;										// armazena a quantidade de bits que representam a posição no arquivo
	char procuradoChar[TAM_NOME];
	stringstream ss;								// fluxo de string que recebe o valor procurado (como string) e o converte para char
	ss.clear();
	ss << procurado;
	ss >> procuradoChar;

	fstream arq(NOME_ARQUIVO, ios:: in | ios::out | ios:: binary);
	if(arq==NULL)
		throw excecao(arquivoProblema, __LINE__);
	arq.seekg(0, ios::beg);
	while(arq.read((char*) &objeto, sizeof(Dado))) {
		if(!strcmp(objeto.nome, procuradoChar)) {	 // recebe os dados do Deus a ser removido e altera a booleana disponivel para true
			aux = arq.tellg();						 // recebe a posição do cursor de leitura do arquivo
			objetoAux.nome[0] = *objeto.nome;
			objetoAux.dominio[0] = *objeto.dominio;
			objetoAux.serAssociado[0] = *objeto.serAssociado;
			objetoAux.mitologia[0] = *objeto.mitologia;
			objetoAux.biografia[0] = *objeto.biografia;
			objetoAux.disponivel = true;
		}
	}
	arq.close();

	fstream arq2(NOME_ARQUIVO, ios:: in | ios::out | ios:: binary);
	if(arq2==NULL)
		throw excecao(arquivoProblema, __LINE__);
	arq2.seekp(aux-TAM_CLASS, ios::beg);				/* seta o cursor de escrita no arquivo com o valor gravado na variável "aux"
														   menos o valor do tamanho da classe (para chegar exatamente no inicio do
														   registro do Deus procurado) */
	if(!arq2.write((char*) &objetoAux , sizeof(Dado))) 	// sobrescreve o objeto
		throw excecao(arquivoProblema, __LINE__);
	arq2.close();
}

int arquivo ::  tamAux() {
	Dado objeto;				// função usada internamente para controle do tamanho "real" do arquivo. (essa leitura considera
	int contador = 0;			//   também objetos com campo "disponivel" true)

	ifstream arq(NOME_ARQUIVO, ios::binary);
	if(arq==NULL)
		throw excecao(arquivoProblema, __LINE__);
	else {
		arq.seekg(0, ios::beg);
		while(arq.read((char*) &objeto, sizeof(Dado))){
			contador++;
		}
		return contador;
	}
}


void arquivo :: ordenar(int posicaoBase) {                              // Metodo que realiza os deslocamentos necessarios dos blocos de dados (cada Deus)
	Dado objeto;                                                        // de acordo com posicaoBase, que dah a posicao na qual o novo Deus deve ser inserido
	int contadorAux = 0;
	int pos;
	bool chave;
	bool chave2 = true;

	ifstream arq3(NOME_ARQUIVO, ios::binary);
	if(arq3==NULL)
		throw excecao(arquivoProblema, __LINE__);
	arq3.seekg(0, ios::beg);
	while(arq3.read((char*) &objeto, sizeof(Dado))) {                   // Verifica se a posicaoBase (onde o Deus deve ser inserido) possui campo disponivel em true
		if((contadorAux == posicaoBase) and (objeto.disponivel)){       // Caso seja, não é necessário nenhum deslocamento e, por isso, chave 2 recebe false
			chave2 = false;
		}
		contadorAux++;
	}
	arq3.close();
	if(!tam)                                                            // Verifica se o tamanho (quantidade de Deuses com campo disponivel em false no arquivo) é igual a 0
		chave=false;                                                    // Caso seja, não é necessário nenhum deslocamento e, por isso, chave recebe false
	else {
		pos=tamAux()-1;                                                 // pos recebe o valor total (considerando os que possuem disponivel em true tambem) de Deuses no arquivo - 1
		chave = true;                                                   // ou seja, a ultima posicao do arquivo
	}

	if((chave) and (chave2)) {                                          // Caso as chaves sejam true, é iniciado o loop para realizar os deslocamentos com a seguinte logica:
		while(pos >= posicaoBase) {                                     // um Um contador (variável pos) recebe o ındice da última posicao do arquivo, faz a leitura
            ifstream arq2(NOME_ARQUIVO, ios::binary);                   // do Deus escrito nesta posicao, o escreve na posic˜ao seguinte e, em seguida, o decrementa, repetindo isso
            if(arq2==NULL)                                              // ate que o valor de pos seja menor que posicaoBase e o programa saia do laco de repeticao e da funcao
				throw excecao(arquivoProblema, __LINE__);
			arq2.seekg((pos)*TAM_CLASS, ios::beg);
			if(arq2.read((char *) &objeto, sizeof(Dado))) {
				if(objeto.disponivel){
					pos--;
					arq2.close();
				}
				else {
					string nomeAux, dominioAux, serAssociadoAux, mitologiaAux, biografiaAux;

					stringstream ssNome;
					ssNome.clear();
					ssNome << objeto.nome;
					nomeAux = ssNome.str();

					stringstream ssDominio;
					ssDominio.clear();
					ssDominio << objeto.dominio;
					dominioAux = ssDominio.str();

					stringstream ssSerAssociado;
					ssSerAssociado.clear();
					ssSerAssociado << objeto.serAssociado;
					serAssociadoAux = ssSerAssociado.str();

					stringstream ssMitologia;
					ssMitologia.clear();
					ssMitologia << objeto.mitologia;
					mitologiaAux = ssMitologia.str();

					stringstream ssBiografia;
					ssBiografia.clear();
					ssBiografia << objeto.biografia;
					biografiaAux = ssBiografia.str();

					Dado aux(nomeAux, objeto.dominio, objeto.serAssociado, objeto.mitologia, objeto.biografia);

					arq2.close();
					fstream arq3(NOME_ARQUIVO, ios::in | ios::out | ios::binary);
					if(arq3==NULL)
						throw excecao(arquivoProblema, __LINE__);
					arq3.seekp(((pos+1)*TAM_CLASS), ios::beg);
					if(!arq3.write((char *) &aux, sizeof(Dado)))
						throw excecao(arquivoProblema, __LINE__);
					pos --;
					arq3.close();
				}
			}
			else
					throw excecao(arquivoProblema, __LINE__);
		}
	}
}

unsigned int arquivo :: posicaoOrdenada(string texto) {	// Função que retorna a posição em que um dado objeto deve ser inserido
	if(!tam)											// Se o arquivo estiver vazio, retornará a primeira posição (posição 0)
		return 0;
	else {
		Dado objeto;

		ifstream arq(NOME_ARQUIVO, ios::binary);		// Declara um arquivo para leitura
		if(arq==NULL)
			throw excecao(arquivoProblema, __LINE__);
		arq.seekg(0, ios::beg);							// Cabeça do cursor na posição inicial
		unsigned int i=0;
		unsigned int pos=0;
		unsigned int posicoesVoltar=0;

		while((arq.read((char *) &objeto, sizeof(Dado)))) {	        // Faz a leitura do arquivo
			if(objeto.disponivel){
				if(pos == (unsigned int) tamAux()-1)                // Se pos estiver na ultima posicao do arquivo e nesta posicao o campo disponivel for true, eh retornada essa posicao
					return pos;
				else {
					posicoesVoltar++;                               // incrementa a quantidade de Deuses a serem sobrescritos que antecedem imediatamente a posicao a ser ordenada
					pos++;
				}
			}
			else {
				i=0;
				while((texto[i] == objeto.nome[i]) and (i<sizeof(texto)) and (i<sizeof(objeto.nome))){              // Enquanto os caracteres forem iguais entre as strings, vai incrementando o contador i
						i++;
				}
				if(texto[i] > objeto.nome[i]) {							// É maior
					posicoesVoltar=0;
						if(pos == (unsigned int) tamAux()-1){			// Última posição
							arq.close();
							return pos+1;                               // retorna a proxima posicao
						}
						else 											// Incrementa posição
							pos++;

				}
				else {													// É menor
					arq.close();
					return pos-posicoesVoltar;
				}
			}
		}
		arq.close();
		return 0;
	}
}


void arquivo :: atualizarTamanho() {                            // Metodo que percorre o arquivo, incrementando uma variavel (iniciada em 0) cada vez que le
	Dado objeto;                                                // um Deus com campo disponivel false. Desta forma, atualiza no final do loop a quantidade de Deuses validos escritos no arquivo

	ifstream arq(NOME_ARQUIVO, ios::in | ios::binary);
	if(arq==NULL)
		throw excecao(arquivoProblema, __LINE__);

	arq.seekg(0, ios::beg);
	unsigned int aux = 0;
	while(arq.read((char *) &objeto, sizeof(Dado))) {
		if(!objeto.disponivel)
			aux+=1;
	}
	tam = aux;
	arq.close();
}

void arquivo :: tratarString(char* texto, unsigned short int chave) {  // Metodo que trata a entrada de strings. A chave seta se a formatacao eh para cada um dos campos de vetor de caracter de um Deus
	unsigned short int i=0;
	texto[i]=toupper(texto[i]);
	int tamString = strlen(texto);

	switch(chave) {
		case 1: 			                                                // NOME = toda palavra se inicia com letra maiuscula
			if(tamString>TAM_NOME)
				throw excecao(excedeTamanho, __LINE__);
			else {
				i=1;
				while(i<tamString) {
					 if((texto[i]==' ') and (i!=(tamString-1))) {
						i++;
						texto[i]=toupper(texto[i]);
					}
					i++;
				}
			}
		break;

		case 2:				                                // SER ASSOCIADO & DOMINIO & MITOLOGIA = Insere um ponto final ao final da string
			if(tamString>TAM_DOM)
				throw excecao(excedeTamanho, __LINE__);

			while(i<tamString) {
				if((i==(tamString-1)) and (texto[i]!='.')) {
					if(texto[i] == ' ')
						texto[i] = '.';
					else
						texto[i+1] = '.';
				}
				i++;
			}
		break;

		case 3:				                                        // BIOGRAFIA = -Insere um ponto final ao final da string
			if(tamString>TAM_BIO)                                   // - Se um ponto final é colocado sem espaço (e.g. "Joaquim tabalha no DCC.Ele ministra aulas"),
				throw excecao(excedeTamanho, __LINE__);             // é formatado inserindo um espaço (i.e. "Joaquim tabalha no DCC. Ele ministra aulas.")
				i=1;
				while(i<tamString) {
					if((texto[i]=='.') and (i!=(tamString-1))) {
						i++;
						if((texto[i]==' ') and (i!=(tamString-1))){
							i++;
							texto[i]=toupper(texto[i]);
						}
						else if((texto[i]!=' ') and (i!=(tamString-1))){
							int j = tamString-1;
							while(j>=i){
								texto[j+1]= texto[j];
								j--;
							}
							texto[i] = ' ';
							texto[i+1] = toupper(texto[i+1]);
						}
					}
					else if((i==(tamString-1)) and (texto[i]!='.')) {
						if(texto[i] == ' ')
							texto[i] = '.';
						else
							texto[i+1] = '.';
					}
					i++;
				}
		break;

	}
}

int arquivo :: tratarInt(char caracter) {			/* Função que trata o caso do input de dados inválidos para entradas de menus
													   e/ou confirmações de ações da programa*/
	if(!isdigit(caracter)) {						// Dados VÁLIDOS para entradas de menus e/ou confirmações: 1 dígito número;
		throw excecao(digitoInvalido, __LINE__);
	}
	else
		return ((int)caracter - 48); 				/* retorna o caracter convertido para int e o subtrai por 48 para obter o real
													   valor desejado (Na tabela ASCII o valor inteiro correspondente ao char '0' é 48)*/
}

void arquivo :: escreverArquivo() {
	int botao=0;  									// Botao para selecao da interface
	char aux;
	Dado objeto, objetoAux;
	objetoAux.clear();
	objeto.clear();

	do{
		cout << "Nome: " << endl;                                  // Recebe do usuario os valores dos campos de deus e os trata
		cin.getline(objetoAux.nome,TAM_NOME);
		tratarString(objetoAux.nome,1);

		if(procuraInterna((string)objetoAux.nome))                  // Pesquisa no arquivo se já existe um Deus com esse nome, caso exista uma excecao é criada
			throw excecao(dadoRepetido, __LINE__);

		else {

			cout << "Domínio: " << endl;
			cin.getline(objetoAux.dominio,TAM_DOM);
			tratarString(objetoAux.dominio,2);

			cout << "Ser associado: " << endl;
			cin.getline(objetoAux.serAssociado,TAM_DOM);
			tratarString(objetoAux.serAssociado,2);

			cout << "Mitologia: " << endl;
			cin.getline(objetoAux.mitologia,TAM_DOM);
			tratarString(objetoAux.mitologia,2);

			cout << "Biografia: " << endl;
			cin.getline(objetoAux.biografia,TAM_BIO);
			tratarString(objetoAux.biografia,3);

			objetoAux.disponivel = false;


			string auxString = objetoAux.nome;
			unsigned int pos = posicaoOrdenada(auxString);                  // Atribui a uma variavel o valor da posicao a inserir o novo Deus
			ordenar(pos);
			fstream arq2(NOME_ARQUIVO, ios_base::out| ios_base::in | ios::binary); 	/* fstream: função de entrada e saída para arquivos PARAMETROS (in :: configura o arquivo
																					   como entrada, out:: configura o arquivo como saida, ate::configura o cursor de saída
																					   para o final do arquivo, binary:: seta o arquivo como binário) */

			arq2.seekp( pos*TAM_CLASS, ios::beg);   // Seta o cursor de saída (caracteres dps da posicao,posição(ios::beg, ios::cur, ios::end))
			if(arq2.write((char* ) &objetoAux, sizeof(Dado))) {
				arq2.close();
				atualizarTamanho();
				cout << endl << "			DEUS INSERIDO COM SUCESSO! :)" << endl << endl;
				cout << "			Deseja adicionar mais algum DEUS?" << endl << endl;
				cout << "			DIGITE 1 p/ SIM e 0 p/ NÃO" << endl;
				cin >> aux;
				if((aux!='0') and (aux!='1'))
					throw excecao(digitoInvalido, __LINE__);
				tratarInt(aux);
				botao=(bool)((int)aux-48);
				cin.ignore();

			}
			else {
				throw excecao(arquivoProblema, __LINE__);
				botao = 0;
			}
		}
		objetoAux.clear();
	}while(botao);
}

bool arquivo :: procuraDeus(string procurado) {                 // Percorre o arquivo comparando se o nome passado por parametro eh o mesmo de algum Deus gravado
	Dado objeto;                                                // Caso seja, imprime os campos deste Deus e retorna true. Caso contrario retorna false

	ifstream arq(NOME_ARQUIVO, ios::binary);
	arq.seekg(0, ios::beg);
	char procuradoChar[TAM_NOME];
	stringstream ss;
	ss.clear();
	ss << procurado;
	ss >> procuradoChar;
	bool encontrou = false;

	while((arq.read((char *) &objeto, sizeof(Dado))) and (!objeto.disponivel)) {
		if(!strcmp(objeto.nome, procuradoChar)) {
			encontrou = true;
			cout << "			Nome: " << objeto.nome << endl;
			cout << "			Domínio: " << objeto.dominio << endl;
			cout << "			Ser associado: " << objeto.serAssociado << endl;
			cout << "			Mitologia: " << objeto.mitologia << endl;
			cout << "			Biografia: " << objeto.biografia << endl;
		}
	}
	if(!encontrou){
		cout << "				Sua busca não retornou nenhum resultado! :( " << endl;
		arq.close();
		return false;
	}
	else
		return true;
}

bool arquivo :: procuraInterna(string procurado) {              // Percorre o arquivo comparando se o nome passado por parametro eh o mesmo de algum Deus gravado
    Dado objeto;                                                // Caso seja, retorna true. Caso contrario retorna false

	fstream arq(NOME_ARQUIVO, ios::in | ios::binary);
	if(arq == NULL)
		throw excecao(arquivoProblema, __LINE__);

	arq.seekg(0, ios::beg);
	char procuradoChar[TAM_NOME];
	stringstream ss;				// fluxo de strings que recebe o valor procurado (como string) e o converte para char
	ss.clear();
	ss << procurado;
	ss >> procuradoChar;
	bool encontrou = false;

	while((arq.read((char *) &objeto, sizeof(Dado))) and (!encontrou)) {
		if(!strcmp(objeto.nome, procuradoChar) and (!objeto.disponivel)) 		// compara os vetores de char
			encontrou = true;
	}
	arq.close();

	if(!encontrou)
		return false;
	else
		return true;
}

void arquivo :: lerArquivo() {                          // Percorre o arquivo imprimindo os campos (exceto disponivel) todos os deuses com campo disponivel em true
	Dado objeto;

	ifstream arq(NOME_ARQUIVO, ios::binary);
	if(arq==NULL)
		throw excecao(arquivoProblema, __LINE__);

	else {
		arq.seekg(0, ios::beg);			// seta o cursor de leitura para o inicio do arquivo
		atualizarTamanho();				// atualiza o tamanho
		if(!tam)
			cout << "Não existe nenhum Deus registrado no banco de dados :(" << endl;               // Caso o tamanho seja 0
		else
			cout << "				O arquivo possui " << tam << " deuses registrados" << endl << endl;  // imprime o tamanho do arquivo

		while(arq.read((char *) &objeto, sizeof(Dado))) {					// faz a leitura e imprime os objetos armazenados no arquivo
			if(!objeto.disponivel){
				cout << "Nome: " << objeto.nome << endl;
				cout << "Domínio: " << objeto.dominio << endl;
				cout << "Ser associado: " << objeto.serAssociado << endl;
				cout << "Mitologia: " << objeto.mitologia << endl;
				cout << "Biografia: " << objeto.biografia << endl << endl;
			}
		}
		arq.close();
	}
}

void arquivo :: menu() {
	int botao;
	char aux;
	ofstream arq(NOME_ARQUIVO, ios::binary);
	arq.close();

	do{
		cout << "                                _____" << endl
		     << "                               |  __ \\" << endl
			 <<"                               | |  | | ___ _   _ ___  ___ ___" << endl
			 <<"                               | |  | |/ _ | | | / __|/ _ / __|" << endl
			 <<"                               | |__| |  __| |_| \\__ |  __\\__ \\" << endl
			 <<"                               |_____/ \\___|\\__,_|___/\\___|___/" << endl
			 <<"    ______      __           _                 _       _   _   __          _ _" << endl
			 <<"   |  ____|    /_/          (_)             /\\| |/\\   | \\ | | /_/         | (_)" << endl
			 <<"   | |__   __ _ _ _ __   ___ _  ___  ___    \\ ` ' /   |  \\| | ___  _ __ __| |_  ___ ___  ___" << endl
			 <<"   |  __| / _` | | '_ \\ / __| |/ _ \\/ __|  |_     _|  | . ` |/ _ \\| '__/ _` | |/ __/ _ \\/ __|" << endl
			 <<"   | |___| (_| | | |_) | (__| | (_) \\__ \\   / , . \\   | |\\  | (_) | | | (_| | | (_| (_) \\__ \\" << endl
			 <<"   |______\\__, |_| .__/ \\___|_|\\___/|___/   \\/|_|\\/   |_| \\_|\\___/|_|  \\__,_|_|\\___\\___/|___/" << endl
			 <<"           __/ | | |" << endl << endl;
		cout << "1 - Inserir Deuses " << endl;
		cout << "2 - Remover Deuses " << endl;
		cout << "3 - Buscar um Deus " << endl;
		cout << "4 - Exibir todos Deuses " << endl;
		cout << "5 - Apagar banco de dados " << endl;
		cout << "0 - Sair " << endl;
		cin >> aux;
		try {
			botao = tratarInt(aux);
			cin.ignore();

			switch(botao) {
				case inserir:
					escreverArquivo();
					break;

				case remover:	{
					string procurado;
					char nome[TAM_NOME];
					cout << "			Digite o NOME do Deus que deseja remover" << endl;
					getline(cin, procurado);
					stringstream sprocurado;
					sprocurado.clear();
					sprocurado.str(procurado);
					sprocurado >> nome;
					tratarString(nome,1);
					if(procuraInterna(nome)) {
						removerDeus(nome);
						cout << "			DEUS REMOVIDO COM SUCESSO! :)" << endl;
					}
					else
						cout << "			Não existe um DEUS registrado com esse nome :(" << endl
							<< "			Tente novamente com outro nome" << endl;
					break;
				}
				case procurar:{
					string procurado;
					char nome[TAM_NOME];
					cout << "			Digite o nome do DEUS que deseja procurar" << endl;
					getline(cin,procurado);
					stringstream sprocurado;
					sprocurado.clear();
					sprocurado.str(procurado);
					sprocurado >> nome;
					tratarString(nome,1);
					procuraDeus(nome);
					break;
				}

				case listar:
					lerArquivo();
					break;

				case apagarBD: {
					bool resposta;
					cout << "		Você realmente deseja apagar o banco de dados?" << endl << endl
					<< "	**** Isso pode acarretar em perda inreversível de dados! ****" << endl << endl
					<< "			DIGITE  1 p/ SIM e 0 p/ NÃO..." << endl;
					cin >> aux;
					if((aux!='0') and (aux!='1'))
						throw excecao(digitoInvalido, __LINE__);
					tratarInt(aux);
					resposta=(bool)((int)aux-48);
					if(resposta) {
						apagarArquivo();
						cout << "			ARQUIVO APAGADO COM SUCESSO! :)" << endl;
					}
				}

				case sair:
						break;

				default:
					throw excecao(digitoInvalido, __LINE__);
					break;
			}
		}

		catch(excecao e){
			cerr << e.mensagem() << endl;
		}

	}while(botao!=0);
}
