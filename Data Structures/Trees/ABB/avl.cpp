#include <iostream>
#include <cstdlib> 

using namespace std;
typedef int dado;

enum posicao { esq, dir };

class noh {
friend class AVL;
friend int calcAltura(noh*); 
friend int calcFatorBalanceamento(noh*);
  private:
	noh * esq;
	noh *dir;
	noh *pai;
	dado valor;
	int altura;
	 ~noh();
  public:
  int fatorBalanceamento();
	  noh(dado);
};

noh::noh(dado valor) {
	esq = NULL;
	dir = NULL;
	pai = NULL;
	this->valor = valor;
	altura = 1;
}

noh::~noh() {
	delete esq;
	delete dir;
}

int noh::fatorBalanceamento() {
	return calcAltura(esq) - calcAltura(dir);
}

int calcAltura(noh* node) {
	if(node == NULL) 
		return 0;
	return node->altura;
}

int calcFatorBalanceamento(noh* node) {
	if(node == NULL) 
		return 0;
	return node->fatorBalanceamento();
}

class AVL {
  private:
	noh * raiz;
	noh *minimoAux(noh *);
	noh *maximoAux(noh *);
	void transplanta(noh *, noh *);
	void percorreEmOrdemAux(noh *, int);
	noh* rotacaoEsquerda(noh* node);
	noh* rotacaoDireita(noh* node);
	noh* arrumaBalanceamento(noh*);
	noh* inserirAux(noh*, dado);
	noh* removerAux(noh*, dado);
	bool verificaNoh(noh*);
	bool percorreVerificandoAux(noh*);	
    public:
	  AVL();
	 ~AVL();
	void inserir(dado);
	void remover(dado);
	noh *buscar(dado);
	dado getMinimo();
	dado getMaximo();
	void percorreEmOrdem();
	bool percorreVerificando();
};

AVL::AVL() {
	raiz = NULL;
}

void AVL::inserir(dado valor) {
	raiz = inserirAux(raiz, valor); 
/*	noh *novoNoh = new noh(valor);
	posicao posInsercao;
	if (raiz == NULL) {
		raiz = novoNoh;
	}
	else {
		noh *atual = raiz;
		noh *anterior;

		while (atual != NULL) {
			anterior = atual;

			if (atual->valor > valor) {
				atual = atual->esq;
				posInsercao = esq;
			}
			else {
				atual = atual->dir;
				posInsercao = dir;
			}
		}

		novoNoh->pai = anterior;

		if (posInsercao == dir)
			anterior->dir = novoNoh;
		else
			anterior->esq = novoNoh;
	}
*/
}

noh* AVL::inserirAux(noh* node, dado valor ) {
	if (node == NULL) {		// SE CHEGOU EM UMA FOLHA NULA 
		noh* novo = new noh(valor);
		return novo; 
	}
											// SE NAO EH UMA FOLHA, CHECA SE INSERE NA ESQUERDA OU DIREITA
	if (valor < node->valor) {
		node->esq = inserirAux(node->esq, valor);
		node->esq->pai = node;
	}
	else if (valor > node->valor) {
		node->dir = inserirAux(node->dir, valor);
		node->dir->pai = node;
	}
	else {
		cerr << "Elemento repetido: " << valor << endl;
		return node;	
	}
	return arrumaBalanceamento(node); // AJUSTA A ARVORE APOS INSERCAO 
}

noh* AVL:: arrumaBalanceamento(noh* node) {		// CHECA E ARRUMA, SE NECESSARIO, O BALANCEAMENTO EM node,
																				 //FAZENDO ROTACOES E AJUSTES NECESSARIOS

	node->altura = 1+ max(calcAltura(node->esq), calcAltura(node->dir));	// ATUALIZA A ALTURA
	int balanc = node->fatorBalanceamento();
	
	if ((balanc >= -1) and (balanc <=1))			// BALANCEADO
		return node;

	if ((balanc>1) && (calcFatorBalanceamento(node->esq) >=0)) 	// DESBALANCEAMENTO ESQUERDA-ESQUERDA 
		return rotacaoDireita(node);
		
	if ((balanc > 1) && (calcFatorBalanceamento(node->esq) < 0 )) {	// DESBALANCEAMENTO ESQUERDA-DIREITA
		node->esq = rotacaoEsquerda(node->esq);
		return rotacaoDireita(node); 
	}
	
	if ((balanc < -1) && (calcFatorBalanceamento(node->dir) <= 0))	// DESBALANCEAMENTO DIREITA-DIREITA
	  return rotacaoEsquerda(node);
	  
	if ((balanc < -1) && (calcFatorBalanceamento(node->dir) > 0)) {	// DESBALANCEAMENTO DIREITA-ESQUERDA
		node->dir = rotacaoDireita(node->dir);
		return rotacaoEsquerda(node);	
	}
	cerr<<"deu bosta" << endl;
	return NULL;                                         	                               		                        	  	                            
}

