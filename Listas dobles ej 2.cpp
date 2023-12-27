#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <string.h>

using namespace std;

typedef struct Consulta
{
	int puesto;
	int hora;
	char texto[25];
}Consulta;

typedef struct Nodo * PuntNodo;

typedef struct Nodo
{
	Consulta datos;
	PuntNodo sig;
	PuntNodo ant;
}Nodo;

//Prototipos
void generarLista(PuntNodo &, PuntNodo &, Consulta);
void mostrarListaSig(PuntNodo,int,int) ;
void mostrarListaAnt(PuntNodo,int,int) ;
void borrarNAntiguas(PuntNodo &, PuntNodo &, int);
void borrarPuesto(PuntNodo &, PuntNodo &, int);
PuntNodo buscar(PuntNodo, int);

int menu ();

// Funcion principal del programa
int main ()
{
	PuntNodo listaSig=NULL; // puntero al primer nodo de la lista
	PuntNodo listaAnt=NULL; // puntero al ultimo nodo de la lista
	int opcion;
	while((opcion = menu()) != 0)
	{
		switch(opcion)
		{
			case 1 : {
						Consulta cons;
				        cout<<"Ingrese la hora de la consulta: "<<endl;
				        cin>>cons.hora;
				        while(cons.hora!=0)
				        {
				        	cout<<"Ingrese puesto: "<<endl;
				        	cin>>cons.puesto;
				        	
				        	cout<<"Ingrese texto: "<<endl;
				        	cin>>cons.texto;
				        	
				        	cout<<"Ingrese la hora de la consulta: "<<endl;
				        	cin>>cons.hora;
						}
				        break;
			         }
			case 2 : {
				       int horadesde;
				       int horahasta;
				       
				       cout<<"Ingrese desde que hora: "<<endl;
				       cin>>horadesde;
				       
				       cout<<"Ingrese hasta que hora: "<<endl;
				       cin>>horahasta;
				    	
				    	mostrarListaSig(listaSig, horadesde, horahasta);
				        break;
			        }
			         
			case 3 : {
				       int horadesde;
				       int horahasta;
				       
				       cout<<"Ingrese desde que hora: "<<endl;
				       cin>>horadesde;
				       
				       cout<<"Ingrese hasta que hora: "<<endl;
				       cin>>horahasta;
				    	
				    	mostrarListaAnt(listaAnt, horadesde, horahasta);
			           break;
			         }
			case 4 : {
				 	   int n;
				 	   
				 	   cout<<"Ingresar cantidad de consultas antiguas a borrar: "<<endl;
				 	   cin>>n;
				 	   
				 	   borrarNAntiguas(listaAnt, listaSig, n);
					   break;
			         }
			case 5 : {
				       int puesto;
				       
				       cout<<"Ingresar el puesto del que se desean borrar consultas: "<<endl;
				       cin>>puesto;
				       
				       buscar(listaAnt, puesto);
				       borrarPuesto(listaSig, listaAnt, puesto);
				       break;
			        }
			default : break;
		}
	}
	return 0 ;
}

void generarLista(PuntNodo & listaSig , PuntNodo & listaAnt , Consulta cons)
{
   	PuntNodo nuevo = new Nodo ;
   	nuevo->datos = cons;
   	nuevo->sig = NULL ;
   	nuevo->ant = NULL ;
   	
   	if (listaSig == NULL)
   	{
   		  listaSig = nuevo ;
   		  listaAnt = nuevo ;
    }
   	else
	   {
	   	  PuntNodo r , ant ;
	   	  r = listaSig ;
	   	  while(r != NULL && cons.hora >= r->datos.hora)
	   	  {
	   	  	ant = r ;
	   	  	r = r->sig ;
		  }
	   	  if ( r == NULL) //se agrega al final de la lista
	   	  {
	   	  		ant->sig = nuevo ;
	   	  		nuevo->ant = ant ;
	   	  		listaAnt = nuevo ;
  		  }
		  else
		  {
		  	if ( r == listaSig) // se agrega al comienzo de la lista
		  	{
		  		nuevo->sig = listaSig ;
		  		listaSig = nuevo  ;
			}
			else // se agrega entre dos nodos
			{
				ant->sig = nuevo ;
				nuevo->sig = r ;
				nuevo->ant = ant ;
			}
		  }
	   }   
}

void mostrarListaSig (PuntNodo listaSig, int horadesde, int horahasta)
{
	PuntNodo r = listaSig;
	while(r != NULL && r->datos.hora >= horadesde && r->datos.hora <= horahasta)
	{
		cout<<"Hora: "<<r->datos.hora<<endl;
		cout<<"Puesto: "<<r->datos.puesto<<endl;
		cout<<"Texto: "<<r->datos.texto<<endl;
	}
	r=r->sig;
}

void mostrarListaAnt (PuntNodo listaAnt, int horadesde, int horahasta)
{
	PuntNodo r = listaAnt;
	while(r != NULL && r->datos.hora >= horadesde && r->datos.hora <= horahasta)
	{
		cout<<"Hora: "<<r->datos.hora<<endl;
		cout<<"Puesto: "<<r->datos.puesto<<endl;
		cout<<"Texto: "<<r->datos.texto<<endl;
	}
	r=r->ant;
}

void borrarNAntiguas (PuntNodo &listaAnt, PuntNodo &listaSig, int n)
{
	PuntNodo r = listaAnt ;
	PuntNodo aux;
	while (r != NULL && n > 0)
	{
	   aux = r ;	
       if (r->ant != NULL)
         (r->ant)->sig = NULL ;
       listaAnt = r->ant ;
       r = r->ant ;
       delete aux ;
       n-- ;
	}
	if ( r == NULL)
	  listaSig = NULL ;
}

PuntNodo buscar(PuntNodo listaAnt,int puesto)
{
    PuntNodo r=listaAnt;
    while(r!=NULL && r->datos.puesto>puesto)
        r=r->ant;
    if(r!=NULL && r->datos.puesto==puesto)
        return r;
    else
        return NULL;
}

void borrarPuesto (PuntNodo &listaSig, PuntNodo &listaAnt, int puesto)
{
    PuntNodo p=buscar(listaAnt,puesto);
    if(p==NULL)
        cout<<"no esta"<<endl;
    else
    {
        if(p==listaSig) //if(p->ant==NULL)
        {
            listaSig=p->sig;
            if(listaSig==NULL) //p==listaD  p->sig==NULL
                listaAnt=NULL; //elimino el único
            else
                listaSig->ant=NULL;//elimino el menor
        }
        else
        {
            if(p==listaAnt) //p->sig==NULL
            { //elimino al último
                listaAnt=p->ant;
                listaAnt->sig=NULL;
            }
            else
            {  //elimino intermedio
                /*
                PuntD anterior=p->ant;
                PuntD siguiente=p->sig;
                anterior->sig=siguiente;
                siguiente->ant=anterior;
                */
                p->ant->sig=p->sig;
                p->sig->ant=p->ant;
            }
        }
        delete p;
    }
}

int menu(void)
{
	int opcion;  
	cout << " 1 agregar una consulta a la lista doble " << endl ;
	cout << " 2 mostrar consulta entre dos horas usando sig " << endl ;
	cout << " 3 mostrar consulta entre dos horas usando ant " << endl ;
	cout << " 4 eliminar las N consultas mas antiguas " << endl ;
	cout << " 5 eliminar consultas de un puesto " << endl ;
    cout << " 0 salir " << endl ;
	cout << "ingrese opcion " ;
	cin >> opcion;
	return opcion ;
}

