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

*********************************************************************************************************************************
																																*/
#include "arquivo.hpp"

void arquivo::insereOrdenado(long posicao, Dado d, int qntD) {
	Dado auxDado;
	int i = 1;
	bool chave = true;
	fstream arq3(NOME_ARQUIVO, ios::in | ios::out | ios::binary );
	//arq3.seekg(posicao+tamanhoDado*(qntD-i), ios::beg);
	//arq3.read((char*) &auxDado, tamanhoDado);
	while(chave) {
		//i++
		arq3.seekg(posicao+tamanhoDado*(qntD-i), ios::beg);
		arq3.seekp(posicao+tamanhoDado*(qntD-i), ios::beg);
		arq3.read((char*) &auxDado, tamanhoDado);
		//cout << "VALOR DE I: " << i << endl;
		//cout << "VALOR DE qntD: " << qntD << endl;
		if(auxDado>d){
			arq3.write((char*) &auxDado, tamanhoDado);
			//cout << "AuxDado: " << auxDado << " >" << " D: " << d << endl;
			if(qntD == i) {
				arq3.seekp(-2*tamanhoDado, ios::cur);
				//long oioi = arq3.tellp();
				/*arq3.seekg(oioi , ios::beg);
				int dadoloko;
				arq3.read((char*) &dadoloko, tamanhoInt);
				cout << "dadoloko: " << dadoloko << endl;*/
				//cout << "d: " << d << endl;
				arq3.write((char*) &d, tamanhoDado);//) cout << "gravou o dois " << endl;
				chave = false;
			}
			else {
				arq3.seekp(-tamanhoDado, ios::cur);
			}
		}
		else {
			//cout << "AuxDado: " << auxDado << " <" << " D: " << d << endl;
		 arq3.write((char*) &d, tamanhoDado);
		 chave = false;
		 }
		i++;
	}
}

