#include <iostream>
#include <cstdlib>

using namespace std;

typedef int Data;

class MaxHeap {
private:
	Data* heap;
	int capacidade;
	int tamanho;
	inline int pai(int i);
	inline int esquerdo(int i);
	inline int direito(int i);
	void arruma();
	void corrigeDescendo(int i);
	void corrigeSubindo(int i);
public:
	MaxHeap(int cap);
	MaxHeap(Data vet[], int tam, int cap=0);
	~MaxHeap();
	void imprime();
	Data espiaRaiz();
	Data retiraRaiz();
	Data* heapSort(Data vet[]);
	void insere (Data d);
};

MaxHeap::MaxHeap(int cap) {
	capacidade = cap;
	heap = new Data[cap];
	tamanho = 0;
}

MaxHeap::MaxHeap (Data vet[], int tam, int cap)  {
	if (cap == 0) {
		capacidade = tam;
	}
	else {
		capacidade = cap;
	}
	heap = new Data[capacidade];
	for (int i = 0; i < tam; i++) {
		heap[i] = vet[i];
	}
	tamanho = tam;
	arruma();
}

Data* MaxHeap:: heapSort(Data vet[]) {
	MaxHeap* novoHeap = new MaxHeap(vet, 13, 0);
	Data* oi = new Data [10];
	for (int i = 0; i < 10; i++)
	{
		oi[i] = novoHeap->heap[i];
	}
	
	return oi;
}

MaxHeap::~MaxHeap() {
	delete [] heap;
}

void MaxHeap::arruma() {
	for (int i = (tamanho/2 -1); i >= 0; i--) {
		corrigeDescendo(i);
	}
}
int MaxHeap::pai(int i) {
	return (i-1)/2;
}
	
int MaxHeap::esquerdo(int i) {
	return 2*i+1;
}

int MaxHeap::direito(int i) {
	return 2*i+2;
}

void MaxHeap::corrigeDescendo(int i) {
	int esq = esquerdo(i);
	int dir = direito(i);
	int maior;
	
	if((esq < tamanho) and (heap[esq] > heap[i])) {
		maior = esq;
	}
	else {
		maior = i;
	}
	
	if((dir < tamanho) and (heap[dir] > heap[maior])) {
		maior = dir;
	}
	
	if (maior!=i) {
		swap(heap[i] , heap[maior]);
		corrigeDescendo(maior);
	}
}	

void MaxHeap :: corrigeSubindo(int i) {
	int p = pai(i);
	if(	heap[i] > heap[p]) {
		swap(heap[i], heap[p]);
		corrigeSubindo(p);
	}
}

void MaxHeap::imprime() {
	for(int i=0; i<tamanho; i++) {
		cout << heap[i] << " "; 
	}
	cout << endl;
}
Data MaxHeap::espiaRaiz() {
	return heap[0];
}

Data MaxHeap:: retiraRaiz() {
	if (tamanho == 0) {
		cerr << " ERRO AO RETIRAR, HEAP VAZIO" << endl;
		exit(EXIT_FAILURE);
	}
	Data aux = heap[0];
	swap(heap[0], heap[tamanho - 1]);
	tamanho--;
	corrigeDescendo(0);
	return aux;
}

void MaxHeap::insere(Data d) {
	if (tamanho == capacidade)  {
		cerr << " HEAP CHEIO, NAO FOI POSSIVEL INSERIR" << endl;
		exit(EXIT_FAILURE);
	}
	heap[tamanho] = d;
	corrigeSubindo(tamanho);
	tamanho++;
}

int main() {
	//int tam = 13;
	
	Data* vet = new Data [10];
	for (int i = 0; i < 10; i++) {
		vet[i] = i;
	}
	
	for (int i = 0; i < 10; i++) {
		cout << vet[i]<< " ";
	}
	
	MaxHeap* h = new MaxHeap(10);
	int* oi = h->heapSort(vet);
	for (int i = 0; i < 10; i++) {
		cout << oi[i] << " " ;
	}
	
	
	/*for(int i = 0; i < tam ; i++) {
		cout << h->retiraRaiz() << " ";
	}
	cout << endl;
	h->imprime();
	
	
	for (int i = 0; i < tam; i++) {
		h->insere(vet[i]);
	}
	h->imprime();
	*/
	delete h;
	return 0;	
}
