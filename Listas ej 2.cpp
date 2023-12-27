//Ejercicio 2 practica de listas

#include <string.h>
#include <stdio.h>
#include <iostream>
#include <conio.h>

using namespace std;

typedef struct producto
{
  int codigo ;
  char descripcion[20];
  float importe;
  int stock ;
}producto;

typedef struct nodo * puntlista ;

typedef struct nodo
{
  producto pro ;
  puntlista sig ;
} nodo ;

void ingresarcodigo(producto &) ;
void ingresardescripcion(producto &) ;
void ingresarimporte(producto &) ;
void ingresarstock(producto &) ;

void borrarTodosLosNodos(puntlista &) ;
void agregarProductoOrdenadoPorCodigo( puntlista & , producto ) ;
void borrarUnNodo( puntlista & , int ) ;
void listar(puntlista) ;

void mostrarKesimo(puntlista , int) ;

int menu(void);

int main(void)
{
   puntlista lista = NULL ; // inicializar la lista vacia
   int opcion ;
   while((opcion = menu()) != 0 )
   {
   	  switch(opcion)
   	  {
   	  	case 1:{
      	  		 borrarTodosLosNodos(lista) ; 
   	  		     break ;
	     }
	     case 2:
			{
			   	producto pro ;
   	    	    ingresarcodigo(pro) ;
			    borrarUnNodo( lista , pro.codigo ) ;
			    break;
		    }
   	    case 3:{
			    producto pro ;
                ingresarcodigo(pro) ;
   	    	    while (pro.codigo != 0)
   	    	    {
                  ingresardescripcion(pro) ;
                  ingresarimporte(pro) ;
                  ingresarstock(pro) ;
				  agregarProductoOrdenadoPorCodigo(lista, pro) ;
  			      ingresarcodigo(pro) ;
   	    	    }
			    break;
			   }
   	    case 4:{
   	    	        int Kesimo ;
   	    	        cout << "ingresar Kesimo " ;
   	    	        cin >> Kesimo ;
       	    	    mostrarKesimo(lista , Kesimo) ;
   	    	    	break;
   	    	     }
   	    case 5:{
			   	break;
			    
             }
		case 6: listar(lista);
		        break;
   	    default: break;
	  }
   }	
   return 0 ;
}

void borrarTodosLosNodos( puntlista & lista ) 
{
	puntlista aux ;
	while(lista != NULL)
	{
		aux = lista ;
		lista = lista->sig ;
		delete aux ;
	}
}

void agregarProductoOrdenadoPorCodigo( puntlista & lista, producto pro) 
{
	puntlista nuevo = new nodo ;
	if (nuevo != NULL)
	{
		//inicilizamos memoria dinamica para nodo
		nuevo->pro = pro ;
		nuevo->sig = NULL ;
		
		if ( lista == NULL)
		   lista = nuevo ;
		else
		{
           puntlista r = lista ;
           puntlista ant ;
           while ( r != NULL && pro.codigo >= r->pro.codigo)
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

void listar( puntlista lista) 
{
   puntlista r = lista ;
   while (r != NULL)
   {
   	  cout << r->pro.codigo << " " << r->pro.descripcion << " " << r->pro.importe << " " << r->pro.stock << endl ;
   	  r = r->sig ;
   }
}

void borrarUnNodo( puntlista & lista , int codigo ) 
{
   puntlista r = lista ;
   puntlista ant ;
   while (r != NULL && codigo != r->pro.codigo)
   {
   	  ant = r ;
   	  r = r->sig ;
   }
   if (r != NULL) // la encontre
   {
   	  if (r == lista) // borrar el primero
   	  	lista = lista->sig ;
	  else
	  {
	  	if ( r->sig == NULL) // borrar el ultimo
	  	  ant->sig = NULL ;
		else // intermedio o entre dos nodos
			ant->sig = r->sig ;
	  }
	  delete r ;
   }
   else
     cout <<  " codigo " << codigo << " no existe " << endl ;
}

void mostrarKesimo(puntlista lista , int Kesimo) 
{
   Kesimo-- ;
   puntlista r = lista ;
   while (r != NULL && Kesimo != 0)
   {
   	  r = r->sig ;
   	  Kesimo-- ;
   }
   if ( r != NULL )
      cout << r->pro.codigo << " " << r->pro.descripcion << " " << r->pro.importe << " " << r->pro.stock << endl ;
   else
      cout << " Keismo " << Kesimo << " fuera de rango " ;	  
}

int menu(void)
{
	int opcion ;
	cout << " 1 borrar todos los nodos de la lista " << endl ;
	cout << " 2 borrar un nodo de un producto " << endl ;
    cout << " 3 agregar nodos ordenados en la lista " << endl ;
    cout << " 4 mostrar Kesimo producto " << endl ;
    cout << " 5  " << endl ;
    cout << " 6 listar " << endl ;
    cout << " 7  " << endl ;
    cout << " 0 salir " << endl ;
    cout << " Ingrese opcion " ;
    cin >> opcion ;
    return opcion ;
}

void ingresarcodigo(producto & pro) 
{
	cout << " Ingrese codigo " ;
   	cin >> pro.codigo ;
}
void ingresardescripcion(producto & pro)  
{
	cout << " Ingrese descripcion " ;
   	cin >> pro.descripcion ;
}
void ingresarimporte(producto & pro) 
{
    cout << " Ingrese importe " ;
   	cin >> pro.importe ;
}

void ingresarstock(producto & pro) 
{
    cout << " Ingrese stock " ;
   	cin >> pro.stock ;
}