void arquivo :: remover(Dado buscado){
	if(!busca(buscado))
		cerr<< "Não possui este dado!" << endl;
	else {
	sequence* seq = new sequence;
	Dado aux;
	int posAchou=-1;
	long posicaoSequence, percurso;
	int indiceSequence;
	fstream arq(NOME_ARQUIVO, ios::in | ios:: out | ios::binary);
	//if(arq) cout << "arquivo existe" << endl;
	arq.seekg(tamanhoCabGeral, ios::beg);
	if(arq.read((char*) &seq->proxSeq, tamanhoInt)) 
	if(arq.read((char*) &seq->qntDados, tamanhoInt)) 
	if(arq.read((char*) &aux, tamanhoDado)) 
		arq.seekg( -(tamanhoDado + tamanhoCabSeq), ios::cur );
	while(aux < buscado and seq->proxSeq != -1 ){
		posicaoSequence = arq.tellg();
		indiceSequence = ( (posicaoSequence - tamanhoCabGeral) / (tamanhoSeq) );
		percurso = (seq->proxSeq - indiceSequence) * (tamanhoSeq); // Retirei abs, para caso seja negativo, ele volte na posição ex: Da 5 pra 3
		arq.seekg(percurso, ios::cur);
		arq.read((char*) &seq->proxSeq, tamanhoInt);
		arq.read((char*) &seq->qntDados, tamanhoInt);
		arq.read((char*) &aux, tamanhoDado);
		arq.seekg( -(tamanhoDado + tamanhoCabSeq), ios::cur );
	}
		if(aux == buscado){								// Se o procurado é o primeiro do sequence
			posicaoSequence = arq.tellg();
			for (int i = 0; i < seq->qntDados-1; i++) {
				arq.seekp(posicaoSequence+tamanhoCabSeq+tamanhoDado+tamanhoDado*i, ios::beg);
				arq.read((char*) &aux, tamanhoDado);
				arq.seekp(-tamanhoDado*2, ios::cur);
				arq.write((char*) &aux, tamanhoDado);
			}
			
			arq.seekp(posicaoSequence, ios::beg);
			arq.seekp(tamanhoInt, ios::cur);
			seq->qntDados--;
			arq.write((char*) &seq->qntDados, tamanhoInt);
			if(!seq->qntDados) {
				arq.seekp(-2*tamanhoInt, ios::cur);
				int posSeq = arq.tellg();
				posSeq = ((posSeq - tamanhoCabGeral) / tamanhoSeq);
		//		cout << "posSeq: " << posSeq << endl;
				if(posSeq == firstSeq) {
				int proximoFirst;
				arq.read((char*) &proximoFirst, tamanhoInt);
				firstSeq = proximoFirst;}
				atualizaNextFree(posSeq);
			}
		}			
		else{											// Se não é o primeiro Dado do Sequence
			if(aux < buscado) {
				arq.read((char*) &seq->proxSeq, tamanhoInt);
				arq.read((char*) &seq->qntDados, tamanhoInt);
			//	cout << "qntDados" << seq->qntDados << endl;
				for (int i = 0; i < seq->qntDados; i++) {
					arq.read((char*) &aux, tamanhoDado);
			//		cout << "i: " << i << endl;
			//		cout << "Aux: " << aux << endl;
			//		cout << "Buscado: " << buscado << endl;
					if(aux == buscado)
						posAchou = i;
				}
				arq.seekp(-(posAchou+1)*tamanhoDado - tamanhoCabSeq, ios::cur);
				posicaoSequence = arq.tellg();
		//		cout << "posicaoSequence: " << (posicaoSequence-tamanhoCabGeral)/tamanhoSeq<< endl;
				if(posAchou == seq->qntDados-1) {		// Se é o último Dado válido do sequence
					arq.seekp(tamanhoInt, ios::cur);
					seq->qntDados--;
					arq.write((char*) &seq->qntDados, tamanhoInt);
				}
				else {									// Se não é o primeiro, nem o ultimo dado do sequence ARRUMAR
		//			cout << "CATORZE BOLLADO! " << endl;
		//			cout << "POS ACHOU: " << posAchou << endl;
		//			cout << "qntDados: " << seq->qntDados << endl;
					for (int i = posAchou; i < seq->qntDados-1; i++) {
		//				cout << "I: " << i << endl;
						//arq.seekg(posicaoSequence+tamanhoCabSeq+tamanhoDado*(i+1), ios::beg);
	//					arq.seekg(tamanhoInt*i+ tamanhoInt, ios::cur);
	//					cout << "tellg(1): " << arq.tellg() << endl; 
						if(arq.read((char*) &aux, tamanhoInt));// cout << "leu aux!!!" << endl;
	//					else cout << "nao leu aux!!" << endl;
	//					cout << "AUX: " << aux << endl;
						//arq.seekg(-tamanhoInt*i, ios::cur);
						arq.seekg(-tamanhoDado*2, ios::cur);
	//					cout << "tellg(2): " << arq.tellg() << endl; 
						if(arq.write((char*) &aux, tamanhoDado));// cout << " Gravou aux!!" << endl;
//						else cout << "nao gravou aux!! " << endl;
						arq.seekg(-tamanhoDado*(1+i), ios::cur);
	//					cout << "tellg(3): " << arq.tellg() << endl; 
					}
					arq.seekp(posicaoSequence, ios::beg);
					arq.seekp(-tamanhoInt, ios::cur);
					seq->qntDados--;
	//				cout << "qntDados : " << seq->qntDados<<endl;
					if(arq.write((char*) &seq->qntDados, tamanhoInt));// cout << "gravou qntDados!!!" << endl;
	//				else cout << "Não gravou qntDados!" << endl;
				}
			}
			else{			
				arq.seekg( -percurso, ios::cur);
				arq.read((char*) &seq->proxSeq, tamanhoInt);
				arq.read((char*) &seq->qntDados, tamanhoInt);
		//		cout << "FORA DO WHILE" << endl;
		//		cout << "qntDados" << seq->qntDados << endl;
				for (int i = 0; i < seq->qntDados; i++) {
					arq.read((char*) &aux, tamanhoDado);
	//				cout << "i: " << i << endl;
	//				cout << "Aux: " << aux << endl;
	//				cout << "Buscado: " << buscado << endl;
					if(aux == buscado)
						posAchou = i;
				}
				arq.seekp(-(posAchou+1)*tamanhoDado - tamanhoCabSeq, ios::cur);
				posicaoSequence = arq.tellg();
				if(posAchou == seq->qntDados-1){	// Se for o ultimo Dado do sequence 
					arq.seekp(tamanhoInt, ios::cur);
					seq->qntDados--;
					arq.write((char*) &seq->qntDados, tamanhoInt);
				}
				else {						
		//			cout << "POS ACHOU VOLTANDO " << posAchou << endl;					// Se o dado não é o primeiro ou o ultimo do sequence
					for (int i = posAchou-1; i < seq->qntDados-2; i++) {	
						arq.seekp(posicaoSequence+tamanhoCabSeq+tamanhoDado+tamanhoDado*i, ios::beg);
						if(arq.read((char*) &aux, tamanhoDado));// cout << "leu aux Voltando" << endl;
			//			cout << "aux: "<< aux << endl;
						arq.seekp(-tamanhoDado*2, ios::cur);
						if(arq.write((char*) &aux, tamanhoDado));//cout << " gravou voltando" << endl;
					}	
					arq.seekp(posicaoSequence, ios::beg);
					//arq.seekp(tamanhoInt, ios::cur);
					//arq.read((char*) &aux, tamanhoDado);
					//cout << "leitura auxiliar: " << aux << endl;
					seq->qntDados--;
		//			cout << "qntDados voltando: " << seq->qntDados << endl;
					if(arq.write((char*) &seq->qntDados, tamanhoInt));// cout << "gravou qntDados voltando" << endl;
				}
			}
		}
	}
}
bool arquivo :: busca(Dado buscado) {
	sequence* seq = new sequence;
	Dado aux;
	bool achou = false;
	long posicaoSequence, percurso;
	int indiceSequence;
	if(!qntSeq)									// confere se existem sequences válidos
		return false;
	ifstream arq(NOME_ARQUIVO, ios::binary);
	if(arq);// cout << "arquivo existe" << endl;
	arq.seekg(tamanhoCabGeral, ios::beg);
	if(arq.read((char*) &seq->proxSeq, tamanhoInt));// cout << "Leu" << endl;
	if(arq.read((char*) &seq->qntDados, tamanhoInt));// cout << "Leu" << endl;
	if(arq.read((char*) &aux, tamanhoDado));// cout << "Leu" << endl;
//	cout << "ProxSeq: " << seq->proxSeq << endl;
//		cout << "QntDados: " << seq->qntDados << endl;
//		cout << "Aux: " << aux << endl;
		arq.seekg( -(tamanhoDado + tamanhoCabSeq), ios::cur );
	while(aux < buscado and seq->proxSeq != -1 ){
		posicaoSequence = arq.tellg();
		indiceSequence = ( (posicaoSequence - tamanhoCabGeral) / (tamanhoSeq) );
		percurso = (seq->proxSeq - indiceSequence) * (tamanhoSeq); // Retirei abs, para caso seja negativo, ele volte na posição ex: Da 5 pra 3
		arq.seekg(percurso, ios::cur);
		arq.read((char*) &seq->proxSeq, tamanhoInt);
		arq.read((char*) &seq->qntDados, tamanhoInt);
		arq.read((char*) &aux, tamanhoDado);
		arq.seekg( -(tamanhoDado + tamanhoCabSeq), ios::cur );
	
//		cout << "ProxSeq: " << seq->proxSeq << endl;
//		cout << "QntDados: " << seq->qntDados << endl;
//		cout << "Aux: " << aux << endl;
	}
	if(aux == buscado)
		return true;
	else {
		if(aux < buscado) {
			arq.read((char*) &seq->proxSeq, tamanhoInt);
			arq.read((char*) &seq->qntDados, tamanhoInt);
			for (int i = 0; i < seq->qntDados; i++) {
				arq.read((char*) &aux, tamanhoDado);
//				cout << "i: " << i << endl;
//				cout << "Aux: " << aux << endl;
//				cout << "Buscado: " << buscado << endl;
				if(aux == buscado)
					achou = true;
			}
		}
		else{			
			arq.seekg( -percurso, ios::cur);
			arq.read((char*) &seq->proxSeq, tamanhoInt);
			arq.read((char*) &seq->qntDados, tamanhoInt);
	//		cout << "FORA DO WHILE" << endl;
	//		cout << "qntDados" << seq->qntDados << endl;
			for (int i = 0; i < seq->qntDados; i++)
			{
				arq.read((char*) &aux, tamanhoDado);
	//			cout << "i: " << i << endl;
	//			cout << "Aux: " << aux << endl;
	//			cout << "Buscado: " << buscado << endl;
				if(aux == buscado)
					achou = true;
			}
		}
	}
	return achou;
}

