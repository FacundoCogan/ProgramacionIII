/*
a.	Una función que arme y muestre una cola de personas.
    (cada registro contiene: número de asiento, nombre y si lleva o no equipaje)
d.  separar la cola en cola con equipaje y cola sin equipaje
c. Una función que dada una cola de personas devuelva cuántas personas pasan con equipaje
   antes que aparezca una sin equipaje (ésta queda en la cola). 
   esta version mantiene la cola original como estaba.
   contamos y la cola queda como estaba.
*/

#include <iostream>
#include <conio.h>
#include <stdio.h>

using namespace std;

typedef struct  Datos
{
  int asiento ;	
  char nombre[30];
  char equipaje ; // s tiene y n no tiene
}Datos;

typedef struct NodoC * PuntNodoC;

typedef struct NodoC
{ 
  Datos dato;
  PuntNodoC sig;
} NodoC ;

typedef struct Cola
{
	PuntNodoC Ent,Sal;
}Cola;

//----------------------------------------
//Funciones de Cola
//----------------------------------------
void Inicializar(Cola &c);
int Vacia(Cola c);
void Poner(Cola &c, Datos dato);
void Sacar(Cola &c, Datos &dato);
void Ver(Cola c, Datos &dato);

//----------------------------------
// funciones del ejercicio
//----------------------------------
void cargarCola(Cola &);
void mostrarCola(Cola & ); //sin cola auxiliar
void separarCola(Cola & , Cola &); //separar de la cola los que no tienen equipaje 
int contarConEquipajeCola(Cola &); 

int menu(void);

int main(void)
{
   Cola pasajeros , sinequipaje;
   int opcion;
   while((opcion = menu()) != 0)
   {
     switch(opcion)
     {
      case 1:
      	Inicializar(pasajeros);
        cargarCola(pasajeros);  
	    break;
      case 2:
   		mostrarCola(pasajeros);  
		cout << endl;
		break;
      case 3:
      	Inicializar(sinequipaje);
       	separarCola(pasajeros,sinequipaje);  
        break;
	  case 4:
	  	mostrarCola(sinequipaje);  
        break;
      case 5:
      	cout << "cantidad de pasajeros con equipaje antes que aparezca uno sin equipaje " << contarConEquipajeCola(pasajeros) << endl ; 
        break;
	  case 6:
        break;
	  case 7:
	  	  break;
    }
   }
   return 0 ;    
}

int menu(void)
{
    int opcion;
	cout<<" 1 - cargar Cola pasajeros  " << endl;
	cout<<" 2 - mostrar Cola pasajeros " << endl;
	cout<<" 3 - separarCola  " << endl ;
	cout<<" 4 - mostrar sinequipaje " << endl ;
	cout<<" 5 - contar con equipaje " << endl ;
	cout<<" 6 - "  << endl;
	cout<<" 7 -  " << endl;
	cout<<" 0 - Salir"<<endl;
    cin >> opcion;
    cout << endl;
    return opcion;
}

void cargarCola(Cola & pasajeros) 
{
	Datos dat;
	cout << "Ingresar asiento:  " ;
	cin >> dat.asiento ;            
	while(dat.asiento != 0) 
	{
	    cout << "Ingresar nombre:  " ;
	    cin >> dat.nombre ;            
		cout << "Ingresar tiene equipaje:  " ;
	    cin >> dat.equipaje ;    
		        
		Poner(pasajeros,dat);   
	    
		cout << "Ingresar asiento:  " ;
	    cin >> dat.asiento ;	
	}
}

void mostrarCola(Cola & pasajeros) //muestra la cola y la deja como estaba sin usar cola auxiliar
{
	Datos dat;
	int primero ; //guardara el numero de asiento del primer pasajero de la cola
	if (!Vacia(pasajeros))
	{
	  Sacar(pasajeros,dat);
	  cout << dat.asiento << " " << dat.nombre << " " << dat.equipaje << endl;
	  primero = dat.asiento;
	  Poner(pasajeros,dat);
	  Ver(pasajeros,dat);
	  while(dat.asiento != primero )
	  {
		Sacar(pasajeros,dat);
	    cout << dat.asiento << " " << dat.nombre << " " << dat.equipaje << endl;
		Poner(pasajeros,dat);
		Ver(pasajeros,dat);
	  }
	  cout << endl ;
    }
}

void separarCola(Cola & pasajeros,Cola & sinequipaje) 
{
	Datos dat;
	int primero ; //guardara el numero de asiento del primer pasajero de la cola
	if (!Vacia(pasajeros))
	{
	  Ver(pasajeros,dat);
	  while(!Vacia(pasajeros) && dat.equipaje == 'n')
	  {
	  	 Sacar(pasajeros,dat) ;
	  	 Poner(sinequipaje,dat) ;
	     if (!Vacia(pasajeros))
	        Ver(pasajeros,dat);
	  }	
	  if (!Vacia(pasajeros)) // si esto es verdadero encontre uno con equipaje
	  {
  	  	  primero = dat.asiento;
		  Sacar(pasajeros,dat);
		  Poner(pasajeros,dat);
		  Ver(pasajeros,dat);
		  while(dat.asiento != primero )
		  {
		  	Sacar(pasajeros,dat);
		  	if (dat.equipaje == 'n')
			   Poner(sinequipaje,dat);
			else   
			   Poner(pasajeros,dat);
			Ver(pasajeros,dat);
		  }
		  cout << endl ;
      }   
    }
}

int contarConEquipajeCola(Cola & pasajeros )
{
	int contador = 0 ;
	Datos dat;
	int primero ; //guardara el numero de asiento del primer pasajero de la cola
	if (!Vacia(pasajeros))
	{
	   Ver(pasajeros,dat);
	   if ( dat.equipaje == 's' )
	      contador++ ;
	   primero = dat.asiento ;
	   Sacar(pasajeros,dat);
   	   Poner(pasajeros,dat);
	   Ver(pasajeros,dat);
	   while(dat.asiento != primero && dat.equipaje == 's' )
	   {
	   	  contador++ ;
          Sacar(pasajeros,dat);
		  Poner(pasajeros,dat);
		  Ver(pasajeros,dat);
       }
       while( dat.asiento != primero )
		   {
		   	Sacar(pasajeros,dat);
		  	Poner(pasajeros,dat);
			Ver(pasajeros,dat);
	  	  }
    }
    return contador ;
 } 

//----------------------------------------
//Funciones de Cola
//----------------------------------------
void Inicializar(Cola &c)
{ 
  c.Ent = NULL;
  c.Sal = NULL;
}

int Vacia(Cola c)
{ 
   return (c.Ent == NULL);
}

void Poner(Cola &c, Datos dato)
{ 
  PuntNodoC n;
  n = new NodoC;
  n->dato = dato;
  n->sig  = NULL;
  if (c.Ent == NULL)
    c.Sal = n;
  else
    c.Ent->sig = n;
  c.Ent = n;
}

void Sacar(Cola &c, Datos &dato)
{
  if (c.Sal != NULL)
  { 
    PuntNodoC n;
    n = c.Sal;
    dato = n->dato;
    c.Sal = n->sig;
    delete n;
    if (c.Sal == NULL) c.Ent = NULL;
  }
}

void Ver(Cola c, Datos & dato)
{
  if (c.Sal != NULL) dato = c.Sal->dato;
}
