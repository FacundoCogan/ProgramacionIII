#include <iostream>
#include <string.h>
#include <conio.h>

using namespace std ;

typedef struct producto
{
	int codigo;
	char nombre[20];
	float precio ;
}producto;

typedef struct nodopro * puntnodopro ;

typedef struct nodopro
{
	producto mipro ;
	puntnodopro sigpro ;
}nodopro ;

typedef struct venta
{
	int nrovta ;
	int fecvta ;
	char cliente[20];
	puntnodopro entlistapro ;
}venta ;

typedef struct nodo * puntnodo ;

typedef struct nodo
{
	venta mivta ;
	puntnodo signrovta ;
	puntnodo sigfecvta ;
	puntnodo sigcliente ;
}nodo ;



//prototipos de las funciones 
int menu(void) ;


//en las funciones enganchar minodo no hago new o sea no pido memoria dinamica
void engancharNodoPorNroVta(puntnodo & entnrovta , puntnodo minodo);
//esta funcion recibe como argumento la entrada a la lista ordenada por nrovta y la direccion del nodo que quiero enganchar
void engancharNodoPorFecVta(puntnodo & entfecvta , puntnodo minodo);
//esta funcion recibe como argumento la entrada a la lista ordenada por fecvta y la direccion del nodo que quiero enganchar
void engancharNodoPorCliente(puntnodo & entcliente , puntnodo minodo);
//esta funcion recibe como argumento la entrada a la lista ordenada por cliente y la direccion del nodo que quiero enganchar

//en esta funcion voy a hacer el new, voy a pedir memoria dinamica para la nueva venta
void generarNodoDeLaVenta(puntnodo & entnrovta , puntnodo & entfecvta , puntnodo & entcliente , venta miventa , puntnodo & puntmivta) ;
// esta funcion recibe como argumento los tres punteros de entrada a la multilista y los datos de la venta en la estructura miventa
// esta funcion va a llamar a las funciones enganchar 


//fucniones mostrar
void mostrarVentasPorNroVta(puntnodo entnrovta);
void mostrarVentasPorFecVta(puntnodo entfecvta);
void mostrarVentasPorCliente(puntnodo entcliente);
void mostrarVentasPorNroVtaConProductos(puntnodo entnrovta);

//funciones de la sublista de productos
void cargarProductosDeLaVenta(puntnodo & puntmivta) ;
void generarSublistaProductos(puntnodopro & entlistapro, producto mipro) ;


int main(void)
{
	puntnodo entnrovta  = NULL;
	puntnodo entfecvta  = NULL;
	puntnodo entcliente = NULL;
	int opcion ;
	while ((opcion = menu())!= 0)
	{
		switch(opcion)
		{
			//agregar venta 
			case 1 :{
				
				venta miventa ;
				cout << "ingrese numero de la venta " ;
				cin >> miventa.nrovta ;
				while(miventa.nrovta != 0)
				{
				    cout << "ingrese fecha de la venta " ;
				    cin >> miventa.fecvta ;
				    cout << "ingrese cliente de la venta " ;
				    cin >> miventa.cliente ;

                    puntnodo puntmivta ;
                    generarNodoDeLaVenta(entnrovta , entfecvta , entcliente , miventa , puntmivta) ;
                   	cargarProductosDeLaVenta(puntmivta) ;
			    
				    cout << "ingrese numero de la venta " ;
				    cin >> miventa.nrovta ;
				}
				
				break;
			}
		case 2 :	
			mostrarVentasPorNroVta(entnrovta);
			break ;

        case 3 :	
			mostrarVentasPorFecVta(entfecvta);
			break ;
         case 4 :	
			mostrarVentasPorCliente(entcliente);
			break ;
         case 5 :	
			mostrarVentasPorNroVtaConProductos(entnrovta);
			break ;

			
		}
	}
}

void generarNodoDeLaVenta(puntnodo & entnrovta , puntnodo & entfecvta , puntnodo & entcliente , venta miventa , puntnodo & puntmivta) 
{
	puntnodo minodo = new nodo ;
	minodo->mivta = miventa ;    // datos de usuario
	minodo->mivta.entlistapro = NULL ;
	minodo->sigcliente = NULL ;  // dato de gestion
	minodo->sigfecvta  = NULL ;  // dato de gestion
	minodo->signrovta  = NULL ;  // dato de gestion
	
    engancharNodoPorNroVta(entnrovta , minodo);
    engancharNodoPorFecVta(entfecvta , minodo);
    engancharNodoPorCliente(entcliente , minodo);
    
    puntmivta = minodo ;
}

void engancharNodoPorNroVta(puntnodo & entnrovta , puntnodo minodo)
{
	if (entnrovta == NULL)
		entnrovta = minodo ;
	else
		{
			puntnodo r = entnrovta ;
			puntnodo ant ;
	        while (r != NULL && minodo->mivta.nrovta > r->mivta.nrovta )
         	{
		        ant = r ;
		        r = r->signrovta ;
        	}
        	if (r == entnrovta) // enganchar al comienzo de la lista por nrovta
        	{
        		minodo->signrovta = entnrovta ;
        		entnrovta = minodo ;
			}
        	else
        	{
        		if ( r == NULL) // enganchar al final de la lista por nrovta
        			ant->signrovta = minodo ;
				else // engachar entre dos nodos 
				{
					ant->signrovta = minodo ;
					minodo->signrovta = r ;
				}
					
			}
		}
}

