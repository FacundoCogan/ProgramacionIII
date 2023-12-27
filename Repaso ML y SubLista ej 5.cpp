#include <iostream>
#include <string.h>

#define CANTVENDEDORES 10

using namespace std;

//Estructura de los archivos
typedef struct VentasUltimoMes
{
    int nroFact;
    int codVen;
    float importe;
}VentasUltimoMes;

typedef struct VendedoresArch
{
    int codVen;
    float importeTotal;
    int cantVentas;
}VendedoresArch;

//Estructura lista simple de vendedores y sublista
typedef struct Detalles
{
	int nroFactura;
	float importe;
}Detalles;
typedef struct NodoSub*PuntSub;
typedef struct NodoSub
{
    Detalles info;
    PuntSub sig;
}NodoSub;

typedef struct Vendedores
{
    int vendedor;
    
    PuntSub listaDetalles;
}Vendedores;

typedef struct NodoL*PuntL;
typedef struct NodoL
{
    Vendedores info;
    PuntL sig;
}NodoL;

//Prototipos
void generarLista(PuntL &);
void agregar(PuntL &, VentasUltimoMes);
void generarSubLista(PuntSub &, Detalles);
void mostrarVentasUltMes(PuntL);
void actualizarArch(PuntL &);
int buscarVendedor(int);

int hashing(int);

//Funcion principal del programa
int main ()
{
	PuntL lista=NULL;
	
	// a
	generarLista(lista);
	mostrarVentasUltMes(lista);
	
	// b
	actualizarArch(lista);
}

//Funciones
int hashing (int codigo)
{
	return (codigo % CANTVENDEDORES);
}

void generarLista(PuntL &lista)
{
	FILE*arch=fopen("VentasUltimoMes.dat", "rb");
	{
		if(arch!=NULL)
		{
			VentasUltimoMes ventMes;
			fread(&ventMes, sizeof(VentasUltimoMes), 1, arch);
			while(!feof(arch))
			{
				agregar(lista, ventMes);
				fread(&ventMes, sizeof(VentasUltimoMes), 1, arch);
			}
			fclose(arch);
		}
	}
}

void agregar(PuntL &lista, VentasUltimoMes ventMes)
{
	PuntL nuevo = new NodoL ;
	if (nuevo != NULL)
	{
		Vendedores info;
		info.vendedor=ventMes.codVen;
		//inicilizamos memoria dinamica para nodo
		nuevo->info = info ;
		nuevo->sig = NULL ;
		
		if ( lista == NULL)
		   lista = nuevo ;
		else
		{
           PuntL r = lista ;
           PuntL ant ;
           while (r != NULL && info.vendedor > r->info.vendedor)
           {
           	  ant = r ;
           	  r = r -> sig ;
		   }
		   if ( r == NULL)  //agrego al final
		   {
		   	  ant->sig = nuevo;
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
	  cout << "Error en crear memoria dinamica para nodo" << endl ;
	
	Detalles det; 
	det.importe=ventMes.importe;
	det.nroFactura=ventMes.nroFact;
	generarSubLista(nuevo->info.listaDetalles, det);
}

void generarSubLista(PuntSub & listaDetalles, Detalles info) 
{
	PuntSub nuevo = new NodoSub ;
	nuevo->info = info ;
	nuevo->sig = NULL ;
	
	if (listaDetalles == NULL)
	   listaDetalles = nuevo ;
	else
	{
			PuntSub r = listaDetalles ;
			PuntSub ant ;
	        while (r != NULL && info.importe < r->info.importe)
         	{
		        ant = r ;
		        r = r->sig ;
        	}
        	if (r == listaDetalles) // enganchar al comienzo de la lista por importe
        	{
        		nuevo->sig = listaDetalles ;
        		listaDetalles = nuevo ;
			}
        	else
        	{
        		if ( r == NULL) // enganchar al final de la lista por importe
        			ant->sig = nuevo ;
				else // engachar entre dos nodos 
				{
					ant->sig = nuevo ;
					nuevo->sig = r ;
				}
			}
	}
}

void mostrarVentasUltMes(PuntL lista)
{
	PuntL r = lista ;
	PuntSub s ;
	while (r != NULL)
	{
		cout << " -------------------------------------------------- " << endl ;
		cout << "Codigo de vendedor " << r->info.vendedor<< endl ;
		s = r->info.listaDetalles ;
		while(s != NULL)
		{
		  cout << " ....................... Importe vendido en el ultimo mes: " << s->info.importe<< " Numero de factura: " << s->info.nroFactura << endl ;
          s = s->sig ;		
		}
		r = r->sig ;
	}
}

void actualizarArch(PuntL &lista)
{
	FILE*arch=fopen("Vendedores.dat", "rb+");
	if(arch!=NULL)
	{
		PuntL lista=NULL;
		VendedoresArch venArch;
		
		fread(&venArch, sizeof(VendedoresArch), 1 , arch); 
      	while (!feof(arch))
      	{
      		int posicion = buscarVendedor(venArch.codVen); // obtenemos la posicion a nivel de registro en el archivo Vendedores.dat
			if (posicion != -1)
			{
				PuntL r = lista ;
				PuntSub s;
				while (r != NULL)
				{
					int cantVentas=0;
					fseek(arch, posicion*sizeof(VendedoresArch), 0);
		  			fread(&venArch,sizeof(VendedoresArch), 1, arch);
					
					s = r->info.listaDetalles ;
					while(s != NULL)
					{
						cantVentas++;
          				s = s->sig ;		
					}
		  			venArch.importeTotal = venArch.importeTotal + s->info.importe;
		  			venArch.cantVentas = cantVentas;
		  			fseek(arch, -sizeof(VendedoresArch), 1);
		  			fwrite(&venArch,sizeof(VendedoresArch), 1, arch);
					r = r->sig ;
				}
				
			}
			fread(&venArch,sizeof(VendedoresArch), 1, arch);
		}
		fclose(arch);
	}
}

int buscarVendedor(int codigo)
{
	int ret = -1 ; 
	FILE * arch = fopen("Vendedores.dat","rb");
    if ( arch != NULL)
    {
       VendedoresArch venArch;
       int pos = hashing(codigo) ;
       fseek(arch , pos * sizeof(venArch) , 0);
       fread(&venArch,sizeof(VendedoresArch),1,arch); 
	   if (venArch.codVen == codigo)
	      ret = pos ; // retorno la posicion a nivel de registro 
	   else  // busqueda en el area de rebalse
	   {
	     fseek(arch, sizeof(VendedoresArch) * CANTVENDEDORES , 0);
	     fread(&venArch,sizeof(VendedoresArch),1,arch); // lectura secuencial 
	     while (venArch.codVen != codigo)
	         fread(&venArch,sizeof(VendedoresArch),1,arch); 
	     if ( venArch.codVen == codigo )
	        ret = (ftell(arch) - sizeof(VendedoresArch)) / sizeof(VendedoresArch); 	
			// ftell retorna la posicion del puntero de R/W relativa a bytes      	
			// a ftell le resto el sizeof(regp) para obtener la posicion al comienzo del registro
			// y lo dividimos por el sizeof(regp) para convertir la posicion relativa en bytes a 
			// posicion relativa a RL
	   }	   
	   fclose(arch);
    }
    else
     cout << "Error en fopen. " << endl ;
	return ret;
}

