#include <iostream>
#include <string.h>

using namespace std;

//Estructura del archivo
typedef struct Examenes
{
    int dni;
    char nombre[25];
    int fecha;
    int cod;
    int nota;
}Examenes;

//Estructura lista simple de estudiantes y sublista de examenes rendidos

typedef struct Rendidos
{
    int cod;
    int fecha;
    int nota;
}Rendidos;
typedef struct NodoSub*PuntSub;
typedef struct NodoSub
{
    Rendidos info;
    PuntSub sig;
}NodoSub;

typedef struct Estudiantes
{
    int dni;
    char nombre[25];
    PuntSub listaRendidos;
}Estudiantes;
typedef struct NodoL*PuntL;
typedef struct NodoL
{
    Estudiantes info;
    PuntL sig;
}NodoL;

//Prototipos
void generarListaYSL(PuntL &, PuntSub &, Estudiantes, Rendidos);
void agregarUnAlumno(PuntL &, Estudiantes);
void generarSubLista(PuntSub &, Rendidos);
void mostrarAlumno(PuntL &);
void archivoBueno(PuntL &, Rendidos, Estudiantes);
float promedio(PuntL &);

//Funcion principal del programa
int main ()
{
	PuntSub listaRendidos=NULL;
	PuntL lista=NULL;
	Estudiantes info;
	Rendidos ren;
	
	// a
	generarListaYSL(lista, listaRendidos, info, ren);
	
	// b
	mostrarAlumno(lista);
	
	// c
	archivoBueno(lista, ren, info);
}

//Funciones
// a
void generarListaYSL(PuntL &lista, PuntSub &listaRendidos)
{
	FILE*arch=fopen("Examenes.dat", "rb");
	{
		if(arch!=NULL)
		{
			Examenes exa;
			fread(&exa, sizeof(Examenes), 1, arch);
			while(!feof(arch))
			{
				agregarUnAlumno(lista, info);
				generarSubLista(listaRendidos, ren);
				fread(&exa, sizeof(Examenes), 1, arch);
			}
			fclose(arch);
		}
	}
}

void agregarUnAlumno(PuntL &lista, Estudiantes info)
{
	PuntL nuevo = new NodoL ;
	if (nuevo != NULL)
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
           while (r != NULL && info.dni > r->info.dni)
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
}

void generarSubLista(PuntSub & listaRendidos, Rendidos ren) 
{
	PuntSub nuevo = new NodoSub ;
	nuevo->info = ren ;
	nuevo->sig = NULL ;
	
	if (listaRendidos == NULL)
	   listaRendidos = nuevo ;
	else
	{
			PuntSub r = listaRendidos ;
			PuntSub ant ;
	        while (r != NULL && ren.cod > r->info.cod )
         	{
		        ant = r ;
		        r = r->sig ;
        	}
        	if (r == listaRendidos) // enganchar al comienzo de la lista por codigo de materia
        	{
        		nuevo->sig = listaRendidos ;
        		listaRendidos = nuevo ;
			}
        	else
        	{
        		if ( r == NULL) // enganchar al final de la lista por codigo de materia
        			ant->sig = nuevo ;
				else // engachar entre dos nodos 
				{
					ant->sig = nuevo ;
					nuevo->sig = r ;
				}
			}
	}
}

// b
void mostrarAlumno(PuntL &lista)
{
	PuntL r = lista ;
	PuntSub s;
	while (r != NULL)
	{
		cout << " -------------------------------------------------- " << endl ;
		cout << "Nombre: " << r->info.nombre << " Dni: " << r->info.dni<< endl ;
		s = r->info.listaRendidos ;
		while(s != NULL)
		{
		  cout << " ....................... Promedio: "<< promedio(lista) << endl ;
          s = s->sig ;		
		}
		r = r->sig ;
	}
}

float promedio(PuntL &lista)
{
	PuntL r = lista ;
	PuntSub s;
	int cont=0;
	int p;
	while (r != NULL)
	{
		s = r->info.listaRendidos ;
		while(s != NULL)
		{
			if(s->info.nota>0)
			{ 
				cont++;
				p+=s->info.nota;
			}
			s = s->sig ;		
		}
		r = r->sig ;
	}
	return(p/cont);
}

// c
void archivoBueno(PuntL &lista, Rendidos ren, Estudiantes info)
{
	PuntL r = lista ;
	PuntSub s;
	while (r != NULL && strcmp(info.nombre, r->info.nombre)<0)
	{
		s = r->info.listaRendidos ;
		while(s != NULL)
		{
			FILE*arch=fopen("Bueno.dat", "wb");
			{
				if (arch != NULL && s->info.nota>=8)
					fwrite(&ren, sizeof(ren), 1, arch);
				fclose(arch);	
			}
			cout<<"Nombre: "<<r->info.nombre<<" Promedio: "<<promedio(lista)<<endl;
    		s = s->sig;		
    	}
	}
	r = r->sig;
}
