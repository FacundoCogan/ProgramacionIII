#include <iostream>

using namespace std;

typedef struct DatosSub
{
	int Numero;
	char letra; 
}DatosSub;

typedef struct NodoSub * PuntSub;
typedef struct NodoSub
{
	DatosSub datossub;
	PuntSub sig;
}NodoSub;

typedef struct Datos
{
	int Numero;
	char nombre[20]; 
	int monto;
	PuntSub sub;
}Datos;

typedef struct NodoA * PuntA;
typedef struct NodoA
{
	Datos datos;
	PuntA izq;
	PuntA der;
}NodoA;


void AgregarNodoArbol(PuntA & raiz , Datos mes );
void AgregarSub(PuntA raiz );
PuntA BuscarMes(PuntA raiz, int nro) ;
void MostrarArbol(PuntA raiz);
void TotalDeMontos(PuntA raiz , int &);
int TotalDeMontosV2(PuntA raiz ) ;

int menu(void);

int main(void)
{
	PuntA raiz = NULL ;
	Datos datos ;
	int opcion ;
    while((opcion =menu()) != 0 )
	{
		switch(opcion)
		{
		 case 1:
		   {
				cout << "Ingrese Numero: ";
				cin >> datos.Numero;
				while(datos.Numero != 0)
				{
					cout<<"Ingrese Nombre: ";
					cin>>datos.nombre;
					cout<<"Ingrese Monto: ";
					cin>>datos.monto;
					datos.sub = NULL ;
					AgregarNodoArbol(raiz,datos);
					cout<<"Ingrese Numero: ";
					cin>>datos.Numero;
				}
				break;
			}   
		case 2:
		  {
		  	MostrarArbol(raiz);
			break;
		  }
		case 3:
		   {
				int nro ;
				cout << "Ingrese Numero de Mes a Buscar: ";
				cin >> nro;
				PuntA aux = BuscarMes(raiz, nro);
				if( aux == NULL)
					cout << "No lo encontro" << endl;
				else
					cout << aux->datos.Numero << " || " << aux->datos.nombre << " || " << aux->datos.monto << endl;
				break;
			}
		case 4:
		   {
		   	  int total = 0 ;
 			  TotalDeMontos(raiz , total);
 			  cout << " Total general de montos " << total << endl;
 			  cout << " Total general de montos V2 " << TotalDeMontosV2(raiz) << endl;
 			  break ;
 		   }
		}
	}
}
	
void AgregarNodoArbol(PuntA & raiz , Datos mes)
{
	PuntA n = new NodoA;
	n->datos = mes;
	n->izq = NULL;
	n->der = NULL;
	
	if(raiz == NULL)
	{
		raiz = n;
        AgregarSub(raiz) ;
	}
	else
	{
		PuntA padre , r ;
		r = raiz;
		while( r != NULL)
		{
			padre = r;
			if(mes.Numero < r->datos.Numero)
				r = r->izq;
			else
				r = r->der;
		}
		if(mes.Numero < padre->datos.Numero)
			padre->izq = n;
		else
			padre->der = n;
		AgregarSub(n) ;	
	}
}

void MostrarArbol(PuntA raiz)
{
	if(raiz != NULL)
	{
		MostrarArbol(raiz->izq);
		cout << raiz->datos.Numero << " || " << raiz->datos.nombre << " || " << raiz->datos.monto << endl;
		
		PuntSub r = raiz->datos.sub ;
		while ( r != NULL ) 
		{
		  cout << "        " << r->datossub.Numero << " || " << r->datossub.letra << endl;
		  r = r->sig ;
		}
		MostrarArbol(raiz->der);
	}
}

void TotalDeMontos(PuntA raiz , int & total)
{
	if(raiz != NULL)
	{
		TotalDeMontos(raiz->izq , total);
		total += raiz->datos.monto ;
		TotalDeMontos(raiz->der , total);
	}
}

int TotalDeMontosV2(PuntA raiz )
{
	static int total = 0 ;
	if(raiz != NULL)
	{
		TotalDeMontosV2(raiz->izq);
		total += raiz->datos.monto ;
		TotalDeMontosV2(raiz->der);
	}
	return total ;
}

                                  
PuntA BuscarMes(PuntA raiz, int nro)
{
	PuntA r = raiz;
	while(r != NULL && r->datos.Numero != nro)
	{
		if(nro < r->datos.Numero)
				r = r->izq;
		else
			r = r->der ;
	}
	return r;
}
	
void AgregarSub(PuntA r)
{
	DatosSub datsub ;
	cout << "           Ingrese Numero sub : ";
	cin >> datsub.Numero;
	while(datsub.Numero != 0)
		{
					cout<<"          Ingrese letra sub : ";
					cin>>datsub.letra;
					
					/*agrega el nodo de la sublista siempre adelante*/
					PuntSub n = new NodoSub ;
					n->datossub = datsub ;
					n->sig = r->datos.sub ;	
					r->datos.sub = n ;
					
	                cout << "           Ingrese Numero sub : ";
					cin>>datsub.Numero;
		}
}
	
int menu(void)
{	
    int opcion ;
	cout << " Menu de opciones    " << endl;
	cout << " 1. Agregar Nodo     " << endl;
	cout << " 2. Mostrar Arbol    " << endl;
	cout << " 3. Buscar Mes       " << endl;
	cout << " 4. Totalizar Montos " << endl;
	cout << " 0. Salir            " << endl;
	cout << " Ingrese opcion      "  ;
	cin >> opcion;
	return opcion;
}
	
