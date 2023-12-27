#include <iostream>
#include <string.h>

using namespace std;

typedef struct Compra
{
    int codObra;
    int fecha;
    float importe;
}Compra;
typedef struct NodoSub*PuntSub;
typedef struct NodoSub
{
    Compra info;
    PuntSub sig;
}NodoSub;

typedef struct Obra
{
    int cod;
    PuntSub listaCompras;
}Obra;
typedef struct NodoL*PuntL;
typedef struct NodoL
{
    Obra info;
    PuntL sig;
}NodoL;

//Prototipos
void agregarUnaObra(PuntL &, Obra);
void cargarSubLista(PuntL &);
void generarSublista(PuntSub &, Compra);
void generarArchivo(PuntL &, Compra);

//Funcion principal del programa
int main()
{
	PuntL lista = NULL;
	Obra info;
	Compra comp;
	
	//cargo lista simple
	agregarUnaObra(lista, info);
	
	//cargo sub lista
	PuntL puntObra;
	cargarSubLista(puntObra);
	
	//genero archivo Materiales
	generarArchivo(lista, comp);
}

//Funciones
void agregarUnaObra(PuntL &lista, Obra info)
{
	cout<<"Ingresar codigo de obra en la que se usara el material: "<<endl;
	cin>>info.cod;
	while(info.cod!=0)
	{
		PuntL nuevo = new NodoL ;
		if (nuevo!=NULL)
		{
			//inicilizamos memoria dinamica para nodo
			nuevo->info = info ;
			nuevo->sig = NULL ;
			
			if ( lista == NULL)
			   lista = nuevo ;
			else
			{
	           PuntL r = lista ;
	           PuntL ant ;
	           while (r != NULL && info.cod >= r->info.cod)
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
		  cout << "Error en crear memoria dinamica para nodo" << endl ;
		  
			cout<<"Ingresar codigo de obra en la que se usara el material: "<<endl;
			cin>>info.cod;
	}
}

void cargarSubLista(PuntL & puntObra) 
{
	Compra comp;
	cout << "Ingrese codigo de obra: " <<endl;
	cin >> comp.codObra ;
	while(comp.codObra != 0)
	{
    	cout << "Ingrese fecha de compra: " <<endl;
	    cin >> comp.fecha;
	
	    generarSublista(puntObra->info.listaCompras, comp);
	
	    cout << "Ingrese importe de la compra: " <<endl;
		cin >> comp.importe ;
	}
}

void generarSublista(PuntSub & listaCompras, Compra comp) 
{
	PuntSub nuevo = new NodoSub ;
	nuevo->info = comp ;
	nuevo->sig = NULL ;
	
	if (listaCompras == NULL)
	   listaCompras = nuevo ;
	else
	{
			PuntSub r = listaCompras ;
			PuntSub ant ;
	        while ((r != NULL) && (comp.codObra >= r->info.codObra))
         	{   
				ant = r ;
		        r = r->sig ;
        	}	
        	if (r == listaCompras) // enganchar al comienzo de la lista por codigo de obra
        	{
        		nuevo->sig = listaCompras ;
        		listaCompras = nuevo ;
			}
        	else
        	{
        		if ( r == NULL) // enganchar al final de la lista por codigo de obra
        			ant->sig = nuevo ;
				else // engachar entre dos nodos 
				{
					ant->sig = nuevo ;
					nuevo->sig = r ;
				}
			}
	}
}

void generarArchivo(PuntL &lista, Compra comp)
{
	PuntL r = lista ;
	PuntSub s;
	while (r != NULL)
	{
		s = r->info.listaCompras ;
		while(s != NULL && (comp.codObra >= s->info.codObra))
		{
			if((comp.codObra == s->info.codObra))
			{
				while(s != NULL && (comp.fecha > s->info.fecha))
				{
					FILE*arch=fopen("Materiales.dat", "ab");
					{
						if (arch != NULL)
							fwrite(&comp, sizeof(comp), 1, arch);
						fclose(arch);	
					}
					s = s->sig;	
				}
			}
			else
			{
				FILE*arch=fopen("Materiales.dat", "ab");
				{
					if (arch != NULL)
						fwrite(&comp, sizeof(comp), 1, arch);
					fclose(arch);	
				}
	    		s = s->sig;	
			}
    	}
	}
	r = r->sig;
}

