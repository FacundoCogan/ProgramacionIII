#include <iostream>
#include <conio.h>
#include <stdio.h> 
#include <string.h>

using namespace std;

typedef struct Alumno
{
    int matricula;
    char nombre[21];
    int nota;
}Alumno;

// Puntero al nodo de la lista
typedef struct Nodo* Punt;

// Estructura del nodo
typedef struct Nodo
{
    Alumno info;
    Punt sig;
}Nodo;

//---------------------------
//Prototipos del ejercicio
//---------------------------
void listar(Punt lista);
void listarAprobados(Punt lista);
void buscarMejorada(Punt lista, int)
void cambiarNota(Punt lista, int, int)
Punt busqueda (Punt lista, int)
void mostrarUnaMat(Punt lista, int)
void cambiarNota2 (Punt lista, int, int)
void agregar(Punt &lista, int, Alumno al)
void agregar2 (Punt &lista, int)
void eliminar (Punt &lista, int)

int main () // Funcion principal del programa
{
	int op;
	Punt lista = NULL;
	while (( op = menu() ) != 0)
	{
		switch(op)
		{
			case 1: 
					;break;
			case 2:
					;break;
			case 3: 
					;break;
		}
	}
}

// Implementacion de las funciones
void listar (Punt lista);
{
	Punt r;
	r=lista;
	while(r!=NULL)
	{
		cout<<"Matricula: "<<info.matricula<<" Nombre: "<<info.nombre<<" Nota: "<<info.nota;<<endl;
		r=r->sig;
	}
}

void listarAprobados(Punt lista)
{
	Punt r;
	r=lista;
	while(r!=NULL)
	{
		if (nota>=4)
		{
			cout<<"Matricula: "<<info.matricula<<" Nombre: "<<info.nombre<<" Nota: "<<info.nota;<<endl;
			r=r->sig;
		}
	}
}

void buscarMejorada(Punt lista, int mat)
{
	Punt r;
	r=lista;
	
	cout<<"Ingrese matricula a buscar: "<<endl;
	cin>>mat;
	
	while(r!=NULL && r->info.matricula<mat)
		r=r->sig;
	if (r==NULL || r->info.matricula!=mat)
		cout<<"No esta"<<endl;
	else
		cout<<"Matricula: "<<info.matricula<<" Nombre: "<<info.nombre<<" Nota: "<<info.nota;<<endl;
}

void cambiarNota(Punt lista, int mat, int nuevaNota)
{
	Punt r;
	r=lista;
	
	cout<<"Ingrese matricula a buscar: "<<endl;
	cin>>mat;
	
	while(r!=NULL && r->info.matricula<mat)
		r=r->sig;
	if (r==NULL || r->info.matricula!=mat)
		cout<<"No esta"<<endl;
	else
		cout<<"Nueva nota: "<<endl;
		r->info.nota=nuevaNota;
}

Punt busqueda (Punt lista, int mat)
{
	Punt r;
	r=lista;
	
	cout<<"Ingrese matricula a buscar: "<<endl;
	cin>>mat;
	
	while(r!=NULL && r->info.matricula<mat)
		r=r->sig;
	if (r==NULL || r->info.matricula!=mat)
		return NULL;
	else
		return r;
}

void mostrarUnaMat(Punt lista, int mat)
{
    Punt p=busqueda(lista,mat);
    if(p==NULL)
        cout<<"No esta"<<endl;
    else
         cout<<p->info.nombre<<p->info.nota<<endl;
}

void cambiarNota2 (Punt lista, int mat, int nuevaNota)
{
	Punt p=busqueda(lista, mat);
	if(p==NULL)
		cout<<"No esta"<<endl;
	else
		p->info.nota=nuevaNota;
}

void agregar(Punt &lista, int mat, Alumno al)
{
	Punt n;
	n=new Nodo;
	n->info=al;
	r=lista;
	while(r->info.matricula<al.matricula)
	{
		ant=r;
		r=r->sig;
	}
	n->sig=r;
	if(r!=lista)
		ant->sig=n;
	else
		lista=n;
}

//hacer agregar pero que tenga en cuenta que si la mat. existe, no lo agregue
void agregar2 (Punt &lista, int mat)
{
	
}

void eliminar (Punt &lista, int mat)
{
	Punt r, ant;
	r=lista;
	while(r->info.matricula<al.matricula)
	{
		ant=r;
		r=r->sig;
	}
	if (r==NULL || r->info.matricula!=mat)
		cout<<"No esta."<<endl;
	else
	{
		if(r!=lista)
			ant->sig=r->sig;
		else
			lista=r->sig;
		delete r;
	}
}