void engancharNodoPorFecVta(puntnodo & entfecvta , puntnodo minodo)
{
	if (entfecvta == NULL)
		entfecvta = minodo ;
	else
		{
			puntnodo r = entfecvta ;
			puntnodo ant ;
	        while (r != NULL && minodo->mivta.fecvta > r->mivta.fecvta )
         	{
		        ant = r ;
		        r = r->sigfecvta ;
        	}
        	if (r == entfecvta) // enganchar al comienzo de la lista por fecvta
        	{
        		minodo->sigfecvta = entfecvta ;
        		entfecvta = minodo ;
			}
        	else
        	{
        		if ( r == NULL) // enganchar al final de la lista por fecvta
        			ant->sigfecvta = minodo ;
				else // engachar entre dos nodos 
				{
					ant->sigfecvta = minodo ;
					minodo->sigfecvta = r ;
				}
					
			}
		}
}

void engancharNodoPorCliente(puntnodo & entcliente , puntnodo minodo)
{
		if (entcliente == NULL)
		entcliente = minodo ;
	else
		{
			puntnodo r = entcliente ;
			puntnodo ant ;
	        while (r != NULL && strcmp(minodo->mivta.cliente,r->mivta.cliente) >= 0)
         	{
		        ant = r ;
		        r = r->sigcliente ;
        	}
        	if (r == entcliente) // enganchar al comienzo de la lista por cliente
        	{
        		minodo->sigcliente = entcliente ;
        		entcliente = minodo ;
			}
        	else
        	{
        		if ( r == NULL) // enganchar al final de la lista por cliente
        			ant->sigcliente = minodo ;
				else // engachar entre dos nodos 
				{
					ant->sigcliente = minodo ;
					minodo->sigcliente = r ;
				}
					
			}
		}
}

int menu(void)
{
	int opcion ;
	cout << "1 agregar venta " << endl ;
	cout << "2 mostrar ventas por nrovta " << endl ;
	cout << "3 mostrar ventas por fecvta " << endl ;
	cout << "4 mostrar ventas por cliente " << endl ;
	cout << "5 mostrar ventas por nrovta con productos " << endl ;
	cout << "0 salir " << endl ;
	cout << "Ingrese opcion  " ;
	cin >> opcion ;
	return opcion ;
}

void mostrarVentasPorNroVta(puntnodo entnrovta)
{
	puntnodo r = entnrovta ;
	while (r != NULL)
	{
		cout << "nrovta " << r->mivta.nrovta << " fecvta " << r->mivta.fecvta << " Cliente " << r->mivta.cliente << endl ;
		r = r->signrovta ;
	}
}

void mostrarVentasPorNroVtaConProductos(puntnodo entnrovta)
{
	puntnodo r = entnrovta ;
	puntnodopro rpro ;
	while (r != NULL)
	{
		cout << " -------------------------------------------------- " << endl ;
		cout << "nrovta " << r->mivta.nrovta << " fecvta " << r->mivta.fecvta << " Cliente " << r->mivta.cliente << endl ;
		rpro = r->mivta.entlistapro ;
		while(rpro != NULL)
		{
		  cout << " ....................... codpro " << rpro->mipro.codigo << " nompro " << rpro->mipro.nombre << " prepro " << rpro->mipro.precio << endl ;
          rpro = rpro->sigpro ;		
		}
		r = r->signrovta ;
	}
}

void mostrarVentasPorFecVta(puntnodo entfecvta)
{
	puntnodo r = entfecvta ;
	while (r != NULL)
	{
		cout << "nrovta " << r->mivta.nrovta << " fecvta " << r->mivta.fecvta << " Cliente " << r->mivta.cliente << endl ;
		r = r->sigfecvta ;
	}
}

void mostrarVentasPorCliente(puntnodo entcliente)
{
	puntnodo r = entcliente ;
	while (r != NULL)
	{
		cout << "nrovta " << r->mivta.nrovta << " fecvta " << r->mivta.fecvta << " Cliente " << r->mivta.cliente << endl ;
		r = r->sigcliente ;
	}
}

void cargarProductosDeLaVenta(puntnodo & puntmivta) 
{
	producto mipro ;
	cout << "Ingrese codigo producto " ;
	cin >> mipro.codigo ;
	while(mipro.codigo != 0)
	{
    	cout << "Ingrese nombre prtoducto " ;
	    cin >> mipro.nombre ;
	    cout << "Ingrese precio producto " ;
	    cin >> mipro.precio ;
	
	    generarSublistaProductos(puntmivta->mivta.entlistapro,mipro) ;
	
	    cout << "Ingrese codigo producto " ;
	    cin >> mipro.codigo ;
	}
}

void generarSublistaProductos(puntnodopro & entlistapro, producto mipro) 
{
	puntnodopro nuevopro = new nodopro ;
	nuevopro->mipro = mipro ;
	nuevopro->sigpro = NULL ;
	
	if (entlistapro == NULL)
	   entlistapro = nuevopro ;
	else
	{
			puntnodopro r = entlistapro ;
			puntnodopro ant ;
	        while (r != NULL && mipro.codigo > r->mipro.codigo )
         	{
		        ant = r ;
		        r = r->sigpro ;
        	}
        	if (r == entlistapro) // enganchar al comienzo de la lista por fecvta
        	{
        		nuevopro->sigpro = entlistapro ;
        		entlistapro = nuevopro ;
			}
        	else
        	{
        		if ( r == NULL) // enganchar al final de la lista por fecvta
        			ant->sigpro = nuevopro ;
				else // engachar entre dos nodos 
				{
					ant->sigpro = nuevopro ;
					nuevopro->sigpro = r ;
				}
			}
	}
}

