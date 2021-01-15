#include "pila.hpp"
#include<stdio.h>

Pila* crear_pila() {
	Pila* pila = new Pila(); 
	pila->cima = NULL;
	pila->size = 0;
	return pila;
}

void destuir_pila(Pila* pila) {
	while (pila->cima != NULL)
		desapilar(pila);
	free(pila);
}

Nodo* crear_nodo(Valor valor) {
	Nodo* nodo = new Nodo();
	nodo->valor = valor; 
	nodo->siguiente = NULL;
	return nodo;
}

void destruir_nodo(Nodo* nodo) {
	nodo->siguiente = NULL;
	free(nodo);
}

void apilar(Pila* pila, Valor valor) {
	Nodo* nodo = crear_nodo(valor);
	nodo->siguiente = pila->cima;
	pila->cima = nodo;
	pila->size++;
}

void desapilar(Pila* pila) {
	if (pila->cima != NULL) {
		Nodo* nodo_eliminar = pila->cima;
		pila->cima = pila->cima->siguiente;
		pila->size--;
		destruir_nodo(nodo_eliminar);
	}
}

Valor obtener_cima(Pila* pila) {
	if (pila->cima == NULL)
		return NULL;
	else {
		return pila->cima->valor;
	}
}

void obtener_elementos(Pila* pila) {
	Nodo* puntero = pila->cima; 
	while (puntero != NULL) {
		std::cout <<" <- "<<puntero->valor; 
		puntero = puntero->siguiente; 
	}
}



int obtener_longitud(Pila* pila) {
	return pila->size;
}
