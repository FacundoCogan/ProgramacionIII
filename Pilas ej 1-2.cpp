#include <iostream>
#include <conio.h>
#include <stdio.h> 
#include <string.h>

using namespace std;

typedef struct Legajo
{
	int numero;
	char sexo;
}Legajo;

typedef struct NodoPila*PuntPila;

typedef struct NodoPila
{
	Legajo datos;
	PuntPila abajo;
	
}NodoPila;

typedef struct Pila
{
    PuntPila tope;
}Pila;

//Prototipos de las funciones
void inicializar(Pila&);
void poner (Pila&, Legajo);
void sacar (Pila&, Legajo&);
void ver (Pila, Legajo&);
bool vacia (Pila);
//--------------------------
void cargarPila(Pila &);
void mostrarPila(Pila);
int cantVarones(Pila);
int nroLegajoM(Pila);
void cargar2Pilas(Pila &pa, Pila &pV, Pila &pM);
void intercaloSexo(Pila pV, Pila pM, Pila &pi);
void unaPilaOrdenada(Pila pV , Pila pM , Pila & po) ;

int menu();

//Funcion principal del programa
int main ()
{
	Pila pa, pV, pM, pi, po;
	inicializar(pa);
	int op;
	while (( op = menu() ) != 0)
	{
		switch(op)
		{
			case 1: 
					cargarPila(pa);break;
			case 2:
					mostrarPila(pa);break;
			case 3: 
					cout<<" Cantidad de varones: "<<cantVarones(pa);break;
			case 4:
					cout<<" Primer legajo mujer: "<<nroLegajoM(pa);break;
			case 5:
				{
						
					cargar2Pilas(pa, pV, pM);
					cout << "--------PILA VARONES--------" << endl;
		  			mostrarPila(pV);  
		  			cout << "--------PILA MUJERES--------" << endl;
		 			mostrarPila(pM);  
		  			cout << "----------------------------" << endl;
		  			break;
        		}
			case 6: 
				{
					cargar2Pilas(pa, pV, pM);
					intercaloSexo(pV, pM, pi);
					cout << "----------------------------" << endl;
					mostrarPila(pi);
					break;
				}
			case 7:
					{	
						cargar2Pilas(pa, pV, pM);
						unaPilaOrdenada(pV , pM , po) ;
						cout << "----------------------------" << endl;
						mostrarPila(po);
						break;
					}	
		}
	}
}


//Implementacion de las funciones

// ---------- FUNCIONES DE PILAS ----------

void inicializar(Pila &pa)
{
    pa.tope=NULL;
}

void poner(Pila &pa, Legajo leg)
{
    PuntPila p=new NodoPila;
    
    p->abajo=pa.tope;
    pa.tope=p;
}

void sacar(Pila &pa, Legajo &leg)
{
    if(!vacia(pa))
    {
        PuntPila p=pa.tope;
        leg=p->datos;
        pa.tope=p->abajo;
        delete p;
    }
    else
        cout<<"ERROR: pila vacia"<<endl;

}

void ver(Pila pa, Legajo &leg)
{
    if(!vacia(pa))
        leg=pa.tope->datos;
}

bool vacia(Pila pa)
{
    
    if(pa.tope==NULL)
        return true;
    else
        return false;
    
}

// --------------------

// a- Una función que arme y devuelva una pila de legajos (cada legajo contiene número y sexo) con valores leídos por teclado. Fin de datos número de legajo cero.

void cargarPila(Pila &pa)
{
	Legajo datos;
	
	cout<<"Ingresar legajo (0 para fin de ingreso de datos): "<<endl;
	cin>>datos.numero;
	
	while (datos.numero!=0)
	{
		cout<<"Ingresar sexo: "<<endl;
		cin>>datos.sexo;
		
		poner(pa, datos);
		
		cout<<"Ingresar legajo: "<<endl;
		cin>>datos.numero;
	}
}

void mostrarPila(Pila p)
{
	Legajo datos;
	Pila paux;
	inicializar(paux);
	while(!vacia(p))
	{
		sacar(p, datos);
		cout<<"Legajo: "<<datos.numero<<" Sexo: "<<datos.sexo<<endl;
		poner(paux, datos);
	}
	cout << endl ;
	
    while(!vacia(paux))
	{
		sacar(paux,datos);
        poner(p,datos);
	}
	
}

// b- Una función que dada una pila de legajos devuelva la cantidad de éstos correspondientes a varones.

