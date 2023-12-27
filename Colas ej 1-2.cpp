#include <iostream>
#include <conio.h>
#include <stdio.h> 
#include <string.h>

using namespace std;

typedef struct Persona
{
	char nombre[25];
	int nroAsiento;
	char equipaje;
	
}Datos;

typedef struct NodoCola*PuntCola;
typedef struct NodoCola
{
    Persona datos;
    PuntCola atras;
}NodoCola;

typedef struct ColaPersonas
{
    PuntCola sal;
    PuntCola ent;
}ColaPersonas;

//----------------------------------------------
//Prototipos de Cola
void poner(ColaPersonas &, Persona);
void sacar(ColaPersonas &, Persona &);
void ver(ColaPersonas, Persona &);
bool vacia(ColaPersonas);
void inicializar(ColaPersonas &);
//------------------------------------------------
//Prototipos de las funciones de menu
void cargarCola(ColaPersonas &);
void mostrarCola(ColaPersonas &);
int cantPersonas(ColaPersonas &);
int cantEquipaje(ColaPersonas &);
void separarCola(ColaPersonas &, ColaPersonas &);

int menu ();


// Funcion principal del programa
int main ()
{
	ColaPersonas cola, sinequipaje;
	inicializar (cola);
	inicializar (sinequipaje);
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
					cout<<"Cantidad de pasajeros: "<<cantPersonas(cola)<<endl;break;
					
			case 4: 
					cout<<"Cantidad de pasajeros con equipaje hasta que se encuentra uno sin: "<<cantEquipaje(cola);break;
				
			case 5:
				{
					separarCola(cola, sinequipaje);
					cout<<"------------COLA SIN EQUIPAJE------------"<<endl;
					mostrarCola(sinequipaje);
					cout<<"-----------------------------------------"
					break;
				}	
		}
	}
}

// ---------- FUNCIONES DE COLAS ----------

void poner(ColaPersonas &cola, Persona per)
{
    PuntCola p;
    p=new NodoCola;
    p->datos=per;
    p->atras=NULL;
    if(!vacia(cola))
        cola.ent->atras=p;
    else
        cola.sal=p;
    cola.ent=p;
}

void sacar(ColaPersonas &cola, Persona &per)
{
    if(!vacia(cola))
    {
        PuntCola p;
        p=cola.sal;
        per=p->datos;
        cola.sal=p->atras;
        delete p;
        if(cola.sal==NULL)
            cola.ent=NULL;
    }
    else
        cout<<"ERROR cola vacia"<<endl;
}

void ver(ColaPersonas cola, Persona &per)
{
    if(!vacia(cola))
        per=cola.sal->datos;
}

bool vacia(ColaPersonas cola)
{
    return cola.ent==NULL && cola.sal==NULL;
}

void inicializar(ColaPersonas &cola)
{
    cola.ent=NULL;
    cola.sal=NULL;
}

// --------------------

// a) Una función que arme y devuelva una cola de personas (cada registro contiene: nombre, número de asiento y si lleva o no equipaje)

void cargarCola(ColaPersonas &cola)
{
	Persona datos;
	
	cout<<"Ingresar numero de asiento (0 para fin de ingreso de datos): "<<endl;
	cin>>datos.nroAsiento;
	
	while(datos.nroAsiento!=0)
	{
		cout<<"Ingresar nombre del pasajero: "<<endl;
		cin>>datos.nombre;
		
		cout<<"El pasajero lleva equipaje? (s/n)"<<endl;
		cin>>datos.equipaje;
		
		poner(cola, datos);
		
		cout<<"Ingresar numero de asiento (0 para fin de ingreso de datos): "<<endl;
		cin>>datos.nroAsiento;

	}
	
}

