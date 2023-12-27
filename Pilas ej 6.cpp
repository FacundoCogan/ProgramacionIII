#include <iostream>
#include <conio.h>
#include <stdio.h> 
#include <string.h>

using namespace std;

typedef struct Pedidos
{
	int nroPedido;
	int nroCliente;
	char detalle[25];
}Pedidos;

typedef struct NodoPila*PuntPila;

typedef struct NodoPila
{
	Pedidos dat;
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
void poner(Pila &, Pedidos);
void sacar(Pila &, Pedidos &);
void ver(Pila , Pedidos &);
//------------------------------------------------

//Prototipo de la funcion principal
void armarPila(Pedidos, Pila &);
void mostrarPedidos(Pila);

//Funcion principal del programa
int main ()
{
	Pedidos unPed;
	Pila pl;
	inicializar(pl);
	
	armarPila(unPed, pl);
	mostrarPedidos(pl);
	
	
}

// ---------- FUNCIONES DE PILAS ----------

bool vacia(Pila pila)
{
    return pila.tope==NULL;
}

void poner(Pila &pila, Pedidos dato)
{
    PuntPila n=new NodoPila;
    n->dat=dato;
    n->abajo=pila.tope;
    pila.tope=n;
}

void sacar(Pila &pila, Pedidos &dato)
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

void ver(Pila pila, Pedidos & dato)
{
    if(!vacia(pila))
        dato=pila.tope->dat;
}

void inicializar(Pila &pila)
{
    pila.tope=NULL;
}

// --------------------
void armarPila(Pedidos unPed, Pila &pl)
{
	FILE*arch=fopen("Pedidos.dat", "rb");
	Pila paux;
	inicializar(paux);
	Pedidos datospaux;
	if(arch!=NULL)
	{
		fread(&unPed, sizeof(unPed), 1, arch);
		while (!feof(arch))
		{
			poner(paux, unPed);
			if(!vacia(paux))
				ver(paux, unPed);
				
			fread(&unPed, sizeof(unPed), 1, arch);
			
			if(unPed.nroPedido==datospaux.nroPedido)
			{
				poner(pl, datospaux);
				poner(pl, unPed);
				if(!vacia(pl))
					ver(pl, datospaux);
					ver(pl, unPed);
			}
			else
			{
				if(unPed.nroPedido > datospaux.nroPedido)
				{
					poner(pl, datospaux);
					if(!vacia(pl))
						ver(pl, datospaux);
				}
				else
				{
					poner(pl, unPed);
					if(!vacia(pl))
						ver(pl, unPed);
				}
			}
			fread(&unPed, sizeof(unPed), 1, arch);
		}
		fclose(arch);
	}
	
	while(!vacia(paux))
	{
		sacar(paux, unPed);
		poner(pl, unPed);
	}
}

void mostrarPedidos(Pila p)
{
	Pedidos dat;
	Pila paux;
	inicializar(paux);
	while(!vacia(p))
	{
		sacar(p, dat);
		cout<<"Numero de pedido: "<<dat.nroPedido<<" Numero de cliente: "<<dat.nroCliente<<" Detalle: "<<dat.detalle<<endl;
		poner(paux, dat);
	}
	
    while(!vacia(paux))
	{
		sacar(paux,dat);
        poner(p,dat);
	}
	
}

