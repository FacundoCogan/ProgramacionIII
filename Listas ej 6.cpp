#include <iostream>
#include <conio.h>
#include <stdio.h> 
#include <string.h>

using namespace std;

// definimos la estructura del registro del archivo empleados
typedef struct Empleados
{
	int legajo;
	char nombre [25];
	int fechaIngreso;
}Empleados;

typedef struct Nodo * PuntNodo;
typedef struct Nodo
{
	Empleados datos;
	PuntNodo sig;
}Nodo;

// Prototipos
void altaEmpleados();
void mostrarEmpleados(char[]);
void generarLista(PuntNodo &);
void crearEmpleadosOrd(PuntNodo);
void agregar_a_la_lista(PuntNodo &, Empleados);

int menu ();

int main ()
{
	PuntNodo lista = NULL ;
	int opcion ;
	while((opcion = menu()) != 0)
	{
		switch (opcion)
		{
			case 1:
					altaEmpleados(); break;
			case 2:
					{
						generarLista(lista);
						crearEmpleadosOrd(lista); break;
					}
					
			case 3:
					{
						char nomArch[20];
						strcpy(nomArch,"Empleados");
				        mostrarEmpleados(nomArch);
				        break;
				    }
			case 4: 
					{
					    char nomArch[20];
	                    strcpy(nomArch,"EmpleadosOrd");
					    mostrarEmpleados(nomArch);
						break;
				    }	
		}
	}
	return 0;
}

void altaEmpleados()
{
	FILE*archi=fopen("Empleados.dat", "wb");
	if(archi!=NULL)
	{
		Empleados datos;	
	   cout << "ingrese legajo ";
	   cin >> datos.legajo ;
	   while (datos.legajo != 0)
	   {
	      cout << "ingrese nombre ";
	      cin >> datos.nombre ;
	      cout << "ingrese ingreso ";
	      cin >> datos.fechaIngreso ;
	      
	      fwrite(&datos,sizeof(datos),1,archi);
	   
	      cout << "ingrese legajo ";
	      cin >> datos.legajo ;
		}
		fclose(archi);
	}
	else
		cout<<"Error en el fopen."<<endl;
}

void mostrarEmpleados (char nomArch[])
{
	FILE * archi = fopen(nomArch, "rb");
	if (archi != NULL)
	{
		Empleados datos;
		fread(&datos, sizeof(datos), 1, archi);
		while (!feof(archi))
		{
			cout << " legajo " << datos.legajo << endl;
            cout << " nombre " << datos.nombre << endl ;
            cout << " ingreso " << datos.fechaIngreso << endl;
            cout << " --------------------- " << endl;
  		    fread(&datos,sizeof(datos),1,archi);
		}
		fclose(archi);
	}
	else
		cout<<"Error en el open"<<endl;
}

void crearEmpleadosOrd(PuntNodo lista)
{
	FILE * archi = fopen("EmpleadosOrd.dat","wb");
	if (archi != NULL)
	{
		PuntNodo r = lista ;
		Empleados emp ;
		while(r != NULL)
		{
			emp = r->datos ;
			fwrite(&emp,sizeof(emp),1,archi) ;
			r = r->sig ;
		}
		fclose(archi);
	}
}

void generarLista(PuntNodo & lista)
{
	FILE * archi = fopen("Empleados","rb");
	if (archi != NULL)
	{
		Empleados emp ;
		fread(&emp,sizeof(emp),1,archi);
		while (!feof(archi))
		{
		  agregar_a_la_lista(lista,emp) ;	
  		  fread(&emp,sizeof(emp),1,archi);
		}
		fclose(archi);
    }
    else
	   cout << "Error en la apertura del archivo empleados " << endl ;	
}

void agregar_a_la_lista(PuntNodo & lista, Empleados emp) 
{
   	PuntNodo nuevo = new Nodo ;
   	nuevo->datos = emp;
   	nuevo->sig = NULL ;
   	
   	if (lista == NULL)
   	   lista = nuevo ;
   	else
	   {
	   	  PuntNodo r , ant ;
	   	  r = lista ;
	   	  while(r != NULL && emp.legajo >= r->datos.legajo)
	   	  {
	   	  	ant = r ;
	   	  	r = r->sig ;
		  }
	   	  if ( r == NULL) //se agrega al final de la lista
	   	  	ant->sig = nuevo ;
		  else
		  {
		  	if ( r == lista) // se agrega al comienzo de la lista
		  	{
		  		nuevo->sig = lista ;
		  		lista = nuevo  ;
			}
			else // se agrega entre dos nodos
			{
				ant->sig = nuevo ;
				nuevo->sig = r ;
			}
		  }
	   }   
}

int menu(void)
{
	int opcion;
	cout << " 1 Crear archivo empleados desordenado " << endl ;
	cout << " 2 Crear archivo empleados ordenado " << endl ;
	cout << " 3 mostrar archivo empleados desordenado " << endl ;
	cout << " 4 mostrar archivo empleados ordenado " << endl ;
    cout << " 0 salir " << endl ;
	cout << "ingrese opcion " ;
	cin >> opcion;
	return opcion ;
}

