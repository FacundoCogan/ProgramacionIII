#include <iostream>
#include <conio.h>
#include <stdio.h> 
#include <string.h>

using namespace std;

typedef struct Persona
{
	int matricula;
    char nombre[25];
    int nroTelefono;

}Persona;

typedef struct Nodo*Punt;
typedef struct Nodo
{
    Persona datos;
    Punt sig;
}Nodo;

//---------------------------
//Prototipos del ejercicio
//---------------------------
void eliminarUnaMat(Punt &, int);
void mostrarPersonas(Punt);
void ingresarMatricula(Persona &) ;
void ingresarNombre(Persona &) ;
void ingresarTelefono(Persona &) ;
void borrarTodosLosNodos(Punt &) ;
void agregarInscriptoAlComienzo( Punt & , Persona ) ;
void agregarInscriptoAlFinal( Punt & , Persona ) ;
void agregarInscriptoOrdenadoPorMatricula( Punt & , Persona ) ;

int menu ();

// Funcion principal del programa
int main ()
{
	Punt lista = NULL;
	Persona datos ;
	int op;
	while (( op = menu() ) != 0)
	{
		switch(op)
		{
			case 1: 
					borrarTodosLosNodos(lista);break;
					
			case 2:
                ingresarMatricula(datos) ;
   	    	    while (datos.matricula != 0)
   	    	    {
                  ingresarNombre(datos) ;
                  ingresarTelefono(datos) ;
				  agregarInscriptoAlComienzo(lista, datos) ;
  			      ingresarMatricula(datos) ;
   	    	    };break;
   	    	    
			case 3: 
   	    	    ingresarMatricula(datos) ;
   	    	    while (datos.matricula != 0)
   	    	    {
   	    	      ingresarNombre(datos) ;
                  ingresarTelefono(datos) ;
				  agregarInscriptoAlFinal(lista, datos) ;
                  ingresarMatricula(datos) ;
				};break;
					
			case 4: 
   	    	    ingresarMatricula(datos) ;
   	    	    while (datos.matricula != 0)
   	    	    {
   	    	      ingresarNombre(datos) ;
                  ingresarTelefono(datos) ;
				  agregarInscriptoOrdenadoPorMatricula(lista, datos) ;
				  ingresarMatricula(datos) ;
   	    	    };break;
   	    	
			case 5:
					ingresarMatricula(datos) ;
					eliminarUnaMat(lista, datos.matricula);break;
					
			case 6:
					mostrarPersonas(lista);break;
		}
	}
}

// --------------------
// Funciones del menu
// --------------------
void borrarTodosLosNodos( Punt & lista) 
{
	Punt aux;
	while(lista!=NULL)
	{
		aux=lista;
		lista=lista->sig;
		delete aux;
	}
}

void agregarInscriptoAlComienzo( Punt & lista, Persona datos) 
{
	Punt nuevo = new Nodo ;
	if (nuevo != NULL)
	{
		//inicilizamos memoria dinamica para nodo
		nuevo->datos.matricula = datos.matricula ;
		strcpy(nuevo->datos.nombre,datos.nombre) ;
		nuevo->datos.nroTelefono  = datos.nroTelefono ;
		nuevo->sig           = NULL ;
		
		if ( lista == NULL)
		   lista = nuevo ;
		else
		{
           nuevo->sig = lista ;
		   lista = nuevo ;			
		}   
	}
	else
	  cout << "Error en crear memoria dinanima para nodo" << endl ;
}

void agregarInscriptoAlFinal( Punt & lista, Persona datos) 
{
	Punt nuevo = new Nodo ;
	if (nuevo != NULL)
	{
		//inicilizamos memoria dinamica para nodo
		nuevo->datos.matricula = datos.matricula ;
		strcpy(nuevo->datos.nombre,datos.nombre) ;
		nuevo->datos.nroTelefono  = datos.nroTelefono ;
		nuevo->sig           = NULL ;
		
		if ( lista == NULL)
		   lista = nuevo ;
		else
		{
           Punt r = lista ;
           Punt ant ;
           while ( r != NULL)
           {
           	  ant = r ;
           	  r = r -> sig ;
		   }
		   ant->sig = nuevo ;
		}   
	}
	else
	  cout << "Error en crear memoria dinanima para nodo" << endl ;
}

void agregarInscriptoOrdenadoPorMatricula( Punt & lista, Persona datos) 
{
	Punt nuevo = new Nodo ;
	if (nuevo != NULL)
	{
		//inicilizamos memoria dinamica para nodo
		nuevo->datos.matricula = datos.matricula ;
		strcpy(nuevo->datos.nombre,datos.nombre) ;
		nuevo->datos.nroTelefono  = datos.nroTelefono ;
		nuevo->sig           = NULL ;
		
		if ( lista == NULL)
		   lista = nuevo ;
		else
		{
           Punt r = lista ;
           Punt ant ;
           while ( r != NULL && datos.matricula >= r->datos.matricula)
           {
           	  ant = r ;
           	  r = r -> sig ;
		   }
		   if ( r == NULL)  //agrego al final
		   {
		   	  ant->sig = nuevo ;
		   }
		   else
		    {
		    	if (r == lista) //agrego al comienzo
		    	{
		    		nuevo->sig = lista ;
		            lista = nuevo ;			
				}
				else // intermedio o entre dos nodos
				{
					nuevo->sig = ant->sig ;
					ant->sig   = nuevo ;
				}
			}
		}   
	}
	else
	  cout << "Error en crear memoria dinanima para nodo" << endl ;
}

void mostrarPersonas(Punt lista)
{
    Punt r; 
    r= lista; 
    
    while (r!=NULL) 
    {
        cout <<" La persona con nombre: "<<r->datos.nombre<<" tiene el numero de telefono: "<<r->datos.nroTelefono<<endl;
        r=r->sig;
    }
}

void eliminarUnaMat(Punt &lista,int mat)
{
    Punt r,ant;
    r=lista;
    
    cout<<"Ingresar matricula con datos a eliminar: "<<endl;
    cin>>mat;
    
    while(r!=NULL && r->datos.matricula<mat)
    {
        ant=r;
        r=r->sig;
    }
    if(r==NULL || r->datos.matricula!=mat) 
        cout<<"No esta";
    else
    {
        if(r!=lista)
            ant->sig=r->sig;
        else
            lista=r->sig;
        delete r;
    }
}

// --------------------
int menu(void)
{
	int opcion ;
	cout << " 1 borrar todos los nodos de la lista " << endl ;
	cout << " 2 agregar nodos al comienzo de la lista " << endl ;
    cout << " 3 agregar nodos al final de la lista " << endl ;
    cout << " 4 agregar nodos ordenados en la lista " << endl ;
    cout << " 5 borrar un nodo de un inscripto " << endl ;
    cout << " 6 listar " << endl ;
    cout << " 7  " << endl ;
    cout << " 0 salir " << endl ;
    cout << " Ingrese opcion " ;
    cin >> opcion ;
    return opcion ;
}

void ingresarMatricula(Persona & datos) 
{
	cout << " Ingrese matricula " ;
   	cin >> datos.matricula ;
}
void ingresarNombre(Persona & datos)  
{
	cout << " Ingrese nombre " ;
   	cin >> datos.nombre ;
}
void ingresarTelefono(Persona & datos) 
{
    cout << " Ingrese telefono " ;
   	cin >> datos.nroTelefono ;
}
