#include <iostream>
#include <conio.h>
#include <stdio.h> 
#include <string.h>

using namespace std;

// definimos la estructura del registro del archivo empleados
typedef struct Empleados
{
	int legajo;
	char nombre [25];
	int fechaIngreso;
}Empleados;

typedef struct Nodo * PuntNodo;
typedef struct Nodo
{
	Empleados datos;
	PuntNodo sig;
}Nodo;

// Prototipos
void generarLista(PuntNodo &);
void crearEmpleadosOrd(PuntNodo);
void agregar_a_la_lista(PuntNodo &, Empleados);

//Funcion principal del programa
int main ()
{
	PuntNodo lista = NULL ;
	
	generarLista(lista);
	crearEmpleadosOrd(lista);
	
}

//Funciones
void crearEmpleadosOrd(PuntNodo lista)
{
	FILE * archi = fopen("EmpleadosOrd.dat","wb");
	if (archi != NULL)
	{
		PuntNodo r = lista ;
		Empleados emp ;
		while(r != NULL)
		{
			emp = r->datos ;
			fwrite(&emp,sizeof(emp),1,archi) ;
			r = r->sig ;
		}
		fclose(archi);
	}
}

void generarLista(PuntNodo & lista)
{
	FILE * archi = fopen("Empleados.dat","rb");
	if (archi != NULL)
	{
		Empleados emp ;
		fread(&emp,sizeof(emp),1,archi);
		while (!feof(archi))
		{
		  agregar_a_la_lista(lista,emp) ;	
  		  fread(&emp,sizeof(emp),1,archi);
		}
		fclose(archi);
    }
    else
	   cout << "Error en la apertura del archivo empleados " << endl ;	
}

void agregar_a_la_lista(PuntNodo & lista, Empleados emp) 
{
   	PuntNodo nuevo = new Nodo ;
   	nuevo->datos = emp;
   	nuevo->sig = NULL ;
   	
   	if (lista == NULL)
   	   lista = nuevo ;
   	else
	   {
	   	  PuntNodo r , ant ;
	   	  r = lista ;
	   	  while(r != NULL && emp.legajo >= r->datos.legajo)
	   	  {
	   	  	ant = r ;
	   	  	r = r->sig ;
		  }
	   	  if ( r == NULL) //se agrega al final de la lista
	   	  	ant->sig = nuevo ;
		  else
		  {
		  	if ( r == lista) // se agrega al comienzo de la lista
		  	{
		  		nuevo->sig = lista ;
		  		lista = nuevo  ;
			}
			else // se agrega entre dos nodos
			{
				ant->sig = nuevo ;
				nuevo->sig = r ;
			}
		  }
	   }   
}
