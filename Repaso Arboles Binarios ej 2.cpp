#include <iostream>

using namespace std;

//Estructura del archivo a generar
typedef struct VentasDiaArch
{
	int nroVen;
	int cantTotal;
	float importeTotal;
}VentasDiaArch;

//Estructura del arbol y su sublista
typedef struct SubLista
{
	int nroFactura;
	float importe; 
}SubLista;

typedef struct NodoSub * PuntSub;
typedef struct NodoSub
{
	SubLista datosSub;
	PuntSub sig;
}NodoSub;

typedef struct Venta
{
	int nroVendedor;
	PuntSub listaSub;
	
}Venta;

typedef struct NodoA * PuntA;
typedef struct NodoA
{
	Venta datos;
	PuntA izq;
	PuntA der;
}NodoA;

//Prototipos
void agregarNodoArbol(PuntA & raiz, Venta);
void agregarSub(PuntA);
void generarArchivo(PuntA &raiz);

//Funcion principal del programa
int main ()
{
	PuntA raiz=NULL;
	Venta datos;
	SubLista datosSub;
	
	cout<<"Ingrese numero de vendedor que hizo la venta: "<<endl;
	cin>>datos.nroVendedor;
	while(datos.nroVendedor!=0)
	{
		agregarNodoArbol(raiz, datos);
		
		cout<<"Ingrese numero de vendedor que hizo la venta: "<<endl;
		cin>>datos.nroVendedor;
	}
	
	generarArchivo(raiz);
}

//Funciones
void agregarNodoArbol(PuntA & raiz, Venta datos)
{
	PuntA n = new NodoA;
	n->datos = datos;
	n->izq = NULL;
	n->der = NULL;
	
	if(raiz == NULL)
	{
		raiz = n;
		agregarSub(raiz);
	}
	else
	{
		PuntA padre , r ;
		r = raiz;
		while( r != NULL)
		{
			padre = r;
			if(datos.nroVendedor< r->datos.nroVendedor)
				r = r->izq;
			else
				r = r->der;
		}
		if(datos.nroVendedor < padre->datos.nroVendedor)
			padre->izq = n;
		else
			padre->der = n;
		agregarSub(n);
	}	
}

void agregarSub(PuntA r)
{
	SubLista datosSub;
	
	cout<<"Ingrese numero de factura: "<<endl;
	cin>>datosSub.nroFactura;
	while(datosSub.nroFactura!=0)
	{
		cout<<"Ingrese importe de la venta: "<<endl;
		cin>>datosSub.importe;
		
		/*agrega el nodo de la sublista siempre adelante*/
		PuntSub n = new NodoSub ;
		n->datosSub = datosSub ;
		n->sig = r->datos.listaSub ;	
		r->datos.listaSub = n ;	
		
		cout<<"Ingrese numero de factura: "<<endl;
		cin>>datosSub.nroFactura;
	}		
}

void generarArchivo(PuntA &raiz)
{
	FILE*arch=fopen("VentasDia.dat", "wb");
	if(arch!=NULL)
	{
		VentasDiaArch venArch;
		if(raiz != NULL)
		{
			int cantVentas=0;
			
			generarArchivo(raiz->izq);
			venArch.nroVen=raiz->datos.nroVendedor;
			
			PuntSub r = raiz->datos.listaSub ;
			while ( r != NULL ) 
			{
				cantVentas++;
		 		r = r->sig;
			}
			venArch.importeTotal = venArch.importeTotal + r->datosSub.importe;
			venArch.cantTotal=cantVentas;
			fwrite(&venArch, sizeof(VentasDiaArch), 1, arch);
			generarArchivo(raiz->der);
		}
	}
}
