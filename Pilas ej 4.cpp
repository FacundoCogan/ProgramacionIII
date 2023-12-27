// Se tienen dos pilas, cada elemento contiene código de un vendedor y monto total de ventas del semestre de esa persona. Una pila corresponde a las ventas del primer semestre y la 
// otra a las del segundo semestre, ambas están ordenadas de menor a mayor por código de vendedor. Hacer una función que recibiendo las dos pilas devuelva otra ordenada de mayor 
// a menor por código de vendedor, con los montos totales vendidos por cada uno de ellos. (Un vendedor puede o no haber realizado ventas en un determinado semestre, por lo tanto puede no estar en alguna de las dos pilas, sí en la otra).
#include <iostream>
#include <conio.h>
#include <stdio.h> 
#include <string.h>

using namespace std;

typedef struct Datos
{
	int codVendedor;
	float montoTotal;
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

//Prototipos de las funciones de menu
void cargarPila(Pila &);
void mostrarPila(Pila);
void pilaOrdenada(Pila pps, Pila pss, Pila &po);

int menu ();

//Funcion principal del programa
int main ()
{
	Pila pl, pps, pss, po;
	inicializar (pl);
	inicializar (pps);
	inicializar (pss);
	int op;
	while (( op = menu() ) != 0)
	{
		switch(op)
		{
			case 1: 
					cargarPila(pps);break;
			case 2:
					mostrarPila(pps);break;
			case 3: 
					cargarPila(pss);break;
			case 4:
					mostrarPila(pss);break;
			case 5:
					{
						pilaOrdenada(pps, pss, po);
						cout << "----------------------------" << endl;	
						mostrarPila(po); 
						break;
					}		
		}
	}
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

// Implementacion de las funciones de menu
void cargarPila(Pila &pl)
{
	Datos dat;
	
	cout<<"Ingresar codigo de vendedor (0 para fin de ingreso de datos): "<<endl;
	cin>>dat.codVendedor;
	
	while (dat.codVendedor!=0)
	{
		cout<<"Ingresar monto total de ventas: "<<endl;
		cin>>dat.montoTotal;
		
		poner(pl, dat);
		
		cout<<"Ingresar codigo de vendedor (0 para fin de ingreso de datos): "<<endl;
		cin>>dat.codVendedor;
	}
}

void mostrarPila(Pila p)
{
	Datos dat;
	Pila paux;
	inicializar(paux);
	while(!vacia(p))
	{
		sacar(p, dat);
		cout<<"Codigo de vendedor: "<<dat.codVendedor<<" Monto total de ventas: "<<dat.montoTotal<<endl;
		poner(paux, dat);
	}
	cout << endl ;
	
    while(!vacia(paux))
	{
		sacar(paux,dat);
        poner(p,dat);
	}
	
}

void pilaOrdenada(Pila pps, Pila pss, Pila &po)
{
	Datos datospps, datospss;
	inicializar(po);
	if(!vacia(pps) && (!vacia(pss)))
	{
		ver(pps, datospps);
		ver(pss, datospss);
	}
	while(!vacia(pps) && (!vacia(pss)))
	{
		if(datospps.codVendedor==datospss.codVendedor)
		{
			poner(po, datospps);
			poner(po, datospss);
			sacar(pps, datospps);
			sacar(pss, datospss);
			if(!vacia(pps) && (!vacia(pss)))
			{
				ver(pps, datospps);
				ver(pss, datospss);
			}
		}
		else
		{
			if(datospps.codVendedor > datospss.codVendedor)
			{
				poner(po, datospss);
				sacar(pss, datospss);
				if(!vacia(pss))
					ver(pss, datospss);
			}
			else
			{
				poner(po, datospps);
				sacar(pps, datospps);
				if(!vacia(pps))
					ver(pps, datospps);
			}
		}
	}
	
	while( !vacia(pps)  )
	{
		sacar(pps,datospps);
		poner(po,datospps);
	}
	while( !vacia(pss)  )
	{
		sacar(pss,datospss);
		poner(po,datospss);
	}
}

// --------------------
int menu () 
{
 int op ;
 cout << "*********** Menu ********** " << endl ;
 cout << "1 Cargar pila ventas del primer semestre" << endl ;
 cout << "2 Mostrar pila ventas del primer semestre" << endl ;
 cout << "3 Cargar pila ventas del segundo semestre" <<endl;
 cout << "4 Mostrar pila ventas del segundo semestre" <<endl;
 cout << "5 Armar pila ordenada de mayor a menor y mostrar" <<endl;
 cout << "0 Salir" << endl ;

 cin >> op ;
 return op ;	
}
