#include "pila.hpp"
#include <iostream>
#include<string>
#include <string.h>
#define COL 7
#define ROW 15

std::string tabla[ROW][COL] =
{
	{"a", "b", "z", "FDC", "S", "M", "N"},
	{"", "", "desplazar 2", "", "14", "", ""},
	{"desplazar 3", "", "desplazar 7", "", "", "4", ""},
	{"desplazar 3", "", "desplazar 7", "", "", "8", ""},
	{"", "desplazar 5", "desplazar 9", "", "", "", "6"},
	{"", "desplazar 5", "desplazar 9", "", "", "", "10"},
	{"", "", "desplazar 11", "", "", "", ""},
	{"M->z", "M->z", "M->z", "", "", "", ""},
	{"desplazar 12", "", "", "", "", "", ""},
	{"", "N->z", "N->z", "", "", "", ""},
	{"", "desplazar 13", "", "", "", "", ""},
	{"", "", "", "S->zMNz", "", "", ""},
	{"M->aMa", "M->aMa", "M->aMa", "", "", "", ""},
	{"", "N->bNb", "N->bNb", "", "", "", ""},
	{"", "", "", "aceptar", "", "", ""}
};


std::string leer(std::string cadena, int* indice_entrada) {
	int indice = *indice_entrada; 
	indice++; 
	*indice_entrada = indice; 
	std::string s; 
	if (indice > cadena.length()) {
		return "FDC"; 
	}
	s.push_back(cadena[indice - 1]); 
	return s; 
}


int buscar_col(char simbolo) {
	for (int col = 0; col < COL; col++) {
		if (simbolo == tabla[0][col][0])
			return col; 
	}
}

int buscar_estado(std::string valor_tabla, std::string cadena_referencia) {
	//re 12 - 10 = 2; 
	int end_count = valor_tabla.length(); 
	int start_count = cadena_referencia.length(); 
	std::string estado_string = ""; 
	for (int i = start_count; i < end_count; i++) {
		estado_string += valor_tabla[i];
	}
	return std::atoi(estado_string.c_str());
}


int contiene(std::string valor_tabla, std::string cadena_ejemplo) {
	int coincidencias = 0; 
	if (valor_tabla.length() > cadena_ejemplo.length()) {
		for (int i = 0; i < valor_tabla.length(); i++) {
			if(valor_tabla[i] == cadena_ejemplo[i]) 
				coincidencias++; 

			if (coincidencias > 2) return 1; 
			if (i == cadena_ejemplo.length()) return -1; 
		}
	}
	return -1; 
}

std::string obtener_izq(std::string valor_tabla) {
	std::string s; 
	s.push_back(valor_tabla[0]); 
	return s; 
}

//m->zzz
void regla_lado_derecho(std::string valor_tabla, std::string cadena_ejemplo, Pila* pila) {
	std::string lado_derecho; 
	int end_count = valor_tabla.length(); 
	int start_count = cadena_ejemplo.length();
	for (int i = start_count; i < end_count; i++)
		lado_derecho += valor_tabla[i]; 

	int veces_a_retirar = lado_derecho.length(); 
	std::string cima_pila = obtener_cima(pila); 
	while (veces_a_retirar > 0) {
		char c = lado_derecho[veces_a_retirar - 1];
		if (c == cima_pila[0]) {
			veces_a_retirar--; 
			desapilar(pila); 
			cima_pila = obtener_cima(pila); 
		}
		else {
			desapilar(pila); 
			cima_pila = obtener_cima(pila);
		}
	}
}

// se fila - s col 
int main() {
	//entrada del usuario
	std::string cadena = "zazabzbz";
	int continuar = 0; 
	int indice_entrada = 0; 
	Pila* pila = new Pila(); 
	int se = 1; 
	std::string simbolo = leer(cadena, &indice_entrada);
	int col = buscar_col(simbolo[0]); 
	apilar(pila, std::to_string(se));
	obtener_elementos(pila);
	printf("\n");
	std::string valor_tabla = tabla[se][col]; 
	
	while (valor_tabla.compare("aceptar") != 0  && continuar != -1 && valor_tabla != "") {
		if (contiene(valor_tabla, "desplazar") != -1) {
			obtener_elementos(pila); 
			printf("\n"); 
			apilar(pila, simbolo);
			//std::cout << obtener_cima(pila);
			se = buscar_estado(valor_tabla, "desplazar "); 
			apilar(pila, std::to_string(se)); 
			//std::cout << obtener_cima(pila);
			simbolo = leer(cadena, &indice_entrada); //aqqui
			col = buscar_col(simbolo[0]);
			obtener_elementos(pila);
			printf("\n");
		}
		else if (contiene(valor_tabla, "->")) {
			regla_lado_derecho(valor_tabla, "M->", pila); 
			se = stoi(obtener_cima(pila));
			std::string lado_izq = obtener_izq(valor_tabla);
			col = buscar_col(lado_izq[0]); 
			apilar(pila, lado_izq);
			obtener_elementos(pila);
			printf("\n");
			//std::cout << obtener_cima(pila);
			se = stoi(tabla[se][col]); 
			apilar(pila,std::to_string(se)); 
			//std::cout << obtener_cima(pila);
			obtener_elementos(pila);
			printf("\n");
		}
		else if (valor_tabla == "") {
			continuar = -1; 
		}
		if (continuar != -1) {
			col = buscar_col(simbolo[0]);
			if (col < 0) {
				continuar = -1;
			}
			else {
				valor_tabla = tabla[se][col];
			}
		}
		
	}

	if (continuar != 1 && valor_tabla.compare("aceptar") == 0)
		std::cout << "\n¡Cadena Aceptada!\n";
	else std::cout << "\nCadena no valida\n"; 
	system("pause");
	return 0; 
}
