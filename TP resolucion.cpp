/*
*/

#include <iostream>
#include <conio.h>
#include <stdio.h>

using namespace std;

typedef struct NodoCola * PuntNodoCola;

typedef struct comercio
{
  int codigoComercio ;
  char rubro[16];
  PuntNodoCola listaVentas ;
}comercio;

typedef struct nodoComercio * puntlistaComercio ;

typedef struct nodoComercio
{
  comercio comer ;
  puntlistaComercio sig ;
} nodoComercio ;

typedef struct  DatoCola
{
  int codigoComercio ;
  char descripcionProducto[16];
  float importeProducto ;
}DatoCola;



typedef struct NodoCola
{ 
  DatoCola datCola;
  PuntNodoCola sig;
} NodoCola ;

typedef struct Cola
{
	PuntNodoCola Ent,Sal;
}Cola;

//----------------------------------------
//Funciones de Cola
//----------------------------------------
void Inicializar(Cola &c);
int Vacia(Cola c);
void Poner(Cola &c, DatoCola dato);
void Sacar(Cola &c, DatoCola &dato);
void Ver(Cola c, DatoCola &dato);

//----------------------------------
// funciones del ejercicio
//----------------------------------
int menu(void) ;
puntlistaComercio agregarComercio(puntlistaComercio &,comercio);
void cargarCola(Cola &);
void registrarVentas(Cola & , puntlistaComercio & , int);
void mostrarComercio( puntlistaComercio) ;
void mostrarCola(Cola &);
   
void agregarVenta(puntlistaComercio & , DatoCola ) ;
puntlistaComercio buscarComercio(puntlistaComercio , int ) ;
   
int main(void)
{
   puntlistaComercio listaComercio = NULL ;
   Cola solicitudVenta;
   Inicializar(solicitudVenta);
   int opcion ;
   while((opcion = menu()) != 6)  // para salir es 6 
	{
		switch(opcion)
		{
			case 1 : {
				        comercio comer ;
                        cout << " Ingresar Codigo de Comercio " ;
                        cin >> comer.codigoComercio ;
                        while (comer.codigoComercio != 0)
                        {
                     	    cout << " Ingresar Rubro " ;
                            cin >> comer.rubro ;
                            comer.listaVentas = NULL ;
   					        agregarComercio(listaComercio,comer);
                            cout << " Ingresar Codigo de Comercio " ;
                            cin >> comer.codigoComercio ;
						}
				        break;
			         }
			case 2 : {
				          cargarCola(solicitudVenta);
				        break;
			         }
			case 3 : {
				       int cantidad ;
				       cout << " Ingresar cantidad de ventas a registrar " << endl;
				       cin >> cantidad ;
				       registrarVentas(solicitudVenta,listaComercio,cantidad);
                       break;
			         }
			case 4 : {
       				   mostrarComercio( listaComercio) ;
   				       break;
			        }
			case 5 : {
				       mostrarCola(solicitudVenta);
				       break;
			        }
			default : break;
		}
	}
    mostrarCola(solicitudVenta);
	return 0 ;  
}

puntlistaComercio agregarComercio( puntlistaComercio & listaComercio, comercio comer) 
{
	puntlistaComercio nuevo = new nodoComercio ;
	if (nuevo != NULL)
	{
		//inicilizamos memoria dinamica para nodoComercio
		nuevo->comer = comer ;
		nuevo->sig = NULL ;
		
		if ( listaComercio == NULL)
		   listaComercio = nuevo ;
		else
		{
           puntlistaComercio r = listaComercio ;
           puntlistaComercio ant ;
           while ( r != NULL && comer.codigoComercio > r->comer.codigoComercio)
           {
           	  ant = r ;
           	  r = r -> sig ;
		   }
		   if ( r != NULL && comer.codigoComercio == r->comer.codigoComercio)
		      cout << " **** Comercio existe **** " << endl ;
		   else
		   {
			   if ( r == NULL)  //agrego al final
			   {
			   	  ant->sig = nuevo ;
			   }
			   else
			    {
			    	if (r == listaComercio) //agrego al comienzo
			    	{
			    		nuevo->sig = listaComercio ;
			            listaComercio = nuevo ;			
					}
					else // intermedio o entre dos nodos
					{
						nuevo->sig = ant->sig ;
						ant->sig   = nuevo ;
					}
				}
			}
			
		}
	}
	else
	  cout << " Error en crear memoria dinanima para nodo" << endl ;
	return nuevo ;  
}

void mostrarComercio( puntlistaComercio listaComercio) 
{
   puntlistaComercio r = listaComercio ;
   while (r != NULL)
   {
   	  cout << r->comer.codigoComercio << " " << r->comer.rubro  << endl ;
   	  if ( r->comer.listaVentas != NULL)
   	  {
   	  	PuntNodoCola v = r->comer.listaVentas ;
   	  	while(v != NULL)
   	  	{
      	   cout << "-------> " << v->datCola.codigoComercio << " " << v->datCola.descripcionProducto << " " << v->datCola.importeProducto << endl ;
   	  	   v = v->sig ;
		}
	  }
   	  r = r->sig ;
   }
   cout << endl ;
}

