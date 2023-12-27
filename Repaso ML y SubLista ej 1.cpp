#include <iostream>
#include <string.h>

using namespace std;

typedef struct Materia
{
    int cod;
    int nota;
}Materia;
typedef struct NodoSub*PuntSub;
typedef struct NodoSub
{
    Materia info;
    PuntSub sig;
}NodoSub;

typedef struct Alumno
{
    int mat;
    char nombre[15];
    int anio;
    PuntSub listaMaterias;
}Alumno;
typedef struct NodoL*PuntL;
typedef struct NodoL
{
    Alumno info;
    PuntL sigMat;
    PuntL sigNom;
    PuntL sigAnio;
}NodoL;

//Prototipos
void agregarAlu(PuntL &, PuntL &, PuntL &, Alumno, PuntL&);
void generarSublista(PuntSub &, Materia);
void cargarSubLista(PuntL &);
void agregarMat(PuntL &, PuntL);
void agregarNom(PuntL &, PuntL);
void agregarAnio(PuntL &, PuntL);
void eliminarAlu(PuntL &, PuntL &, PuntL &, int);
void eliminaLogAnio(PuntL &, PuntL);
void eliminaLogNom(PuntL &, PuntL);
PuntL buscaElimLogMat(PuntL &, int);
void eliminarLista(PuntSub &);
void mostrarAluEntreMat(PuntL &, int, int);
void menosDeCinco(PuntL &);
int aprobadas(PuntL &);

//Funcion principal del programa
int main ()
{
	int matEli, matdesde, mathasta;
	Alumno alu;
	PuntL lMat=NULL;
	PuntL lNom=NULL;
	PuntL lAnio=NULL;
	
	//a
	cout<<"Ingrese numero de matricula: "<<endl;
	cin>>alu.mat;
	while(alu.mat!=0)
	{
		cout<<"Ingrese nombre: "<<endl;
		cin>>alu.nombre;
		
		cout<<"Ingrese anio que cursa: "<<endl;
		cin>>alu.anio;
		
		PuntL puntAlu;
		agregarAlu(lMat, lNom, lAnio, alu, puntAlu);
		cargarSubLista(puntAlu);
	}
	
	//b
	cout<<"Ingrese matricula de alumno a eliminar: "<<endl;
	cin>>matEli;
	eliminarAlu(lMat, lNom, lAnio, matEli);
	
	//c
	cout<<"Ingrese matricula desde: "<<endl;
	cin>>matdesde;
	
	cout<<"Ingrese matricula hasta: "<<endl;
	cin>>mathasta;
	mostrarAluEntreMat(lMat, matdesde, mathasta);
	
	//d
	cout<<"Alumnos de primer anio con menos de 5 materias aprobadas: "<<endl;
	menosDeCinco(lAnio);
}

//Funciones
// b
void agregarAlu(PuntL &lMat, PuntL &lNom, PuntL &lAnio, Alumno alu, PuntL &puntAlu)
{
    PuntL nuevo = new NodoL ;
	nuevo->info = alu ;    // datos de usuario
	nuevo->info.listaMaterias = NULL ;
	nuevo->sigMat = NULL ;  // dato de gestion
	nuevo->sigNom  = NULL ;  // dato de gestion
	nuevo->sigAnio  = NULL ;  // dato de gestion
	
    agregarMat(lMat, nuevo);
    agregarNom(lNom, nuevo);
    agregarAnio(lAnio, nuevo);
    
    puntAlu = nuevo;
}

void agregarMat(PuntL &lista, PuntL n)
{
    if (lista == NULL)
		lista = n ;
	else
		{
			PuntL r = lista ;
			PuntL ant ;
	        while (r != NULL && n->info.mat > r->info.mat )
         	{
		        ant = r ;
		        r = r->sigMat ;
        	}
        	if (r == lista) // enganchar al comienzo de la lista por nromat
        	{
        		n->sigMat = lista ;
        		lista = n ;
			}
        	else
        	{
        		if ( r == NULL) // enganchar al final de la lista por nromat
        			ant->sigMat = n ;
				else // engachar entre dos nodos 
				{
					ant->sigMat = n ;
					n->sigMat = r ;
				}
					
			}
		}
}
void agregarNom(PuntL &lista,PuntL n)
{
    if (lista == NULL)
		lista = n ;
	else
		{
			PuntL r = lista ;
			PuntL ant ;
	        while (r != NULL && strcmp(r->info.nombre,n->info.nombre)<0)
         	{
		        ant = r ;
		        r = r->sigNom ;
        	}
        	if (r == lista) // enganchar al comienzo de la lista por nromat
        	{
        		n->sigNom = lista ;
        		lista = n ;
			}
        	else
        	{
        		if ( r == NULL) // enganchar al final de la lista por nromat
        			ant->sigNom = n ;
				else // engachar entre dos nodos 
				{
					ant->sigNom = n ;
					n->sigNom = r ;
				}
					
			}
		}
}
void agregarAnio(PuntL &lista,PuntL n)
{
    if (lista == NULL)
		lista = n ;
	else
		{
			PuntL r = lista ;
			PuntL ant ;
	        while (r != NULL && n->info.anio > r->info.anio)
         	{
		        ant = r ;
		        r = r->sigAnio ;
        	}
        	if (r == lista) // enganchar al comienzo de la lista por nromat
        	{
        		n->sigAnio = lista ;
        		lista = n ;
			}
        	else
        	{
        		if ( r == NULL) // enganchar al final de la lista por nromat
        			ant->sigAnio = n ;
				else // engachar entre dos nodos 
				{
					ant->sigAnio = n ;
					n->sigAnio = r ;
				}
					
			}
		}
}