void arquivo :: apagarArquivo() {					// Função para deleção do banco de Dados
	ofstream arq(NOME_ARQUIVO, ios::trunc);		    /* Inicia o arquivo de modo truncado, ou seja, reinicia o
													   arquivo do ZERO, apagando todos os dados anteriores */
	if(arq==NULL)
		throw excecao(arquivoProblema, __LINE__);
	else {
		arq.close();
		qntSeq = 0;
	firstSeq = -1;
	nextFreeSeq = 0;									// Atualiza tamanho;
	}
}

void arquivo:: imprime() {
	Dado dadoAux;
	int qntAux, proxAux, indiceSequence;
	int j;
	long posicaoSequence, percurso;
	ifstream arq4(NOME_ARQUIVO, ios::binary);
	int contador = retornaQntSeq();
	//cout << " contador = " << contador << endl;
	arq4.seekg(tamanhoCabGeral+(tamanhoSeq*firstSeq), ios::beg);
	while(contador > 0) {
		
		arq4.read((char*) &proxAux, tamanhoInt);
		arq4.read((char*) &qntAux, tamanhoInt);
		if(!qntAux){
			arq4.seekg(-tamanhoCabSeq, ios::cur);
			posicaoSequence = arq4.tellg();
			indiceSequence = ( (posicaoSequence - tamanhoCabGeral) / (tamanhoSeq) );
			percurso = (proxAux - indiceSequence) * (tamanhoSeq); 
			arq4.seekg(percurso, ios::cur);
			contador--;
		}
		else{
		cout << "SEQUENCE: " <<qntSeq - contador << endl;
		if((proxAux == -1) or (proxAux == 1))
		cout <<"Proximo Sequence: " << proxAux<< endl;
		else
		cout <<"Proximo Sequence: " << proxAux - 1<< endl;
		cout <<"Quantidade de Dados: " << qntAux << endl;
		j = qntAux;
		while(j>0) {
			arq4.read((char*) &dadoAux, tamanhoDado);
			cout << dadoAux << endl;
			j--;
		}
		arq4.seekg(-tamanhoDado*qntAux-tamanhoCabSeq, ios::cur);
		posicaoSequence = arq4.tellg();
		indiceSequence = ( (posicaoSequence - tamanhoCabGeral) / (tamanhoSeq) );
		percurso = (proxAux - indiceSequence) * (tamanhoSeq); 
		arq4.seekg(percurso, ios::cur);
		contador--;
		}
	}
}
		 
	