int cantVarones(Pila pa)
{
    Pila paux;
    inicializar(paux);
    int cont=0;
    Legajo datos;
    while(!vacia(pa))
    {
        sacar(pa,datos);
        if(datos.sexo=='v')
            cont++;
        poner(paux,datos);
    }
    while(!vacia(paux))
    {
        sacar(paux,datos);
        poner(pa,datos);
    }
    return cont;
}

// c- Una función que dada una pila de legajos devuelva el número del primer legajo correspondiente a una mujer.

int nroLegajoM(Pila pa)
{
	int primer= -1;
	Pila paux;
    inicializar(paux);
    Legajo datos;
    if(!vacia(pa))
    	ver(pa, datos);
    while(!vacia(pa) && datos.sexo!='m')
    {
        sacar(pa, datos);
    	poner(paux, datos);
    	
    	if(!vacia(pa))
        	ver(pa, datos);
    }
	if(!vacia(pa))
		primer=datos.numero;
	
	while(!vacia(paux))
	{
		sacar(paux, datos);
		poner(pa, datos);
	}
	return primer; 
}

// d- Dada una pila de legajos hacer una función que devuelva dos pilas, una con los legajos de los varones y la otra con los de las mujeres.

void cargar2Pilas (Pila &pa, Pila &pV, Pila &pM)
{
	Legajo datos;
	Pila paux;
	inicializar (paux);
	inicializar(pV);
	inicializar(pM);
	while(!vacia(pa))
	{
		sacar(pa,datos);
		if(datos.sexo=='v')
			poner(pV, datos);
		else
			poner(pM, datos);
		poner(paux, datos);
	}
	
	while(!vacia(paux))
	{
		sacar(paux,datos);
        poner(pa,datos);
	}
	
}

// e- Dada una pila de legajos, generar otra donde aparezcan intercalados los de varones y mujeres (1x1), pudiendo o no sobrar legajos de varones y mujeres.

void intercaloSexo(Pila pV, Pila pM, Pila &pi)
{
	Legajo datos;
	inicializar(pi);
	while(!vacia(pV) && (!vacia(pM)))
	{
		sacar(pV, datos);
		poner(pi,datos);
		sacar(pM, datos);
		poner(pi, datos);
	}
	while( !vacia(pV)  )
	{
		sacar(pV,datos);
		poner(pi,datos);
	}
	
	while( !vacia(pM)  )
	{
		sacar(pM,datos);
		poner(pi,datos);
	}
}

// f- Dadas dos pilas de legajos A y B, ordenadas por número de legajo, devolver C conteniendo la totalidad de los legajos. Debe mantener el orden.

void unaPilaOrdenada(Pila pV, Pila pM, Pila &po)
{
	Legajo datosv, datosm;
	inicializar(po);
	if(!vacia(pV) && (!vacia(pM)))
	{
		ver(pV, datosv);
		ver(pM, datosm);
	}
	while(!vacia(pV) && (!vacia(pM)))
	{
		if(datosv.numero==datosm.numero)
		{
			poner(po, datosv);
			poner(po, datosm);
			sacar(pV, datosv);
			sacar(pM, datosm);
			if(!vacia(pV) && (!vacia(pM)))
			{
				ver(pV, datosv);
				ver(pM, datosm);
			}
		}
		else
		{
			if(datosv.numero>datosm.numero)
			{
				poner(po, datosm);
				sacar(pM, datosm);
				if(!vacia(pM))
					ver(pM, datosm);
			}
			else
			{
				poner(po, datosv);
				sacar(pV, datosv);
				if(!vacia(pV))
					ver(pV, datosv);
			}
		}
	}
	
	while( !vacia(pV)  )
	{
		sacar(pV,datosv);
		poner(po,datosv);
	}
	while( !vacia(pM)  )
	{
		sacar(pM,datosm);
		poner(po,datosm);
	}
}

int menu () 
{
 int op ;
 cout << "*********** Menu ********** " << endl ;
 cout << "1 Cargar pila de legajos" << endl ;
 cout << "2 Mostrar pila de legajos" << endl ;
 cout << "3 Mostrar cantidad de varones" <<endl;
 cout << "4 Primer legajo mujer" <<endl;
 cout << "5 Hacer dos pilas diferenciando sexos" <<endl;
 cout<<  "6 Intercalar pilas "<<endl;
 cout<<  "7 Ordenar 2 pilas en una sola "<<endl;
 cout << "0 Salir" << endl ;

 cin >> op ;
 return op ;	
}
