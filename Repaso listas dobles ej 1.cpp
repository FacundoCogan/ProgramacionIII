/*
    ejercicio 1 practica de listas dobles
*/

#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <string.h>

using namespace std;
 
typedef struct Empleados
{
	int legajo;
	char nombre[20];
}Empleados;

typedef struct Nodo * PuntNodo ;

typedef struct Nodo
{
	Empleados datos ;
	PuntNodo sig ;
	PuntNodo ant ;
}Nodo;

// Prototipos
void actualizarAnt(PuntNodo , PuntNodo &) ;
void mostrarListaAnt(PuntNodo) ;

int menu(void);

int main(void)
{
	PuntNodo listaSig = NULL ; // puntero al primer nodo de la lista
    PuntNodo listaAnt = NULL ; // puntero al ultimo nodo de la lista
    
    actualizarAnt(listaSig, listaAnt);
    
    mostrarListaAnt(listaAnt);
}

//Funciones
void actualizarAnt(PuntNodo listaSig, PuntNodo &listaAnt)
{
	PuntNodo r = listaSig ;
	PuntNodo ant ;
	while(r != NULL)
   {
      if (r != listaSig) 
	    r->ant = ant ;
	  ant = r ;
	  r = r->sig ;   
   }
   listaAnt = ant ;
}

void  mostrarListaAnt(PuntNodo listaAnt)
{
	PuntNodo r = listaAnt ;
	while(r != NULL)
	{
		cout << " Legajo " << r->datos.legajo << endl ;
		cout << " nombre " << r->datos.nombre << endl ;
		cout << "-----------------------------"<< endl ;
		r = r->ant ;
	}
}
