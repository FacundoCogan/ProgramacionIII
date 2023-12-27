#include <iostream>
#include <string.h>

#define CANTPELICULAS 10

using namespace std;

//Estructura de los archivos
typedef struct PeliculasArch
{
    int cod;
    char titulo[25];
    char genero[25];
    int cantDescargas;
    int fechaUltDes;
}PeliculasArch;

typedef struct DescargasArch
{
    char nombre [25];
    int codPel;
    int fechaDes;
}DescargasArch;

//Estructura lista simple de peliculas y sublista de descargas
typedef struct Descargas
{
	char nombre[25];
	int cod;
	int fechaDes;
}Descargas;
typedef struct NodoSub*PuntSub;
typedef struct NodoSub
{
    Descargas info;
    PuntSub sig;
}NodoSub;

typedef struct Peliculas
{
    int cod;
    char titulo[25];
    char genero[25];
    int cantDescargas;
    int fechaUltDes;
    
    PuntSub listaDescargas;
}Peliculas;

typedef struct NodoL*PuntL;
typedef struct NodoL
{
    Peliculas info;
    PuntL sig;
}NodoL;

//Prototipos
void generarLista(PuntL &);
void generarSubLista(PuntSub &, Descargas);
void agregar(PuntL &, PeliculasArch);
void actualizarArch (PuntL &, int);
PuntL buscarPelicula(PuntL &, int);
void mostrarPeliculasDescargas(PuntL);

int hashing(int);

//Funcion principal del programa
int main ()
{
	PuntL lista=NULL;
	PeliculasArch pelArch;
	
	// a
	generarLista(lista);
	actualizarArch(lista, pelArch.cod);
	
	// b
	mostrarPeliculasDescargas(lista);
}

//Funciones
int hashing(int codigo)
{
	return (codigo % CANTPELICULAS);
}

void generarLista(PuntL &lista)
{
	FILE*arch=fopen("Peliculas.dat", "rb");
	{
		if(arch!=NULL)
		{
			PeliculasArch pelArch;
			fread(&pelArch, sizeof(PeliculasArch), 1, arch);
			while(!feof(arch))
			{
				agregar(lista, pelArch);
				fread(&pelArch, sizeof(PeliculasArch), 1, arch);
			}
			fclose(arch);
		}
	}
	FILE*archD=fopen("Descargas.dat", "rb");
	{
		if(archD!=NULL)
		{
			DescargasArch desArch;
			fread(&desArch, sizeof(DescargasArch), 1, archD);
			while(!feof(arch))
			{
				PuntL n=buscarPelicula(lista, desArch.codPel);
				if(n!=NULL)
				{
					Descargas des; 
					des.cod=n->info.cod;
					des.fechaDes=n->info.fechaUltDes;
					strcpy(des.nombre,desArch.nombre);
				
					generarSubLista(n->info.listaDescargas, des);
				}
				fread(&desArch, sizeof(DescargasArch), 1, archD);
			}
			fclose(arch);
		}
	}
}

void agregar(PuntL &lista, PeliculasArch pelArch)
{
	PuntL nuevo = new NodoL ;
	if (nuevo != NULL)
	{
		Peliculas info;
		info.cod=pelArch.cod;
		info.cantDescargas=pelArch.cantDescargas;
		info.fechaUltDes=pelArch.fechaUltDes;
		strcpy(info.genero,pelArch.genero);
		strcpy(info.titulo,pelArch.titulo);
		//inicilizamos memoria dinamica para nodo
		nuevo->info = info ;
		nuevo->sig = NULL ;
		
		if ( lista == NULL)
		   lista = nuevo ;
		else
		{
           PuntL r = lista ;
           PuntL ant ;
           while (r != NULL && info.cod > r->info.cod)
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
	
}

void generarSubLista(PuntSub & listaDescargas, Descargas info) 
{
	PuntSub nuevo = new NodoSub ;
	nuevo->info = info ;
	nuevo->sig = NULL ;
	
	if (listaDescargas == NULL)
	   listaDescargas = nuevo ;
	else
	{
			PuntSub r = listaDescargas ;
			PuntSub ant ;
	        while (r != NULL && info.fechaDes > r->info.fechaDes)
         	{
		        ant = r ;
		        r = r->sig ;
        	}
        	if (r == listaDescargas) // enganchar al comienzo de la lista por importe
        	{
        		nuevo->sig = listaDescargas ;
        		listaDescargas = nuevo ;
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

void mostrarPeliculasDescargas(PuntL lista)
{
	PuntL r = lista ;
	PuntSub s ;
	while (r != NULL)
	{
		cout << " -------------------------------------------------- " << endl ;
		cout << "Codigo de pelicula: " << r->info.cod<<" Cantidad de descargas: " << r->info.cantDescargas<< endl ;
		
		r = r->sig ;
	}
}

void actualizarArch(PuntL &lista, int codigo)
{
	FILE*arch=fopen("Peliculas.dat", "rb+");
	if(arch!=NULL)
	{
		PuntL lista=NULL;
		PeliculasArch pelArch;
		
		fread(&pelArch, sizeof(PeliculasArch), 1 , arch); 
      	while (!feof(arch))
      	{
      		int posicion = hashing(codigo);
			if (posicion != -1)
			{
				PuntL r = lista ;
				PuntSub s;
				while (r != NULL)
				{
					int cantDescargas=0;
					fseek(arch, posicion*sizeof(PeliculasArch), 0);
		  			fread(&pelArch,sizeof(PeliculasArch), 1, arch);
					
					s = r->info.listaDescargas ;
					while(s != NULL)
					{
						cantDescargas++;
          				s = s->sig ;		
					}
					pelArch.cantDescargas=cantDescargas;
					pelArch.cod=s->info.cod;
		  			pelArch.fechaUltDes = s->info.fechaDes;
		  			fseek(arch, -sizeof(PeliculasArch), 1);
		  			fwrite(&pelArch,sizeof(PeliculasArch), 1, arch);
					r = r->sig ;
				}
				
			}
			fread(&pelArch,sizeof(PeliculasArch), 1, arch);
		}
		fclose(arch);
	}
}

PuntL buscarPelicula(PuntL &lista,int cod)
{
    PuntL r=lista,ant;
    while(r!=NULL && r->info.cod<cod)
    {
        ant=r;
        r=r->sig;
    }

    if(r==NULL || r->info.cod!=cod)
        return NULL;
    else
    {
        if(r!=lista)
            ant->sig=r->sig;
        else
            lista=r->sig;
        return r;
    }
}


