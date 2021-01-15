#ifndef PILA
#define PILA
#include<iostream>
//valor que se ingresara a la tabla
typedef std::string Valor;

typedef struct nodo {
	Valor valor;
	struct nodo* siguiente;
}Nodo;

typedef struct pila {
	Nodo* cima;
	int size;
}Pila;


Pila* crear_pila();

void destruir_pila(Pila*);

Nodo* crear_nodo(Valor);

void desapilar(Pila*);

void apilar(Pila*, Valor);

Valor obtener_cima(Pila*);

void obtener_elementos(Pila*);

int obtener_longitud(Pila* pila);
#endif /*pila.h*/ 
