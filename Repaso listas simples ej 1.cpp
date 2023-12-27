#include <iostream>
#include <conio.h>
#include <stdio.h> 
#include <string.h>

using namespace std;

typedef struct Persona
{
	int matricula;
    char nombre[25];
    int nroTelefono;

}Persona;

typedef struct Nodo*Punt;
typedef struct Nodo
{
    Persona datos;
    Punt sig;
}Nodo;

//---------------------------
//Prototipos del ejercicio
//---------------------------
void agregarUnInscripto(Punt &, Persona);
void ingresarMat(Persona);
void darUnaBaja(Punt &, int);
void imprimirLista(Punt);

// Funcion principal del programa
int main()
{
	Punt lista = NULL;
	Persona datos;

	agregarUnInscripto(lista, datos);
	
	ingresarMat(datos);
	darUnaBaja(lista, datos.matricula);
	
	imprimirLista(lista);
}

// --------------------
// Funciones del menu
// --------------------

//a
void agregarUnInscripto(Punt &lista, Persona datos)
{
	Punt nuevo = new Nodo ;
	if (nuevo != NULL)
	{
		//inicilizamos memoria dinamica para nodo
		nuevo->datos = datos ;
		nuevo->sig = NULL ;
		
		if ( lista == NULL)
		   lista = nuevo ;
		else
		{
           Punt r = lista ;
           Punt ant ;
           while (r != NULL && datos.matricula >= r->datos.matricula)
           {
           	  ant = r ;
           	  r = r -> sig ;
		   }
		   if ( r == NULL)  //agrego al final
		   {
		   	  ant->sig = nuevo ;
		   }
		   else
		    {
		    	if (r == lista) //agrego al comienzo
		    	{
		    		nuevo->sig = lista ;
		            lista = nuevo ;			
				}
				else // intermedio o entre dos nodos
				{
					nuevo->sig = ant->sig ;
					ant->sig   = nuevo ;
				}
			}
		}   
	}
	else
	  cout << "Error en crear memoria dinamica para nodo" << endl ;
}

void ingresarMat(Persona datos)
{
	cout<<"Ingresar una matricula: "<<endl;
	cin>>datos.matricula;
}

void darUnaBaja(Punt &lista, int mat)
{
	Punt r = lista ;
	Punt ant ;
   while (r != NULL && mat != r->datos.matricula)
   {
   	  ant = r ;
   	  r = r->sig ;
   }
   if (r != NULL) // la encontre
   {
   	  if (r == lista) // borrar el primero
   	  	lista = lista->sig ;
	  else
	  {
	  	if ( r->sig == NULL) // borrar el ultimo
	  	  ant->sig = NULL ;
		else // intermedio o entre dos nodos
			ant->sig = r->sig ;
	  }
	  delete r ;
   }
   else
     cout <<  " Matricula " << mat << " no existe " << endl ;
}

void imprimirLista(Punt lista)
{
	Punt r; 
    r= lista; 
    
    while (r!=NULL) 
    {
        cout <<" La persona con nombre: "<<r->datos.nombre<<" tiene el numero de telefono: "<<r->datos.nroTelefono<<endl;
        r=r->sig;
    }
}