int arquivo::retornaQntSeq() {
	int aux, zero=0, menosUm=-1;
	fstream arq2(NOME_ARQUIVO, ios::in | ios::out | ios::binary);
	if(!arq2){
		cout << "nao abriu em retornaQntSeq" << endl;
		fstream arq2(NOME_ARQUIVO, ios::in | ios::out | ios::binary | ios::trunc);
		if(arq2) cout << "ABRIU TRUNCADO" << endl;
		arq2.seekp(0, ios::beg);
		 
		if(arq2.write((char*) &zero, tamanhoInt)) cout << "gravou no retornaQntSeq" << endl;
		else cout << "nao gravou no retornaQntSeq" << endl;
		 
		if(arq2.write((char*) &menosUm, tamanhoInt)) cout << "gravou no retornaQntSeq" << endl;
		if(arq2.write((char*) &zero, tamanhoInt)) cout << "gravou no retornaQntSeq" << endl;
		arq2.close();
		return 0;
		
	}
	else {
		cout << "arquivo aberto" << endl;
		arq2.seekp(0, ios::beg);
		arq2.read ((char*) &aux, tamanhoInt);
		arq2.close();			
		return aux;
	}
}

int arquivo::retornaFirstSeq() {
	int aux;
	ifstream arq2(NOME_ARQUIVO, ios::binary);
	arq2.seekg(tamanhoInt, ios::beg);
	arq2.read ((char*) &aux, tamanhoInt);
	arq2.close();
	return aux;
}

int arquivo::retornaNextFreeSeq() {
    int aux;
	ifstream arq2(NOME_ARQUIVO, ios::binary);
	arq2.seekg(tamanhoInt*2, ios::beg);
	arq2.read ((char*) &aux, tamanhoInt);
	arq2.close();
	return aux;
}

