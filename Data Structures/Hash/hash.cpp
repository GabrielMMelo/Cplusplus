#include <iostream>
#include <ctype.h>

using namespace std;

const int UMPRIMO = 19;

int funcaoHash(string s, int M) {
	long h = 0;
	for (unsigned i = 0; i < s.length(); i++) {
		h = (UMPRIMO * h + s[i]) %M;
	} 
	return h;
}

class noh {
friend class tabelaHash;
private:
	string chave;
	string valor;
	noh* proximo = NULL;
public:
	noh() {
		chave = "";
		valor = "";
	}
};

class tabelaHash {
private:
	noh** elementos;		// Ponteiro de noh que aponta pra outro noh que aponta para o proximo noh
	int capacidade;
public:
	tabelaHash(int cap) {
		elementos = new noh*[cap];		// vetor de ponteiros de nós
		capacidade = cap;
		
		for(int i = 0; i < cap; i++) {		// limpa os valores
			elementos[i] = NULL;
		}
	}
	
	~tabelaHash() {
		for(int i = 0; i< capacidade; i++) {
			noh* atual = elementos[i];
			while(atual != NULL) { 	// percorre a lista removendo todos os nós
				noh* aux = atual;
				atual = atual->proximo;
				delete aux;
			}
		}
		delete[] elementos;			// deleta vetor de ponteiros para ponteiros
	}

	void insere(string c, string v) {
		int h;
		h = funcaoHash(c, capacidade);
		
		if(recupera(c) == "NAO ENCONTRADO!") {
				if (elementos[h] == NULL) {
					elementos[h] = new noh;
					elementos[h]->chave = c;
					elementos[h]->valor = v;
				}
				else {
					cout << "colidiu: " << c << endl;
				noh* atual = elementos[h];
				
				while (atual->proximo != NULL) {	// achando local para insercao
					atual = atual->proximo;
				}
				
				noh* novo = new noh;
				novo->chave = c;
				novo->valor = v;
				atual->proximo = novo;
			}
		}
		else {
			cout << "ITEM JA ESTAH NA TABELA!" << endl;
		}
	}
	
	string recupera(string c) { 	//recupera uim valor associado a uma dada chave
		int h;
		h = funcaoHash(c, capacidade);
		
		if((elementos[h] != NULL) and (elementos[h]->chave == c)){
			return elementos[h]->valor;
		}
		else{
			noh* atual = elementos[h];
			
			while((atual != NULL) and (atual->chave != c)) {
				atual = atual->proximo;
			}
			
			if((atual != NULL) and (atual->chave == c)) {
				return atual->valor;
			}
			else {
					return "NAO ENCONTRADO!";
			}
		}
	}
	
	void altera(string c, string v) { 		// altera o valor associado a uma chave
		int h;								// não trata colisão, nem chave não encontrada
		h = funcaoHash(c, capacidade);
		
		if((elementos[h] != NULL) and (elementos[h]->chave == c)) {
			elementos[h]->valor = v;
		}
		else {
			noh* atual = elementos[h];
			
			while ((atual != NULL) and (atual->chave !=c)) {
				atual = atual->proximo;
			}
			
			if((atual != NULL) and (atual->chave == c)) {
				atual->valor =v;
			}
			else {
				cerr << "ERRO NA ALTERACAO!" << endl;
			}
		}
	}
	
	void remove(string c) { 		// retira um valor associado a uma chave
		int h = funcaoHash(c, capacidade); 
		
		if ((elementos[h] != NULL) and (elementos[h]->chave ==c)) {	// removendo da cabeça da lista
			noh* aux = elementos[h];
			elementos[h] = elementos[h]->proximo;
			delete aux;
		}
		else {
			noh* atual = elementos[h];
			noh* anterior;
			
			while ((atual != NULL) and (atual->chave != c)) {
				anterior = atual;
				atual = atual->proximo;
			}
			
			if ((atual != NULL) and (atual->chave == c)) {
				anterior->proximo = atual->proximo;
				delete atual;
			}
			else {
				cerr << "ERRO NA REMOCAO!" << endl;
			}
		}
	}
	
	void percorre() {		// percorrendo a tabela hash (para depuração)
		noh* atual;
		for (int i = 0; i < capacidade; i++) {
			cout << i << ":";
			atual = elementos[i];
			while (atual != NULL) {
				cout << "[" << atual->chave << "/" 
				<< atual->valor << "]->";
				atual = atual->proximo;
			}
			cout << "NULL "; 
		}
	}
};

int converter(char c) {
	if(islower(c))
		c=toupper(c);
	int dado = -65 + (int)c ;
	return dado;
}

int main() {
	/*tabelaHash th(10);
	
	th.insere("Ola", "Ola a todos");
	th.insere("Olk", "Vai ter colisao");
	th.insere("Ols", "Vai ter colisao");
	th.insere("Ole", "Vai ter colisao");
	th.insere("Olg", "Vai ter colisao");
	th.insere("Olh", "Vai ter colisao");
	th.insere("Rola", "Rola a todos");
	
	th.percorre();
	cout << endl;
	cout << th.recupera("ola") << endl;
	cout << th.recupera("Rola") << endl;
	cout << th.recupera("olk") << endl;
	
	th.altera("aranha", "homem que arranha");
	cout << th.recupera("aranha") << endl;
	
	th.remove("olk");
	cout << th.recupera("olk") << endl;
	
	cout << endl;
	th.percorre();
	cout << endl;
	
	*/
	char a;
	for (int i = 0; i < 13; i++)
	{
		cin >> a;
		cout << (converter(a)%5) << endl;
	}
	return 0;
}
