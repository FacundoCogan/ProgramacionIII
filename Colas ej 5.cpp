#include <iostream>
#include <conio.h>
#include <stdio.h> 
#include <string.h>

using namespace std;

typedef struct Cliente
{
	int nroUbi;
	int cantProd;
}Clientes;

typedef struct NodoCola*PuntCola;
typedef struct NodoCola
{
	Clientes datos;
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
void poner(Cola &, Clientes);
void sacar(Cola &, Clientes &);
void ver(Cola, Clientes &);
bool vacia(Cola);
void inicializar(Cola &);

//---------------------------
//Prototipos del ejercicio
//---------------------------
void cargarCola(Cola &);
void mostrarCola(Cola &);
void separarCola(Cola &, Cola &);
int menu();

// Funcion principal del programa
int main ()
{
	Cola cola, pocosprod;
	inicializar (cola);
	inicializar (pocosprod);
	int op;
	while (( op = menu() ) != 0)
	{
		switch(op)
		{
			case 1: 
					cargarCola(cola);break;
			case 2:
					mostrarCola(cola);break;
			case 3: 
					{
						separarCola(cola, pocosprod);
						cout<<"------------COLA DE 5 O MAS PRODUCTOS------------"<<endl;
						mostrarCola(cola);
						cout<<"------------COLA DE MENOS DE 5 PRODUCTOS------------"<<endl;
						mostrarCola(pocosprod);
						cout<<"-----------------------------------------"<<endl;
						break;
					}
		}
	}
}

// ---------- FUNCIONES DE COLAS ----------

void poner(Cola &cola, Cliente unCl)
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

void sacar(Cola &cola, Cliente &unCl)
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

void ver(Cola cola, Cliente &unCl)
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

void cargarCola(Cola &cola)
{
	Cliente datos;
	
	cout<<"Ingresar numero de ubicacion (0 para fin de ingreso de datos): "<<endl;
	cin>>datos.nroUbi;
	
	while(datos.nroUbi!=0)
	{
		cout<<"Ingresar cantidad de productos que lleva: "<<endl;
		cin>>datos.cantProd;
		
		poner(cola, datos);
		
		cout<<"Ingresar numero de ubicacion (0 para fin de ingreso de datos): "<<endl;
		cin>>datos.nroUbi;
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

void separarCola (Cola &cola, Cola &pocosprod)
{
	Cliente datos;
	
	int primero;
	if(!vacia(cola))
	{
		ver(cola, datos);
		while(!vacia(cola) && datos.cantProd>0 && datos.cantProd<5)
		{
			sacar(cola, datos);
			poner(pocosprod, datos);
			if(!vacia(cola))
				ver(cola, datos);
		}
		if(!vacia(cola)) // si esto es verdadero, encontre uno con 5 o mas de 5 productos
		{
			primero=datos.nroUbi;
			datos.nroUbi=datos.nroUbi-primero;
			sacar(cola, datos);
			poner(cola, datos);
			ver(cola,datos);
			while(datos.nroUbi!=primero)
			{
				if (datos.cantProd<5)
					poner(pocosprod, datos);
				else
					poner(cola, datos);
				sacar(cola, datos);
				poner(cola, datos);
				ver(cola, datos);
			}
			cout<<endl;
		}
	}
}


// --------------------
int menu () 
{
 int op ;
 cout << "*********** Menu ********** " << endl ;
 cout << "1 Cargar cola de clientes" << endl ;
 cout << "2 Mostrar cola de clientes" << endl ;
 cout << "3 Mostrar cola de clientes que compran menos de 5 productos" <<endl;
 cout << "0 Salir" << endl ;

 cin >> op ;
 return op ;	
}
