#include <iostream>
#include <conio.h>
#include <stdio.h> 
#include <string.h>

#define DIM 30

using namespace std;

typedef struct Alumno
{
    int legajo;
    char nombre[21];
    int nota;
}Alumno;

//protipos de las funciones
void inicializarVector(Alumno*vp[]);
void cargarAlumnos(Alumno*vp[] , int c);
float promedio(Alumno*vp[],int c);
void mostrarAlumnos(Alumno*vp[] , int c);

int menu ();

// funcion principal de nuestro programa
int main ()
{
	Alumno * vp[DIM];
	int op;
	int c;
	while (( op = menu() ) != 0)
	{
		switch(op)
		{
			case 1: 
					inicializarVector(vp);break;
			case 2:
					cargarAlumnos(vp, c);
			case 3:
					promedio(vp, c);
			case 4:
					mostrarAlumnos(vp, c);
		}
	}
	
}

// implementacion de las funciones
void inicializarVector (Alumno* vp[])
{
	int i;
	
	for (i=0; i<DIM; i++)
	{
		vp[i]=NULL;
	}
}

void cargarAlumnos(Alumno* vp[], int c)
{
	int i;
	
	cout<<"Ingrese cantidad de alumnos: "<<endl;
	cin>>c;
	
	for (i=0; i<DIM && i<c; i++)
	{
		vp[i]=new Alumno; //pido memoria dinamica con new, la direccion que devuelve new se guarda en una posicion del vector
		
		cout<<"Ingrese legajo: "<<endl;
		cin>>vp[i]->legajo; // utilizo el operador de referencia por direccion de memoria que es el -> para guardar el legajo tipeado en la parte de la estructura Alumno que corresponde al legajo
		
		cout<<"Ingrese nombre: "<<endl;
		cin>>vp[i]->nombre;
		
		cout<<"Ingrese nota: "<<endl;
		cin>>vp[i]->nota;
	}
}

float promedio(Alumno* vp[], int c)
{
	int i;
	int suma=0;
	
	cout<<"Ingrese cantidad de alumnos: "<<endl;
	cin>>c;
	
	for (i=0; i<DIM && i<c; i++)
	{
		suma+=vp[i]->nota;
	}
	return (suma/c);
}

void mostrarAlumnos(Alumno* vp[], int c)
{
	cout<<"Ingrese cantidad de alumnos: "<<endl;
	cin>>c;
	
	int i;
	for (i=0; i<DIM && i<c; i++)
	{
		cout<<"El alumno con legajo "<<vp[i]->nombre<<" obtuvo la nota "<<vp[i]->nota<<endl;
	}
}

int menu () 
{
 int op ;
 cout << "*********** Menu ********** " << endl ;
 cout << "1 Inicializar vector " << endl ;
 cout << "2 Cargar alumnos al vector" << endl ;
 cout << "3 Promedio de notas" << endl ;
 cout << "4 Mostrar vector de alumnos" << endl ;
 cout << "0 Salir" << endl ;

 cin >> op ;
 return op ;	
}