void mostrarCola (ColaPersonas &cola)
{
	Persona datos;
	
	int primero;
	if(!vacia(cola))
	{
		sacar(cola, datos);
		cout<<" Asiento: "<<datos.nroAsiento<<" Nombre: "<<datos.nombre<<" Lleva equipaje: "<<datos.equipaje<<endl;
		primero=datos.nroAsiento;
		poner(cola, datos);
		ver(cola,datos);
		while(datos.nroAsiento!=primero)
		{
			sacar(cola, datos);
			cout<<" Asiento: "<<datos.nroAsiento<<" Nombre: "<<datos.nombre<<" Lleva equipaje: "<<datos.equipaje<<endl;
			poner(cola, datos);
			ver(cola, datos);
		}
		
	}

}

/* con cola ausiliar
int cantidad(ColaPersonas & cola)
{
    Persona per;
    ColaPersonas caux;
    inicializar(caux);
    int cont=0;
    while(!vacia(cola))
    {
       sacar(cola,per);
       cont++;
       poner(caux,per);
    }
    while(!vacia(caux))
    {
        sacar(caux,per);
        poner(cola,per);
    }
    return cont;
}
*/

// b) Una función que dada una cola de personas devuelva la cantidad de elementos que contiene. Puede desarmar la cola
int cantPersonas(ColaPersonas & cola)
{
    Persona per,pri;
    int cont=0;
    if(!vacia(cola))
    {
        sacar(cola,pri);
        cont++;
        poner(cola,pri);
        ver(cola,per);
        while(per.nroAsiento != pri.nroAsiento)
        {
            sacar(cola,per);
            cont++;
            poner(cola,per);
            ver(cola,per);
        }
    }
    return cont;
}

// c) Una función que dada una cola de personas devuelva cuántas personas pasan con equipaje antes que aparezca una sin equipaje (ésta queda en la cola). Puede desechar los elementos que pasaron
// esta version no desecha elementos

int cantEquipaje(ColaPersonas & cola)
{
	Persona datos;
	int cont=0;
	int primero; // guardara el numero de asiento del primer pasajero de la cola
	if(!vacia(cola))
	{
		ver(cola, datos);
		if (datos.equipaje=='s')
			cont++;
		primero=datos.nroAsiento;
		sacar(cola, datos);
		poner(cola, datos);
		ver(cola,datos);	
		while(datos.nroAsiento!=primero && datos.equipaje=='s')
		{
			cont++;
			sacar(cola, datos);
			poner(cola, datos);
			ver(cola, datos);
		}
		while(datos.nroAsiento!=primero)
		{	
			sacar(cola, datos);
			poner(cola, datos);
			ver(cola, datos);
		}		
	}
	return cont;
}


// d) Dada una cola de personas dividirla, generando dos nuevas, una con las personas con equipaje y la otra con las que no llevan equipaje; no usar estructuras auxiliares
void separarCola (ColaPersonas &cola, ColaPersonas &sinequipaje)
{
	Persona datos;
	
	int primero;
	if(!vacia(cola))
	{
		ver(cola, datos);
		while(!vacia(cola) && datos.equipaje=='n')
		{
			sacar(cola, datos);
			poner(sinequipaje, datos);
			if(!vacia(cola))
				ver(cola, datos);
		}
		if(!vacia(cola)) // si esto es verdadero, encontre uno con equipaje
		{
			primero=datos.nroAsiento;
			sacar(cola, datos);
			poner(cola, datos);
			ver(cola,datos);
			while(datos.nroAsiento!=primero)
			{
				if (datos.equipaje='n')
					poner(sinequipaje, datos);
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
 cout << "1 Cargar cola de personas" << endl ;
 cout << "2 Mostrar cola de personas" << endl ;
 cout << "3 Cantidad de pasajeros" <<endl;
 cout << "4 Cantidad de pasajeros con equipaje hasta que se encuentra uno sin" <<endl;
 cout << "5 Mostrar cola sin equipaje" <<endl;
 cout << "0 Salir" << endl ;

 cin >> op ;
 return op ;	
}
