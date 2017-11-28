#include <iostream>
#include <cstdlib> 

using namespace std;
typedef int dado;

enum posicao
{ esq, dir };

class noh
{
	friend class ABB;
  private:
	  noh * esq;
	noh *dir;
	noh *pai;
	dado valor;
	 ~noh();
  public:
	  noh(dado);
};

noh::noh(dado valor)
{
	esq = NULL;
	dir = NULL;
	pai = NULL;
	this->valor = valor;
}

noh::~noh()
{
	delete esq;
	delete dir;
}

class ABB
{
  private:
	noh * raiz;
	noh *minimoAux(noh *);
	noh *maximoAux(noh *);
	void transplanta(noh *, noh *);
	void percorreEmOrdemAux(noh *, int);
  public:
	  ABB();
	 ~ABB();
	void inserir(dado);
	dado remover(dado);
	noh *buscar(dado);
	dado getMinimo();
	dado getMaximo();
	void percorreEmOrdem();

};

ABB::ABB()
{
	raiz = NULL;
}

void ABB::inserir(dado valor)
{
	noh *novoNoh = new noh(valor);
	posicao posInsercao;
	if (raiz == NULL)
	{
		raiz = novoNoh;
	}
	else
	{
		noh *atual = raiz;
		noh *anterior;

		while (atual != NULL)
		{
			anterior = atual;

			if (atual->valor > valor)
			{
				atual = atual->esq;
				posInsercao = esq;
			}
			else
			{
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
}

noh *ABB::minimoAux(noh * raizAux)
{
	while (raizAux->esq != NULL)
	{
		raizAux = raizAux->esq;
	}
	return raizAux;
}

dado ABB::getMinimo()
{
	if (raiz == NULL)
	{
		cerr << "arvore vazia!" << endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		noh *minimo = minimoAux(raiz);
		return minimo->valor;
	}
}

noh *ABB::maximoAux(noh * raizAux)
{
	while (raizAux->dir != NULL)
	{
		raizAux = raizAux->dir;
	}
	return raizAux;
}

dado ABB::getMaximo()
{
	if (raiz == NULL)
	{
		cerr << "arvore vazia!" << endl;
		exit(EXIT_FAILURE);
	}
	else
	{
n		noh *maximo = maximoAux(raiz);
		return maximo->valor;
	}
}

noh *ABB::buscar(dado valor)
{
	noh *atual = raiz;

	while (atual != NULL)
	{

		if (atual->valor == valor)
			return atual;
		else if (atual->valor > valor)
			atual = atual->esq;
		else
			atual = atual->dir;
	}

	return atual;
}

void ABB::transplanta(noh * antigo, noh * novo)
{
	if (raiz == antigo)
		raiz = novo;
	else if (antigo == antigo->pai->esq)
		antigo->pai->esq = novo;
	else
		antigo->pai->dir = novo;
	if (novo != NULL)
	{
		novo->pai = antigo->pai;
	}
}


dado ABB::remover(dado valor)
{
	noh *nohRemover = buscar(valor);

	if (nohRemover == NULL)
	{
		cerr << "dado não existe na arvore" << endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		// noh nao tem filhos à esquerda
		if (nohRemover->esq == NULL)
			transplanta(nohRemover, nohRemover - dir);
		else if (nohRemover->dir == NULL)
			transplanta(nohRemover, nohRemover - esq);
		else
		{
			noh *sucessor = minimoAux(nohRemover->dir);

			if (sucessor->pai != nohRemover)
			{
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
	}
}


void ABB::percorreEmOrdem()
{
	percorreEmOrdemAux(raiz, 0);
	cout << endl;
}

void ABB::percorreEmOrdemAux(noh * atual, int nivel)
{
	if (atual != NULL)
	{
		percorreEmOrdemAux(atual->esq, nivel + 1);
		cout << "atual->valor: " << atual->valor << " nivel: " << nivel << "// ";
		percorreEmOrdemAux(atual->dir, nivel + 1);
	}
}

int main()
{
	ABB *tree = new ABB;
	tree->inserir(3);
	tree->inserir(7);
	tree->inserir(1);
	tree->inserir(5);
	tree->inserir(88);
	tree->percorreEmOrdem();
	tree->remover(3);
	tree->percorreEmOrdem();
}