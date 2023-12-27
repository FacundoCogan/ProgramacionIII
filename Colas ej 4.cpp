#include <iostream>
#include <conio.h>
#include <stdio.h> 
#include <string.h>

using namespace std;

typedef struct Pasajero
{
	char nombre[25];
	int dni;
	int nroTel;
	char destino;
}Pasajero;

typedef struct NodoCola*PuntCola;
typedef struct NodoCola
{
	Pasajero datos;
	PuntCola atras;
}NodoCola;

typedef struct Cola
{
    PuntCola sal;
    PuntCola ent;
}Cola;

//----------------------
//Prototipos de Cola
//----------------------
void poner(Cola &, Pasajero);
void sacar(Cola &, Pasajero &);
void ver(Cola, Pasajero &);
bool vacia(Cola);
void inicializar(Cola &);

//---------------------------
//Prototipos del ejercicio
//---------------------------
void cargarCola(Cola &, Cola &);
void procesarCola(Cola &, Cola&);
void mostrarCola(Cola &);

// Funcion principal del programa
int main()
{
	Pasajero datos;
	Cola colaC, colaM;
	
	inicializar(colaC);
	inicializar(colaM);
	
	cargarCola(colaC, colaM);
	
}

// ---------- FUNCIONES DE COLAS ----------

void poner(Cola &cola, Pasajero unCl)
{
    PuntCola p;
    p=new NodoCola;
    p->datos=unCl;
    p->atras=NULL;
    if(!vacia(cola))
        cola.ent->atras=p;
    else
        cola.sal=p;
    cola.ent=p;
}

void sacar(Cola &cola, Pasajero &unCl)
{
    if(!vacia(cola))
    {
        PuntCola p;
        p=cola.sal;
        unCl=p->datos;
        cola.sal=p->atras;
        delete p;
        if(cola.sal==NULL)
            cola.ent=NULL;
    }
    else
        cout<<"ERROR cola vacia"<<endl;
}

void ver(Cola cola, Pasajero &unCl)
{
    if(!vacia(cola))
        unCl=cola.sal->datos;
}

bool vacia(Cola cola)
{
    return cola.ent==NULL && cola.sal==NULL;
}

void inicializar(Cola &cola)
{
    cola.ent=NULL;
    cola.sal=NULL;
}

// --------------------

void cargarCola(Cola &colaC, Cola &colaM)
{
	Pasajero datos;
	
	cout<<"Ingresar dni (0 para fin de ingreso de datos): "<<endl;
	cin>>datos.dni;
	
	while(datos.dni!=0)
	{
		cout<<"Ingresar nombre: "<<endl;
		cin>>datos.nombre;
		
		cout<<"Ingrese numero de telefono: "<<endl;
		cin>>datos.nroTel;
		
		cout<<"Ingrese destino: "<<endl;
		cin>>datos.destino;
		
		if(destino=='c')
			poner(colaC, datos);
		else
			poner(colaM, datos);
		
		cout<<"Ingresar dni (0 para fin de ingreso de datos): "<<endl;
		cin>>datos.dni;
	}
}

void procesarCola(Cola &colaE, Cola &colaC, Cola &colaM)
{
	Pasajero datos;
	
	cout<<"Ingrese disponibilidad de vuelo a Cordoba: "<<endl;
	cin>>dispoC;
	
	cout<<"Ingrese disponibilidad de vuelo a Mar del Plata: "<<endl;
	cin>>dispoM;
	
	int primero;
	if(!vacia(colaE))
	{
		ver(colaE, datos);
		if(destino=='c')
		{
			while(!vacia(cola) && dispoC>0)
			{
				
			}
		}
		
	}
	
}

void mostrarCola (Cola &cola)
{
	Cliente datos;
	
	int primero;
	if(!vacia(cola))
	{
		sacar(cola, datos);
		cout<<" Ubicacion: "<<datos.nroUbi<<" Cantidad de productos: "<<datos.cantProd<<endl;
		primero=datos.nroUbi;
		poner(cola, datos);
		ver(cola,datos);
		while(datos.nroUbi!=primero)
		{
			sacar(cola, datos);
			cout<<" Ubicacion: "<<datos.nroUbi<<" Cantidad de productos: "<<datos.cantProd<<endl;
			poner(cola, datos);
			ver(cola, datos);
		}
	}
}
