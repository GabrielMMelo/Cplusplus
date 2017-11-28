/*						ARVORE AVL _ ESTRUTURAS DE DADOS UFLA 
  										@Gabriel Melo
  - Altura das subarvores esquerda e direita de cada no *** em no maximo uma unidade 
  
  - Fator de balanceamento: hd - he    {-1,0,1}
  
   *Se o modulo do fator de balanceamento for maior que 1, a arvore precisa ser balanceada
  
  -> Rotação Simples
  -> Rotação Dupla
  
  		MAIS CUSTOSA QUE A RUBRO NEGRA PARA MANTER O BALANCEAMENTO
  		porém é mais refinado (balanceamento puro = oapenas uma folha desbalanceada)
		
		INSERÇÃO::insercao em um noh com fator de balanceamento 0 é suave. Em 1 vai precisar de rotacao.
		
		ROTACAO SIMPLES:: LL: rotaciona a direita
						  RR: rotaciona a esquerda 
 
		ROTACAO DUPLA:: RL: primeira rotaciona a direita e dpois a esquerda  
 */ 
 
#include <iostream> 
#include <cstdlib>
#include <sstream>
using namespace std;

typedef int Dado;
enum posicao {l, r};

enum exces {ArvoreVazia, ErroNaoCatalogado};
class exc {
friend class avl;
private:
	int linha;
	exces typeexc;
public:
	string msg();
	exc (exces typeexc, int linha);
};

exc::exc(exces typeexc, int linha) {
	this->typeexc = typeexc;
	this->linha = linha;
}

string exc :: msg() {
	stringstream ss;
	ss.clear();
	ss << "Um erro foi encontrado: ";
	switch(typeexc) {
		case ArvoreVazia:
		ss << "Árvore vazia! ";
		break;
		
		case ErroNaoCatalogado:
		ss << "Erro não catalogado! ";
		break;
	}
	
	ss << "(encontrado na linha" << linha << ")" << endl;
	return ss.str();
}

class noh {
friend class avl;
private:
	noh* esq;
	noh* dir;
	noh* pai;
	Dado valor;
public:
	noh();
	noh(Dado d) {
		valor = d;
		pai = NULL;
		esq = NULL;
		dir = NULL;
	}
	~noh();
};

class avl {
private:
	noh* raiz;
	void rotacionaDir(noh*);
	void rotacionaEsq(noh*);
	int fatorBalan(noh*);
	void transplanta(noh*, noh*);

public:

	void insere(Dado);
	Dado remove();
	void percorreEmOrdem();
	void percorrePreOrdem();
	void percorrePosOrdem();
	avl(){raiz = NULL;}
	~avl();	
	
};
	
void avl::insere(Dado d) {
	noh* novoNoh = new noh(d);
	posicao posicaoIns;
	if(raiz == NULL) {
		raiz = novoNoh;
		novoNoh->pai = NULL;
	}
	else {
		noh* atual = raiz;
		noh* anterior;
		
		while(atual!=NULL) {
			anterior = atual;
			
			if(novoNoh->valor >= anterior->valor) {
				atual = atual->dir;
				posicaoIns = r;
			}
			
			else {
				atual = atual->esq;
				posicaoIns = l;
			}
		}
		novoNoh->pai = anterior;
		if(posicaoIns == l) 
			anterior->esq = novoNoh;
		else 
			anterior->dir = novoNoh;
		
	}
}

void avl :: rotacionaEsq(noh* n) {   // Filho a direita vira pai do pai e filho do pai do pai 
	if(n->pai==NULL) {				// acho que dá pra fazer sem diferenciar NULL de um outro pai qualquer
		n->pai = n->esq;
		n->esq->dir = n;
		n->esq->pai = NULL;
		raiz = n->esq;
		n->esq = NULL;
		
	}
	
	else {
		n->pai = n->esq;
		n->esq->dir = n;
		n->esq->pai = n->pai;
		n->esq = NULL;
	}
}

void avl :: rotacionaDir(noh* n) {   // Filho a esquerda vira pai do pai e filho do pai do pai 
	
	if(n->pai==NULL) {				// acho que dá pra fazer sem diferenciar NULL de um outro pai qualquer
		n->pai = n->dir;
		n->dir->esq = n;
		n->dir->pai = NULL;
		n->dir = NULL;
	}
	
	else {
		n->pai = n->dir;
		n->dir->esq = n;
		n->dir->pai = n->pai;
		n->dir = NULL;
	}
}

// no caso de rotacao de rotacao dupla, passa como parametro o noh de baixo e na rotaco simples para o noh mais de cima 

void avl :: percorreEmOrdem() {
	try{
	if(raiz==NULL)
		 exc(ArvoreVazia, __LINE__);
	 }
	 catch(exc e) {
		 cerr << e.msg() << endl;
	}
}

int avl :: fatorBalan(noh* n){
	return (n->dir->h - n->esq->h);  
}



int main() {



}