void arquivo :: atualizaNextFree(int numSeq) {			// ARRUMAR IMPRESSAO QUANDO ESTA VAZIO O SEQUENCE ( NAO IMPRIMIR VAZIO )  /// ARRUMAR O FIRSTSEQ ((comparação em remover que verifica se o sequence a ficar vazio(remover o ultimo Dado) é o firstSeq
	int aux, proxDoNulo;
	fstream arqAux(NOME_ARQUIVO, ios::in | ios::out | ios::binary);
	
	arqAux.seekp((numSeq*tamanhoSeq)+tamanhoCabGeral, ios::beg);
	arqAux.read((char*) &proxDoNulo, tamanhoInt);
	
	arqAux.seekp(tamanhoCabGeral+(firstSeq*tamanhoInt), ios::beg);
	arqAux.read((char*) &aux, tamanhoInt);
	while(aux != numSeq-1) {
		arqAux.seekp(tamanhoSeq, ios::cur);
		arqAux.read((char*) &aux, tamanhoInt);
	}
	arqAux.seekp(-tamanhoInt, ios::beg);
	arqAux.write((char*) &proxDoNulo, tamanhoInt);
	/*arqAux.seekp((retornaNextFreeSeq*tamanhoSeq)+tamanhoCabGeral, ios::beg);
	arqAux.read((char*) &aux, tamanhoInt);*/
	arqAux.seekp((numSeq*tamanhoSeq)+tamanhoCabGeral, ios::beg);
	int nextF = retornaNextFreeSeq();
	arqAux.write((char*) &nextF, tamanhoInt);
	nextFreeSeq = numSeq;

}

arquivo::arquivo () {
	qntSeq = retornaQntSeq();
	firstSeq = retornaFirstSeq();
	nextFreeSeq = retornaNextFreeSeq();
}

