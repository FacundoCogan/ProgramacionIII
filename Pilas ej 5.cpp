#include <iostream>
#include <conio.h>
#include <stdio.h> 
#include <string.h>

using namespace std;

typedef struct Datos
{
	int nro;
	float monto;
	char nombre[25];
}Datos;

typedef struct NodoPila*PuntPila;

typedef struct NodoPila
{
	Datos dat;
	PuntPila abajo;
	
}NodoPila;

typedef struct Pila
{
    PuntPila tope;
}Pila;

//----------------------------------------------
//Prototipos de Pila
void inicializar(Pila &);
bool vacia(Pila);
void poner(Pila &, Datos);
void sacar(Pila &, Datos &);
void ver(Pila , Datos &);
//------------------------------------------------

//Prototipo de la funcion principal
void ordenoFacturas (Pila, Pila, Pila &, Pila &);

//Funcion principal del programa
int main ()
{
	Pila pl, pd, pt, po, pdes;
	
	inicializar(pl);
	inicializar(pd);
	inicializar(pt);
	
	ordenoFacturas(pd, pt, po, pdes);
	
}

// ---------- FUNCIONES DE PILAS ----------

bool vacia(Pila pila)
{
    return pila.tope==NULL;
}

void poner(Pila &pila, Datos dato)
{
    PuntPila n=new NodoPila;
    n->dat=dato;
    n->abajo=pila.tope;
    pila.tope=n;
}

void sacar(Pila &pila, Datos &dato)
{
    if(!vacia(pila))
    {
        PuntPila p=pila.tope;
        dato=p->dat;
        pila.tope=p->abajo;
        delete p;
    }
    else
        cout<<"Pila Vacia";
}

void ver(Pila pila, Datos & dato)
{
    if(!vacia(pila))
        dato=pila.tope->dat;
}

void inicializar(Pila &pila)
{
    pila.tope=NULL;
}

// --------------------

void ordenoFacturas (Pila pd, Pila pt, Pila &po, Pila &pdes)
{
	Datos datospd, datospt;
	inicializar(po);
	inicializar(pdes);
	if(!vacia(pd) && (!vacia(pt)))
	{
		ver(pd, datospd);
		ver(pt, datospt);
	}
	while(!vacia(pd) && (!vacia(pt)))
	{
		if(datospd.nro==datospt.nro)
		{
			poner(po, datospd);
			poner(po, datospt);
			sacar(pd, datospd);
			sacar(pt, datospt);
			if(!vacia(pd) && (!vacia(pt)))
			{
				ver(pd, datospd);
				ver(pt, datospt);
			}
		}
		else
		{
			if(datospd.nro!=datospt.nro)
			{
				poner(pdes, datospd);
				poner(pdes, datospt);
				sacar(pd, datospd);
				sacar(pt, datospt);
				if(!vacia(pd) && (!vacia(pt)))
				{
					ver(pd, datospd);
					ver(pt, datospt);
				}
			}
			
		}
	}
	
	while( !vacia(pd)  )
	{
		sacar(pd,datospd);
		poner(pdes,datospd);
	}
	while( !vacia(pt)  )
	{
		sacar(pt,datospt);
		poner(pdes,datospt);
	}
}
