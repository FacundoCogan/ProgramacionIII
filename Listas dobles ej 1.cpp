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

void generarListaSig(PuntNodo & , Empleados);
void actualizarAnt(PuntNodo , PuntNodo &) ;
void mostrarListaSig(PuntNodo) ;
void mostrarListaAnt(PuntNodo) ;

int menu(void);

int main(void)
{
	PuntNodo listaSig = NULL ; // puntero al primer nodo de la lista
    PuntNodo listaAnt = NULL ; // puntero al ultimo nodo de la lista
	int opcion ;
	while((opcion = menu()) != 0)
	{
		switch(opcion)
		{
			case 1 : {
				        Empleados emp ;
				        cout << "Ingrese legajo " ;
				        cin >> emp.legajo ;
				        while (emp.legajo != 0)
				        {
				        	cout << "Ingrese nombre " ;
				            cin >> emp.nombre ;
				        	generarListaSig(listaSig,emp);
				        	cout << "Ingrese legajo " ;
				            cin >> emp.legajo ;
						}
				        break;
			         }
			case 2 : {
                       actualizarAnt(listaSig , listaAnt) ;
				       break;
			        }
			         
			case 3 : {
				       mostrarListaSig(listaSig);
			           break;
			         }
			case 4 : {
				       mostrarListaAnt(listaAnt);
					   break;
			         }
			case 5 : {
				       break;
			        }
			default : break;
		}
	}
	return 0 ;
}

void generarListaSig(PuntNodo & listaSig , Empleados emp)
{
   	PuntNodo nuevo = new Nodo ;
   	nuevo->datos = emp;
   	nuevo->sig = NULL ;
   	nuevo->ant = NULL ;
   	
   	if (listaSig == NULL)
   	   listaSig = nuevo ;
   	else
	   {
	   	  PuntNodo r , ant ;
	   	  r = listaSig ;
	   	  while(r != NULL && emp.legajo >= r->datos.legajo)
	   	  {
	   	  	ant = r ;
	   	  	r = r->sig ;
		  }
	   	  if ( r == NULL) //se agrega al final de la lista
	   	  	ant->sig = nuevo ;
		  else
		  {
		  	if ( r == listaSig) // se agrega al comienzo de la lista
		  	{
		  		nuevo->sig = listaSig ;
		  		listaSig = nuevo  ;
			}
			else // se agrega entre dos nodos
			{
				ant->sig = nuevo ;
				nuevo->sig = r ;
			}
		  }
	   }   
}


void actualizarAnt(PuntNodo listaSig , PuntNodo & listaAnt) 
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

void  mostrarListaSig(PuntNodo listaSig)
{
	PuntNodo r = listaSig ;
	while(r != NULL)
	{
		cout << " Legajo " << r->datos.legajo << endl ;
		cout << " nombre " << r->datos.nombre << endl ;
		cout << "-----------------------------"<< endl ;
		r = r->sig ;
	}
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

int menu(void)
{
	int opcion;
	cout << " 1 Crear lista de empleados con ant = NULL " << endl ;
	cout << " 2 actualizar ant " << endl ;
	cout << " 3 mostrar lista usando  sig " << endl ;
	cout << " 4 mostrar lista usando  ant " << endl ;
    cout << " 0 salir " << endl ;
	cout << "ingrese opcion " ;
	cin >> opcion;
	return opcion ;
}