noh* AVL :: rotacaoEsquerda(noh* node) {			// ROTACAO A ESQUERDA NA SUBARVORE COM RAIZ EM node E RETORNA O 																								//NOVO PAI DA SUBARVORE
	noh* nodeAux = node->dir;		//ACHA O NOH FILHO A DIREITA DE node
	node->dir = nodeAux->esq;		// ARMAZENA SUBARVORE A ESQUERDA DE nodeAux COMO FILHO A DIREITA DE node
	
	if (nodeAux->esq != NULL) {		// ATUALIZA O PAI DO NOH A ESQUERDA DE node
		nodeAux->esq->pai = node;
	}
	
	nodeAux->pai = node->pai;			// ATUALIZA O PAI DE nodeAux
	
	if (node->pai != NULL) {				// COLOCANDO nodeAux NO LUGAR DE node
		if (node == node->pai->esq)
			node->pai->esq = nodeAux;
		else
			node->pai->dir = nodeAux;
	}
	
	nodeAux->esq = node;			// FAZ node COMO FILHO DE nodeAux
	node->pai = nodeAux;
	
	node->altura = 1+max(calcAltura(node->esq), calcAltura(node->dir));			// ATUALIZA AS ALTURAS
	nodeAux->altura = 1+max(calcAltura(node->esq), calcAltura(node->dir));
	return nodeAux;
}

noh* AVL :: rotacaoDireita(noh* node) {			// ROTACAO A ESQUERDA NA SUBARVORE COM RAIZ EM node E RETORNA O 																								//NOVO PAI DA SUBARVORE
	noh* nodeAux = node->esq;		//ACHA O NOH FILHO A DIREITA DE node
	node->dir = nodeAux->dir;		// ARMAZENA SUBARVORE A ESQUERDA DE nodeAux COMO FILHO A DIREITA DE node
	
	if (nodeAux->dir != NULL) {		// ATUALIZA O PAI DO NOH A ESQUERDA DE node
		nodeAux->dir->pai = node;
	}
	
	nodeAux->pai = node->pai;			// ATUALIZA O PAI DE nodeAux
	
	if (node->pai != NULL) {				// COLOCANDO nodeAux NO LUGAR DE node
		if (node == node->pai->esq)
			node->pai->esq = nodeAux;
		else
			node->pai->dir = nodeAux;
	}
	
	nodeAux->dir = node;			// FAZ node COMO FILHO DE nodeAux
	node->pai = nodeAux;
	
	node->altura = 1+max(calcAltura(node->esq), calcAltura(node->dir));			// ATUALIZA AS ALTURAS
	nodeAux->altura = 1+max(calcAltura(node->esq), calcAltura(node->dir));
	return nodeAux;
}

noh *AVL::minimoAux(noh * raizAux) {
	while (raizAux->esq != NULL) {
		raizAux = raizAux->esq;
	}
	return raizAux;
}

dado AVL::getMinimo() {
	if (raiz == NULL) {
		cerr << "arvore vazia!" << endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		noh *minimo = minimoAux(raiz);
		return minimo->valor;
	}
}

noh *AVL::maximoAux(noh * raizAux) {
	while (raizAux->dir != NULL) {
		raizAux = raizAux->dir;
	}
	return raizAux;
}

dado AVL::getMaximo() {
	if (raiz == NULL) {
		cerr << "arvore vazia!" << endl;
		exit(EXIT_FAILURE);
	}
	else {
		noh *maximo = maximoAux(raiz);
		return maximo->valor;
	}
}

noh *AVL::buscar(dado valor) {
	noh *atual = raiz;
	while (atual != NULL) {
		if (atual->valor == valor)
			return atual;
		else if (atual->valor > valor)
			atual = atual->esq;
		else
			atual = atual->dir;
	}

	return atual;
}

void AVL::transplanta(noh * antigo, noh * novo) {
	if (raiz == antigo)
		raiz = novo;
	else if (antigo == antigo->pai->esq)
		antigo->pai->esq = novo;
	else
		antigo->pai->dir = novo;
	if (novo != NULL)
		novo->pai = antigo->pai;
}

void AVL::remover(dado valor) {
	raiz = removerAux(raiz, dado);
	/*noh *nohRemover = buscar(valor);
	if (nohRemover == NULL) {
		cerr << "dado não existe na arvore" << endl;
		exit(EXIT_FAILURE);
	}
	else {
		// noh nao tem filhos à esquerda
		if (nohRemover->esq == NULL)
			transplanta(nohRemover, nohRemover - dir);
		else if (nohRemover->dir == NULL)
			transplanta(nohRemover, nohRemover - esq);
		else {
			noh *sucessor = minimoAux(nohRemover->dir);
			if (sucessor->pai != nohRemover) {
				transplanta(sucessor, sucessor->dir);
				sucessor->dir = nohRemover->dir;
				sucessor->dir->pai = sucessor;
			}
			transplanta(nohRemover, sucessor);
			sucessor->esq = nohRemover->esq;
			sucessor->esq->pai = sucessor;
		}
		nohRemover->esq = NULL;
		nohRemover->dir = NULL;
		return nohRemover->valor;
		delete nohRemover;
	*/}


noh* AVL::removerAux(noh* node, dado valor) {		// INICIALMENTE CAMINHAMOS NA ARVORE PARA ENCONTRAR O NOH POR BUSCA RECURSIVA

		if (node == NULL)	
}


void AVL::percorreEmOrdem() {
	percorreEmOrdemAux(raiz, 0);
	cout << endl;
}

void AVL::percorreEmOrdemAux(noh * atual, int nivel) {
	if (atual != NULL) {
		percorreEmOrdemAux(atual->esq, nivel + 1);
		cout << "atual->valor: " << atual->valor << " nivel: " << nivel << "// ";
		percorreEmOrdemAux(atual->dir, nivel + 1);
	}
}

int main() {
	AVL *tree = new AVL;
	tree->inserir(3);
	tree->inserir(7);
	tree->inserir(1);
	tree->inserir(5);
	tree->inserir(88);
	tree->inserir(89);
	tree->inserir(90);
	tree->inserir(91);
	tree->inserir(92);
	tree->percorreEmOrdem();
	tree->remover(3);
	tree->percorreEmOrdem();
}