/* arq2.seekp( pos*TAM_CLASS, ios::beg);   // Seta o cursor de saída (caracteres dps da posicao,posição(ios::beg, ios::cur, ios::end))
			if(arq2.write((char* ) &objetoAux, sizeof(Dado)))

*/
void arquivo::inserir(Dado d) {
	if(busca(d))
		throw excecao(dadoRepetido, __LINE__);
	sequence* seq = new sequence;
	int aux; // Util
	long auxMove; //Util
	long posicaoSequence; // Util
	int indiceSequence; // Util
	int percurso; // Util
	Dado dadoAux; // Util
	Dado auxNovo1; // Util
	Dado auxNovo2; // Util

	fstream arq(NOME_ARQUIVO, ios::out| ios::in | ios::binary);
	
	/*if(arq) cout << "arquivo existe" << endl;
	
	cout <<"qntSeq: "<< qntSeq << endl;
	cout << "firstSeq: " << firstSeq << endl;
	cout << "nextFreeSeq: " << nextFreeSeq << endl;*/
	//else fstream arq(NOME_ARQUIVO, ios::out| ios::in | ios::binary | ios::trunc);
	//arq.seekg(0, ios::beg);
	//cout << "tamanhoInt: " << tamanhoInt << endl;
	if (arq.read ((char*) &qntSeq, tamanhoInt)) {
		
		//arq.seekg( -tamanhoInt, ios::cur);
		if (qntSeq > 0) {
		//	cout << "qntSeq eh maior que 0" << endl;
			//Se TRUE, ir para a posição $firstSeq, e compara se @valor.nome > Dado.nome na primeira posicao			
			arq.seekg(tamanhoCabGeral + (tamanhoSeq * (firstSeq)) , ios::beg);
			posicaoSequence = arq.tellg();
			arq.read((char*) &seq->proxSeq, tamanhoInt);//) cout << "leu " << endl;
			//cout << "seq->proxSeq" << seq->proxSeq << endl;
			arq.read((char*) &seq->qntDados, tamanhoInt);//) cout << "leu " << endl;
			//cout << "seq->qntDados" << seq->qntDados << endl;
			arq.read((char*) &dadoAux, tamanhoDado);//) cout << "leu " << endl;
			//cout << "dado " << dadoAux << endl;
			arq.seekg(posicaoSequence, ios::beg);
			
			//Se TRUE,Atualiza as variáveis do sequence com os valores do cabeçalho e confere se @proxSeq != -1
			//Feito antes do IF
			//Retirei o If, tudo feito só com while	
			
			while (seq->proxSeq != -1 and d >= dadoAux) {
			//	cout << "entrou while (seq->proxSeq != -1 and d > dadoAux)" << endl;
				//Se TRUE, cria uma variavel 	@posicaoSequence = tellg()-> @indiceSequence = long indiceSequence((posicaoSequence-(5*sizeof(int)+sizeof(Dado)))/(tamanhoCabSeq + tamanhoSeq)) e usa-la para a nova variável @percurso (long percurso = abs(proxSeq - indiceSequence)*(tamanhoSeq + tamanhoCabSeq)) que recebera o valor da quantidade que ira andar para o primeiro Dado do proximo sequence. Pula para o proximo sequence, no primeiro Dado e  confere se $valor.nome > $Dado.nome na posicao atual
				posicaoSequence = arq.tellg();
				indiceSequence = ( (posicaoSequence - tamanhoCabGeral) / (tamanhoSeq) );
				percurso = (seq->proxSeq - indiceSequence) * (tamanhoSeq); // Retirei abs, para caso seja negativo, ele volte na posição ex: Da 5 pra 3
				arq.seekg(percurso, ios::cur);
				arq.read((char*) &seq->proxSeq, tamanhoInt);
				arq.read((char*) &seq->qntDados, tamanhoInt);
				arq.read((char*) &dadoAux, tamanhoDado);
				arq.seekg( -(tamanhoDado + tamanhoCabSeq), ios::cur );
			}	 
			//Se FALSE, usa -$percurso (menos $percurso) para voltar para o primeiro $Dado do sequence anterior. Confere se $qntDados == 5
			    
			if (qntSeq > 1 and d < dadoAux) {
				//cout << "entrou if (qntSeq > 1 and d < dadoAux)" << endl;
			arq.seekg( -percurso, ios::cur);
			arq.read((char*) &seq->proxSeq, tamanhoInt);
			arq.read((char*) &seq->qntDados, tamanhoInt);
			arq.seekg( -(tamanhoInt * 2), ios::cur);
			}				
			
			if (seq->qntDados == 5) {
				//cout << " entrou if (seq->qntDados == 5) " << endl;
				//Se TRUE, $percurso (long percurso = abs($NextFreeSeq - $indiceSequence)*(tamanhoSeq + tamanhoCabSeq)-2*sizeof(int)) 
				//salva o 4º e 5º Dado do Sequence em duas variaveis auxiliares (Dado aux1, Dado aux2), 
				//volta para o cabeçalho grava $proxSeq em uma variável $auxProxSeq, atualiza $proxSeq com o 
				//valor de @nextFreeSeq, atualiza o tamanho com 3 e pula até o proximo sequence vazio(usando percurso), 
				//escreve seu cabeçaho com os valores (proxSeq e 2, nesta ordem), escreve aux1 na primeira posição do Dado 
				//do sequence atual, aux2 na segunda posição do sequence atual, volta para a primeira posicao e compara se  
				//$valor.nome > $Dado.nome
				posicaoSequence = arq.tellg();		// INICIO DO SEQUENCE
				if(seq->proxSeq == -1) {
					indiceSequence = (posicaoSequence - tamanhoCabGeral ) / tamanhoSeq ; // CALCULA O INDICE RELATIVO DO SEQUENCE 
					//cout << "indice do sequence: " << indiceSequence << endl; 
					percurso = (nextFreeSeq - indiceSequence) * tamanhoSeq;				// CALCULA O PERCURSO ( EM BITS ) DO 
					int menosUm=-1, zero=0;
					arq.seekp(percurso, ios::cur);
					arq.write((char*) &menosUm, tamanhoInt);
					arq.write((char*) &zero, tamanhoInt);
					arq.seekp(-percurso-2*tamanhoInt, ios::cur);
					qntSeq++;
					arq.seekp(0, ios::beg);
					arq.write((char*) &qntSeq, tamanhoInt);
					//cout << "qntSeq: " << qntSeq << endl;
					arq.seekg(posicaoSequence, ios::beg);
				}
				indiceSequence = (posicaoSequence - tamanhoCabGeral ) / tamanhoSeq ; // CALCULA O INDICE RELATIVO DO SEQUENCE 
				//cout << "indice do sequence: " << indiceSequence << endl; 
				percurso = (nextFreeSeq - indiceSequence) * tamanhoSeq;				// CALCULA O PERCURSO ( EM BITS ) DO 
				//cout << "percurso= " << percurso / tamanhoSeq << endl;
				arq.seekg(tamanhoCabSeq+(tamanhoDado *3), ios::cur);				// VAI PARA O QUARTO DADO DO SEQUENCE 
				arq.read((char*) &auxNovo1, tamanhoDado);							// LÊ O 4º E O GRAVA EM UMA VARIAVEL AUX1
				//cout << "auxNovo1: " << auxNovo1 << endl;							
				arq.read((char*) &auxNovo2, tamanhoDado);							// LÊ O 5º E O GRAVA EM UMA VARIAVEL AUX2
				//cout << "auxNovo2: " << auxNovo2 << endl;
				arq.seekg(-tamanhoDado*5 - tamanhoInt*2, ios::cur);					// VOLTA PARA O INICIO DO SEQUENCE
                int auxProxSeq = seq->proxSeq;									// (OK!)   SALVA O VALOR DA PRIMEIRA POSICAO DO SEQUENCE 
				seq->proxSeq = nextFreeSeq;								// OK	ATUALIZA O VALOR DA PRIMEIRA POSICAO DO SEQUENCE
				seq->qntDados = 3;												// ATUALIZA O CAMPO DO CABEÇALHO DO SEQUENCE REFERENTE A QUANTIDADE DE DADOS
		        auxMove = arq.tellg();											// ARMAZENA A POSICAO ( INICIO DO SEQUENCE)
		        //cout << "(auxMove-tamanhoCabGeral) / tamanhoSeq"  << (auxMove-tamanhoCabGeral) / tamanhoSeq << endl;
		        arq.seekp(auxMove, ios::beg);                                  // ANDA COM A CABEÇA DE ESCRITA PARA O INICIO DO SEQUENCE 
		        int aux2 = seq->proxSeq;										
		        int aux3;
		        //cout << " aux2 = " << aux2 << endl;
		        arq.write((char*) &aux2, tamanhoInt);							// ESCREVE O INDICE PROXIMO SEQUENCE NO CABEÇALHO
		        arq.seekg(-tamanhoInt, ios::cur);
		        arq.read((char*) &aux3, tamanhoInt);
		        //cout << " newProxSeq = " << aux3 << endl;
		        aux2 = seq->qntDados;
                arq.write((char*) &aux2,tamanhoInt); 							// ESCREVE A QUANTIDADE DE DADOS NO CABECALHO
                arq.seekg(-tamanhoInt, ios::cur);
                arq.read((char*) &aux3, tamanhoInt);
		        //cout << " newQntDados = " << aux3 << endl;
                int numerodoProx, numeroDados;
                arq.seekg(auxMove, ios::beg);
                arq.read((char*) &numerodoProx, tamanhoInt);
                //cout << "numero do prox: " << numerodoProx << endl;
                arq.read((char*) &numeroDados, tamanhoInt);
                //cout << "numeroDados: " << numeroDados << endl;
                arq.seekg(-tamanhoInt * 2,ios::cur);		// VOLTA PARA INICIO DO SEQUENCE 
				arq.seekp(percurso, ios::cur);
				arq.read((char*) &aux, tamanhoInt);
				auxMove = arq.tellg();						// segunda posicao do cabeçalho do novo sequence 
				//cout << "AUX= " << aux  << endl;
				if(aux != -1){ // Precisa colocar tbm o valor que aparece caso crie um novo sequence !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					nextFreeSeq = aux;
					arq.seekp(2*tamanhoInt, ios::beg);
					arq.write((char*) &nextFreeSeq, tamanhoInt);
					arq.seekg(auxMove, ios::beg);
				}
				else{
					nextFreeSeq = qntSeq+1;
					arq.seekp(2*tamanhoInt, ios::beg);
					arq.write((char*) &nextFreeSeq, tamanhoInt);
					arq.seekg(auxMove, ios::beg);
					
				}
				int dois = 2;
				arq.seekg(-tamanhoInt, ios::cur);
				arq.write((char*) &auxProxSeq, tamanhoInt);
				arq.write((char*) &dois, tamanhoInt);
				arq.write((char*) &auxNovo1, tamanhoDado);
				arq.write((char*) &auxNovo2, tamanhoDado);
                arq.seekp(-tamanhoDado*2, ios::cur);	//2º cab seq
                //arq.seekg(tamanhoCabSeq, ios::cur);
				arq.read((char*) &dadoAux, tamanhoDado);				
				//cout << "DADO AUX(PRIMEIRO DO NOVO SEQUENCE): " << dadoAux << endl;
						
				if (d > dadoAux ) {
					//cout << "D = " << d <<" >" << " dadoAux= " << dadoAux << endl;
				    arq.seekg(-tamanhoDado-tamanhoInt, ios::cur);
				    seq->qntDados = 3;
				    int aux2 = seq->qntDados;
				    arq.write((char*) &aux2, tamanhoInt);
				    auxMove=arq.tellg();
				    insereOrdenado(auxMove, d, seq->qntDados-1);
				}
					
				else {
				    arq.seekg(-percurso-tamanhoDado-tamanhoInt, ios::cur);						// vai ter que tratar esses sinais 
				    arq.seekp(-percurso, ios::cur);
				    seq->qntDados = 4;				 
				    int aux2 = seq->qntDados;
				    arq.write((char*) &aux2, tamanhoInt);
				    insereOrdenado(arq.tellp(), d, seq->qntDados);
			    }
		    }			

			else {
				//cout << " entrou else do  if (seq->qntDados == 5)" << endl;
				//Se FALSE, insere ordenado e atualiza o tamanho;
				auxMove = arq.tellg();
				arq.seekp(auxMove + tamanhoInt, ios::beg);
				seq->qntDados++;
				//cout << " quantidade de dados = " << seq->qntDados << endl;
				int aux2 = (seq->qntDados);
				arq.write((char*) &aux2, tamanhoInt);
				insereOrdenado(arq.tellg(), d, seq->qntDados-1);
				//arq.seekp(seq->qntDados * tamanhoDado, ios::cur);
				//arq.write((char*) &d, tamanhoDado);
				// ******** PARTE DA FUNÇÃO DE ORDENAÇÂO DO SEQUENCE ***********	                    
			}
		}	
				
//Se FALSE, incrementa $numSeq, $posSeq, $numReg. Escreve o cabeçalho do primeiro sequence na posição atual(Cabeçalho Sequence -> $proxSeq = -1, $qntDados = 1. Escreve o @valor.  
		else {
			int menosUm =-1, um=1;
			//cout << "qntSeq eh igual a 0" << endl;
			arq.seekp(tamanhoCabGeral + (nextFreeSeq * tamanhoSeq), ios::beg);
			arq.write((char*) &menosUm, tamanhoInt);
			arq.write((char*) &um, tamanhoInt);
			arq.write((char* ) &d, tamanhoDado);
			qntSeq++;
			firstSeq++;
			nextFreeSeq++;
			arq.seekp(0, ios::beg);
			arq.write((char*) &qntSeq, tamanhoInt);
			arq.write((char*) &firstSeq, tamanhoInt);
			arq.write((char*) &nextFreeSeq, tamanhoInt);
		}
	}	
	else { //cout << "abertura 1 falhou";
		cout<< "Você deseja truncar o arquivo para corrigir este erro? y/n (todo conteudo será apagado)" << endl;
		char resp;
		cin >> resp;
		if(resp=='y') {
			 fstream arq(NOME_ARQUIVO, ios::in | ios::out | ios::binary | ios::trunc);
			// if(arq) cout << "ABRIU TRUNCADO" << endl;
			 arq.seekp(0, ios::beg);
			 int zero = 0;
			 int menosUm = -1;
			 
			 arq.write((char*) &zero, tamanhoInt);
			 
			 arq.write((char*) &menosUm, tamanhoInt);
			 arq.write((char*) &zero, tamanhoInt);
			 inserir(d);
		 }
	 }
		delete seq;
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
				case 1: {
					Dado valor;
					cout << "inserir!" << endl;
					cin>>valor;
					inserir(valor);
					break;
				}
				case 2:	{
					string procurado;
					char nome[TAM_NOME];
					cout << "			Digite o NOME do Deus que deseja remover" << endl;
					getline(cin, procurado);
					stringstream sprocurado;
					sprocurado.clear();
					sprocurado.str(procurado);
					sprocurado >> nome;
					tratarString(nome,1);
					//if(procuraInterna(nome)) {
					//	removerDeus(nome);
					//	cout << "			DEUS REMOVIDO COM SUCESSO! :)" << endl;
					//}
					//else
					//	cout << "			Não existe um DEUS registrado com esse nome :(" << endl
					//		<< "			Tente novamente com outro nome" << endl;
					break;
				}
				case 3:{
					string procurado;
					char nome[TAM_NOME];
					cout << "			Digite o nome do DEUS que deseja procurar" << endl;
					getline(cin,procurado);
					stringstream sprocurado;
					sprocurado.clear();
					sprocurado.str(procurado);
					sprocurado >> nome;
					tratarString(nome,1);
					//procuraDeus(nome);
					break;
				}

				case 4:
					imprime();
					break;

				case 5: {
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

				case 0:
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
