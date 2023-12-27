#include <iostream>
#include <string.h>

using namespace std;

//Estructura de los archivos
typedef struct Inscripcion
{
    int mat;
    char nombreApe[25];
    int codMat;
}Examenes;

typedef struct AlumnoArchivo
{
    int nroMat;
    char nombreApe[25];
    int cantMatIns;
}AlumnoArchivo;

//Estructura lista simple de alumnos y sublista
typedef struct NodoSub*PuntSub;
typedef struct NodoSub
{
    int codMat;
    PuntSub sig;
}NodoSub;

typedef struct Alumno
{
    int nroMat;
    char nombreApe[25];
    
    PuntSub listaDatos;
}Alumno;

typedef struct NodoL*PuntL;
typedef struct NodoL
{
    Alumno info;
    PuntL sig;
}NodoL;

//Prototipos
void generarLista(PuntL &);
void agregar(PuntL &, Inscripcion);
void generarSubLista(PuntSub &, int);
void generarArchivo(PuntL &);
void mostrarAlumno(PuntL);

//Funcion principal del programa
int main ()
{
	PuntL lista=NULL;
	
	// a
	generarLista(lista);
	generarArchivo(lista);
	
	// b
	mostrarAlumno(lista);
}

//Funciones
void generarLista(PuntL &lista)
{
	FILE*arch=fopen("Inscripcion.dat", "rb");
	{
		if(arch!=NULL)
		{
			Inscripcion ins;
			int codMat;
			fread(&ins, sizeof(Inscripcion), 1, arch);
			while(!feof(arch))
			{
				agregar(lista, ins);
				fread(&ins, sizeof(Inscripcion), 1, arch);
			}
			fclose(arch);
		}
	}
}

void agregar(PuntL &lista, Inscripcion ins)
{
	PuntL nuevo = new NodoL ;
	if (nuevo != NULL)
	{
		Alumno info;
		info.nroMat=ins.mat;
		strcpy(info.nombreApe,ins.nombreApe);
		//inicilizamos memoria dinamica para nodo
		nuevo->info = info ;
		nuevo->sig = NULL ;
		
		if ( lista == NULL)
		   lista = nuevo ;
		else
		{
           PuntL r = lista ;
           PuntL ant ;
           while (r != NULL && info.nroMat > r->info.nroMat)
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
	  
	generarSubLista(nuevo->info.listaDatos, ins.codMat);
}

void generarSubLista(PuntSub & listaDatos, int codMat) 
{
	PuntSub nuevo = new NodoSub ;
	nuevo->codMat = codMat ;
	nuevo->sig = NULL ;
	
	if (listaDatos == NULL)
	   listaDatos = nuevo ;
	else
	{
			PuntSub r = listaDatos ;
			PuntSub ant ;
	        while (r != NULL && codMat > r->codMat)
         	{
		        ant = r ;
		        r = r->sig ;
        	}
        	if (r == listaDatos) // enganchar al comienzo de la lista por codigo de materia
        	{
        		nuevo->sig = listaDatos ;
        		listaDatos = nuevo ;
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

void generarArchivo(PuntL &lista)
{
	FILE*arch=fopen("Alumnos.dat", "wb");
	if (arch != NULL)
	{
		PuntL r = lista;
		PuntSub s;
		while (r != NULL)
		{
			AlumnoArchivo aluArch;
			aluArch.nroMat=r->info.nroMat;
			strcpy(aluArch.nombreApe,r->info.nombreApe);
			int cantMaterias=0;
			
			s = r->info.listaDatos;	
			while(s != NULL)
			{
	    		s = s->sig;
				cantMaterias++;		
	    	}
	    	aluArch.cantMatIns=cantMaterias;
	    	fwrite(&aluArch, sizeof(AlumnoArchivo), 1, arch);
	    	r = r->sig;
		}
		fclose(arch);
	}
}

void agregarAlfa(PuntL &lista, Alumno info)
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
           while (r != NULL && strcmp(nuevo->info.nombreApe,r->info.nombreApe) >= 0)
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

void mostrarAlumno(PuntL lista)
{
	PuntL r = lista ;
	PuntL nuevaLista=NULL;
	
	while (r != NULL)
	{
		agregarAlfa(nuevaLista, r->info);
		r = r->sig ;
	}
	r=nuevaLista;
	while(r!=NULL)
	{
		PuntSub s = r->info.listaDatos;	
		int cantMaterias=0;
		while(s != NULL)
		{
	    	s = s->sig;
			cantMaterias++;	
	    }
		if(cantMaterias>5)
			cout<<" Nombre: "<<r->info.nombreApe<<" Matricula: "<<r->info.nroMat<<" Cantidad de materias inscriptas: "<<cantMaterias<<endl;
	}
}