void cargarCola(Cola & p) 
{
	DatoCola dat;
	cout << " Ingresar codigo comercio :  " ;
	cin >> dat.codigoComercio ;            
	while(dat.codigoComercio != 0) 
	{
	    cout << " Ingresar descripcion producto :  " ;
	    cin >> dat.descripcionProducto ;            
		cout << " Ingresar importe producto :  " ;
	    cin >> dat.importeProducto ;            
		Poner(p,dat);   
	    cout << " Ingresar codigo comercio :  " ;
	    cin >> dat.codigoComercio ;	
	}
}

void mostrarCola(Cola & p) //muestra la cola y la deja como estaba usando cola auxiliar
{
	Cola aux ;
	Inicializar(aux) ;
	DatoCola dat ;
	while (!Vacia(p))
	{
	  Sacar(p,dat);
	  cout << dat.codigoComercio << " " << dat.descripcionProducto << " " << dat.importeProducto << endl;
	  Poner(aux,dat) ;
    }
    cout << endl ;
    while (!Vacia(aux))
	{
	  Sacar(aux,dat);
	  Poner(p,dat) ;
    }
}

void registrarVentas(Cola & solicitudVenta , puntlistaComercio & listaComercio , int cantidad)
{
	DatoCola dat;
	while(!Vacia(solicitudVenta) && cantidad != 0 )  
	  {
	    Sacar(solicitudVenta,dat);
	    agregarVenta(listaComercio,dat) ;
	    cantidad--;
	  }
}

void agregarVenta(puntlistaComercio & listaComercio , DatoCola dat) 
{
   puntlistaComercio r = buscarComercio(listaComercio,dat.codigoComercio) ;
   if ( r == NULL)
      {
      	cout << " **** comercio " << dat.codigoComercio << " No existe ***** " << endl ;
      	comercio comer ;
      	comer.codigoComercio = dat.codigoComercio ;
      	cout << " Ingrese rubro del nuevo comercio: " ;
      	cin >> comer.rubro ;
      	comer.listaVentas = NULL ;
      	r = agregarComercio(listaComercio,comer) ;
	  }      
    
	PuntNodoCola nue = new NodoCola ;
	nue->datCola = dat ;
	nue->sig = NULL ;
	PuntNodoCola v = r->comer.listaVentas ;
    
    if (r->comer.listaVentas == NULL)
           r->comer.listaVentas = nue ;
    else
	{
	   PuntNodoCola v = r->comer.listaVentas ;
       PuntNodoCola ant	;
       while (v != NULL && nue->datCola.importeProducto <= v->datCola.importeProducto)
       {
       	  ant = v ;
       	  v = v->sig ;
	   }
	   if (v == NULL) //ultimo
	      ant->sig = nue ;
	   else
	       {
	       	 if ( v == r->comer.listaVentas) // primero
	       	 {
		        nue->sig = r->comer.listaVentas ;
		        r->comer.listaVentas = nue ;
		  	 }
		  	 else //entre dos nodos
		  	 {
		  	 	ant->sig = nue ;
		  	 	nue->sig = v ;
			 }
		   }   
	}       
}

puntlistaComercio buscarComercio(puntlistaComercio listaComercio , int codigoComercio)
{
   puntlistaComercio r = listaComercio ;
   while (r != NULL && codigoComercio > r->comer.codigoComercio)
    	  r = r->sig ;
   if (r != NULL && codigoComercio == r->comer.codigoComercio)     	  
     return r ;
   else
     return NULL ;  
}
   	  	
int menu(void)
{
	int opcion;
	cout << " ************ Menu de opciones ******* " << endl ;
	cout << " 1 Inscribir comercios                 " << endl ;
	cout << " 2 Ingresar solicitude de venta en cola de solicitudes  " << endl ;
	cout << " 3 Registrar Ventas                    " << endl ;
	cout << " 4 Mostrar los comercios y sus ventas  " << endl ;
	cout << " 5 Mostrar cola de solicitudes         " << endl ;
	cout << " 6 salir mostrar ventas no registradas " << endl ;
	cout << " ************************************* " << endl ;
	cout << " ingrese opcion " ;
	cin >> opcion;
	cout << " ************************************* " << endl ;
	return opcion ;
}

//----------------------------------------
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

void Poner(Cola &c, DatoCola dato)
{ 
  PuntNodoCola n;
  n = new NodoCola;
  n->datCola = dato;
  n->sig  = NULL;
  if (c.Ent == NULL)
    c.Sal = n;
  else
    c.Ent->sig = n;
  c.Ent = n;
}

void Sacar(Cola &c, DatoCola &dato)
{
  if (c.Sal != NULL)
  { 
    PuntNodoCola n;
    n = c.Sal;
    dato = n->datCola;
    c.Sal = n->sig;
    delete n;
    if (c.Sal == NULL) c.Ent = NULL;
  }
}

void Ver(Cola c, DatoCola &dato)
{
  if (c.Sal != NULL) dato = c.Sal->datCola;
}
