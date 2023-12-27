#include <iostream>
#include <conio.h>
#include <stdio.h> 
#include <string.h>

using namespace std;

typedef struct Alumno
{
    int legajo;
    char nombre[21];
    int nota;
}Alumno;

// Puntero al nodo de la lista
typedef struct Nodo* PuntNodo;

// Estructura del nodo
typedef struct Nodo
{
    Alumno datos;
    PuntNodo otroNodo;
}Nodo;

// Prototipos de las funciones
void crear3Alumnos(PuntNodo &);
void mostrarAlumnos(PuntNodo);
void agregarAlumno(PuntNodo &);
int menu ();


int main () // Funcion principal del programa
{
	int op;
	PuntNodo estructura = NULL;
	while (( op = menu() ) != 0)
	{
		switch(op)
		{
			case 1: 
					crear3Alumnos(estructura);break;
			case 2:
					mostrarAlumnos(estructura);break;
			case 3: 
					agregarAlumno(estructura);break;
		}
	}
}


// Implementacion de las funciones
void crear3Alumnos(PuntNodo &pestr)
{
    Alumno alu ;
	
	PuntNodo p , q , r ;
	p = new Nodo ;
	q = new Nodo ;
	r = new Nodo ;
		
	cout << "ingrese legajo " <<endl;
	cin  >> alu.legajo ;
    cout << "ingrese nombre " <<endl;
	cin  >> alu.nombre ;
	p->datos=alu;
	p->otroNodo = q ;
	
	cout << "ingrese legajo " <<endl;
	cin  >> alu.legajo ;
    cout << "ingrese nombre " <<endl;
	cin  >> alu.nombre ;
	q->datos = alu ;
	q->otroNodo = r ;
	
	cout << "ingrese legajo " <<endl;
	cin  >> alu.legajo ;
    cout << "ingrese nombre " <<endl;
	cin  >> alu.nombre ;
	r->datos = alu ;
	r->otroNodo = NULL ;
	
	pestr = p ;
}

void mostrarAlumnos (PuntNodo estructura)
{
	PuntNodo aux = estructura;
	cout << "************************\n" ;
	while (aux != NULL)
	{
		cout<<"Legajo "<<aux->datos.legajo<<" Nombre "<<aux->datos.nombre<<endl;
		aux=aux->otroNodo;
	}
	cout << "************************\n" ;
}

void agregarAlumno( PuntNodo & pestr) // al final de la lista de personas
{
	Alumno alu ;
	
	PuntNodo nuevoAlu = new Nodo ;
		
	cout << "ingrese legajo " ;
	cin  >> alu.legajo ;
    cout << "ingrese nombre " ;
	cin  >> alu.nombre ;
	
	nuevoAlu->datos = alu ;
	nuevoAlu->otroNodo = NULL ;

    if (pestr == NULL)
       pestr = nuevoAlu ;
	else
	 {
     	PuntNodo ant , aux = pestr ;
     	while ( aux != NULL)
	     {
		   ant = aux ;
	       aux = aux->otroNodo ;	
         }   
        ant->otroNodo = nuevoAlu ;
    }
}

int menu () 
{
 int op ;
 cout << "*********** Menu ********** " << endl ;
 cout << "1 Cargar 3 alumnos con sus datos " << endl ;
 cout << "2 Mostrar alumnos con sus datos" << endl ;
 cout << "3 Agregar un alumno mas" <<endl;
 cout << "0 Salir" << endl ;

 cin >> op ;
 return op ;	
}
