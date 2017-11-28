#include <iostream>

using namespace std;

typedef int data;

class node {
private:
	node* next;
	data item;
public:
	node();
	~node();
}

node::node() {
	item = 0;
	next = NULL;
}	

class pilha {	
private:
	node* top;
	
public:
	pilha();
	~pilha();
	void empilha(data);
	data desempilha();
	void imprime();
}

pilha::pilha() {
	top = NULL;
}

void pilha::empilha(data d) {
	node* newNode = new node;
	if(top == NULL) {
		newNode.item = d;
	}
	else {
		top->next = newNode;
		top=NewNode;
	}
}

data pilha::desempilha() {
	if(top == NULL) {
		cerr << "naao foi possivel remover, pilha vazia" << endl;
		exit(EXIT_FAILURE);
	}
}

pilha::~pilha(){
	while(top!=NULL) {
		desempilha();
	}
}
