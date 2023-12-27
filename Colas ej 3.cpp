#include <iostream>
#include <conio.h>
#include <stdio.h> 
#include <string.h>

using namespace std;

typedef struct Encomienda
{
	int codCliente;
	char direccion[30];
	int km;
	
}Datos;

typedef struct NodoCola*PuntCola;
typedef struct NodoCola
{
    Encomienda datos;
    PuntCola atras;
}NodoCola;

typedef struct ColaEnc
{
    PuntCola sal;
    PuntCola ent;
}ColaEnc;

//----------------------
//Prototipos de Cola
//----------------------
void poner(ColaEnc &, Encomienda);
void sacar(ColaEnc &, Encomienda &);
void ver(ColaEnc, Encomienda &);
bool vacia(ColaEnc);
void inicializar(ColaEnc &);

//---------------------------
//Prototipos del ejercicio
//---------------------------
void cargarCola(ColaEnc &);
void mostrarCola(ColaEnc &);
void realizarEnvios(ColaEnc &, int &);

int menu ();

// Funcion principal del programa
int main ()
{
	ColaEnc cola;
	inicializar (cola);
	int KM=0; // km que puede recorrer el repartidor en 0 
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
					if (KM>0)
					{
						realizarEnvios(cola, KM);
						cout<<" Quedan "<<KM<<" kilometros a favor del repartidor"<<endl;
					}
					else
						cout<<"Debe ingresar KM a recorrer por el repartidor"<<endl;
					break;
					
			case 4: 
					cout<<"Ingresar KM a recorrer por el repartidor"<<endl;
					cin>>KM;
					break;

		}
	}
}

// --------------------
// Funciones de cola
// --------------------
void poner(ColaEnc &cola, Encomienda enc)
{
    PuntCola p;
    p=new NodoCola;
    p->datos=enc;
    p->atras=NULL;
    if(!vacia(cola))
        cola.ent->atras=p;
    else
        cola.sal=p;
    cola.ent=p;
}

void sacar(ColaEnc &cola, Encomienda &enc)
{
    if(!vacia(cola))
    {
        PuntCola p;
        p=cola.sal;
        enc=p->datos;
        cola.sal=p->atras;
        delete p;
        if(cola.sal==NULL)
            cola.ent=NULL;
    }
    else
        cout<<"ERROR cola vacia"<<endl;
}

void ver(ColaEnc cola, Encomienda &enc)
{
    if(!vacia(cola))
        enc=cola.sal->datos;
}

bool vacia(ColaEnc cola)
{
    return cola.ent==NULL && cola.sal==NULL;
}

void inicializar(ColaEnc &cola)
{
    cola.ent=NULL;
    cola.sal=NULL;
}

// --------------------
// Funciones del menu
// --------------------
void cargarCola(ColaEnc &cola)
{
	Encomienda datos;
	
	cout<<"Ingresar codigo de cliente (0 para fin de ingreso de datos): "<<endl;
	cin>>datos.codCliente;
	
	while(datos.codCliente!=0)
	{
		cout<<"Ingresar direccion de la encomienda: "<<endl;
		cin>>datos.direccion;
		
		cout<<"Ingresar km (distancia a recorrer para entregar el pedido): "<<endl;
		cin>>datos.km;
		
		poner(cola, datos);
		
		cout<<"Ingresar codigo de cliente (0 para fin de ingreso de datos): "<<endl;
		cin>>datos.codCliente;

	}	
}

void mostrarCola (ColaEnc &cola)
{
	Encomienda datos;
	
	int primero;
	if(!vacia(cola))
	{
		sacar(cola, datos);
		cout<<" Codigo de cliente: "<<datos.codCliente<<" Direccion: "<<datos.direccion<<" km: "<<datos.km<<endl;
		primero=datos.codCliente;
		poner(cola, datos);
		ver(cola,datos);
		while(datos.codCliente!=primero)
		{
			sacar(cola, datos);
			cout<<" Codigo de cliente: "<<datos.codCliente<<" Direccion: "<<datos.direccion<<" km: "<<datos.km<<endl;
			poner(cola, datos);
			ver(cola, datos);
		}
	}
}

void realizarEnvios(ColaEnc &cola, int &KM) // version que elimina de la cola los pedidos realizados
{
	Encomienda datos;
	int primero;
	if (!vacia(cola))
	{
		ver(cola, datos);
		while(!vacia(cola) && datos.km <= KM && KM>0)
		{
			sacar(cola, datos);
			KM=KM-datos.km;
			if (!vacia(cola))
				ver(cola, datos);
		}
		if (!vacia(cola))
		{
			primero=datos.codCliente;
			sacar(cola, datos);
			poner(cola, datos);
			ver(cola, datos);
			while(datos.codCliente!=primero)
			{
				sacar(cola, datos);
				if(datos.km<=KM)
					KM=KM-datos.km;
				else
					poner(cola, datos);
				ver(cola, datos);
			}
		}
	}
}

// --------------------
int menu () 
{
 int op ;
 cout << "*********** Menu ********** " << endl ;
 cout << "1 Cargar cola de encomiendas" << endl ;
 cout << "2 Mostrar cola de encomiendas" << endl ;
 cout << "3 Procesar envios" <<endl;
 cout << "4 Ingresar km que recorrer el repartidor" <<endl;
 cout << "0 Salir" << endl ;

 cin >> op ;
 return op ;	
}
	