void cargarSubLista(PuntL & puntAlu) 
{
	Materia mate;
	cout << "Ingrese codigo: " <<endl;
	cin >> mate.cod ;
	while(mate.cod != 0)
	{
    	cout << "Ingrese nota: " <<endl;
	    cin >> mate.nota;
	
	    generarSublista(puntAlu->info.listaMaterias, mate);
	
	    cout << "Ingrese codigo: " <<endl;
		cin >> mate.cod ;
	}
}

void generarSublista(PuntSub & listaMaterias, Materia mate) 
{
	PuntSub nuevo = new NodoSub ;
	nuevo->info = mate ;
	nuevo->sig = NULL ;
	
	if (listaMaterias == NULL)
	   listaMaterias = nuevo ;
	else
	{
			PuntSub r = listaMaterias ;
			PuntSub ant ;
	        while (r != NULL && mate.cod > r->info.cod )
         	{
		        ant = r ;
		        r = r->sig ;
        	}
        	if (r == listaMaterias) // enganchar al comienzo de la lista por codigo de materia
        	{
        		nuevo->sig = listaMaterias ;
        		listaMaterias = nuevo ;
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

// c
void eliminarAlu(PuntL &lMat, PuntL &lNom, PuntL &lAnio, int matEli)
{
    PuntL p;
    p=buscaElimLogMat(lMat, matEli);
    if(p!=NULL)
    {
        eliminaLogNom(lNom,p);
        eliminaLogAnio(lAnio, p);
    }
    eliminarLista(p->info.listaMaterias);
    delete p;
}
PuntL buscaElimLogMat(PuntL &lista, int mat)
{
    PuntL r=lista,ant;
    while(r!=NULL && r->info.mat<mat)
    {
        ant=r;
        r=r->sigMat;
    }

    if(r==NULL || r->info.mat!=mat)
        return NULL;
    else
    {
        if(r!=lista)
            ant->sigMat=r->sigMat;
        else
            lista=r->sigMat;
        return r;
    }
}
void eliminaLogNom(PuntL &lista,PuntL p)
{
    PuntL r=lista,ant;
    while(r!=NULL && r!=p)
    {
        ant=r;
        r=r->sigNom;
    }

    if(r==p)//r!=NULL
    {
        if(r!=lista)
            ant->sigNom=r->sigNom;
        else
            lista=r->sigNom;

    }
}
void eliminaLogAnio(PuntL &lista,PuntL p)
{
    PuntL r=lista,ant;
    while(r!=NULL && r!=p)
    {
        ant=r;
        r=r->sigAnio;
    }

    if(r==p)//r!=NULL
    {
        if(r!=lista)
            ant->sigAnio=r->sigAnio;
        else
            lista=r->sigAnio;

    }
}
void eliminarLista(PuntSub &lista)
{
    PuntSub paux;
    while(lista!=NULL)
    {
        paux=lista;
        lista=lista->sig;
        delete paux;
    }
}

// d
void mostrarAluEntreMat(PuntL &lista, int matdesde, int mathasta)
{
	PuntL r = lista ;
	PuntSub s;
	while (r != NULL && r->info.mat >= matdesde && r->info.mat <= mathasta)
	{
		cout << " -------------------------------------------------- " << endl ;
		cout << "Nombre: " << r->info.nombre << " Matricula: " << r->info.mat << " Anio: " << r->info.anio << endl ;
		s = r->info.listaMaterias ;
		while(s != NULL)
		{
		  cout << " ....................... Codigo de materia aprobada: " << s->info.cod << " Nota: " << s->info.nota << endl ;
          s = s->sig ;		
		}
		r = r->sigMat ;
	}
}

// e
void menosDeCinco(PuntL &lista)
{
	PuntL r = lista ;
	PuntSub s;
	int q=aprobadas(lista);
	while (r != NULL && r->info.anio==1 && q<5)
	{
		cout << " -------------------------------------------------- " << endl ;
		cout << "Nombre: " << r->info.nombre <<endl;
		s = r->info.listaMaterias ;
		while(s != NULL)
		{
          s = s->sig ;		
		}
		r = r->sigMat ;
	}
}

int aprobadas(PuntL &lista)
{
	int cont=0;
	PuntL r = lista ;
	PuntSub s;
	while (r != NULL)
	{
		s = r->info.listaMaterias;
		while(s != NULL)
		{
			if(s->info.nota>=4)
				cont++;
          s = s->sig ;		
		}
		r = r->sigMat ;
	}
	return cont;
}
