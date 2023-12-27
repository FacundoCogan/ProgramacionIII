#include <iostream>

using namespace std;

//Estructura de los archivos
typedef struct VentasDiaArch
{
	int nroVen;
	int cantTotal;
	float importeTotal;
}VentasDiaArch;

typedef struct VentasOrdArch
{
	int nroVen;
	int cantTotal;
	float importeTotal;
}VentasOrdArch;

//Estructura del arbol

typedef struct Venta
{
	int nroVendedor;
	int nroFactura;
	float importe; 
	
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
void arbolXImporte(PuntA &raiz, Venta);
void generarArchivoOrd(PuntA &raiz);

//Funcion principal del programa
int main ()
{
	PuntA raiz=NULL;
	Venta datos;
	
	cout<<"Ingrese numero de vendedor que hizo la venta: "<<endl;
	cin>>datos.nroVendedor;
	while(datos.nroVendedor!=0)
	{
		cout<<"Ingrese numero de factura: "<<endl;
		cin>>datos.nroFactura;
		
		cout<<"Ingrese importe de la venta: "<<endl;
		cin>>datos.importe;
		
		agregarNodoArbol(raiz, datos);
		
		cout<<"Ingrese numero de vendedor que hizo la venta: "<<endl;
		cin>>datos.nroVendedor;
	}
	
	generarArchivo(raiz);
	
	arbolXImporte(raiz, datos);
	generarArchivoOrd(raiz);
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
	}
	else
	{
		PuntA padre , r ;
		r = raiz;
		while( r != NULL)
		{
			padre = r;
			if(datos.nroVendedor < r->datos.nroVendedor)
				r = r->izq;
			else
				r = r->der;
		}
		if(datos.nroVendedor < padre->datos.nroVendedor)
			padre->izq = n;
		else
			padre->der = n;
	}	
}


void generarArchivo(PuntA &raiz)
{
	FILE*arch=fopen("VentasDia.dat", "wb");
	if(arch!=NULL)
	{
		int cantVentas=0;
		VentasDiaArch venArch;
		if(raiz != NULL)
		{
			generarArchivo(raiz->izq);
			cantVentas++;
			venArch.nroVen=raiz->datos.nroVendedor;
			venArch.importeTotal = venArch.importeTotal + raiz->datos.importe;
			venArch.cantTotal=cantVentas;
		
			fwrite(&venArch, sizeof(VentasDiaArch), 1, arch);
			generarArchivo(raiz->der);
		}
	}
}

void generarArbolXImporte(PuntA &raiz, Venta ven)
{
	FILE*arch=fopen("VentasDia.dat", "rb");
	if(arch!=NULL)
	{
		VentasDiaArch venArch;
	
		fread(&venArch, sizeof(VentasDiaArch), 1, arch);
		while(!feof(arch))
		{
			ven.importe=venArch.importeTotal;
			ven.nroVendedor=venArch.nroVen;
		
			arbolXImporte(raiz, ven);
			fread(&venArch, sizeof(VentasDiaArch), 1, arch);
		}
	}
}

void arbolXImporte(PuntA & raiz, Venta datos)
{
	PuntA n = new NodoA;
	n->datos = datos;
	n->izq = NULL;
	n->der = NULL;
	
	if(raiz == NULL)
	{
		raiz = n;
	}
	else
	{
		PuntA padre , r ;
		r = raiz;
		while( r != NULL)
		{
			padre = r;
			if(datos.importe > r->datos.importe)
				r = r->izq;
			else
				r = r->der;
		}
		if(datos.importe > padre->datos.importe)
			padre->izq = n;
		else
			padre->der = n;
	}	
}

void generarArchivoOrd(PuntA &raiz)
{
	FILE*arch=fopen("VentasOrd.dat", "wb");
	if(arch!=NULL)
	{
		int cantVentas=0;
		VentasOrdArch ordArch;
		if(raiz != NULL)
		{
			generarArchivo(raiz->izq);
			cantVentas++;
			ordArch.nroVen=raiz->datos.nroVendedor;
			ordArch.importeTotal = ordArch.importeTotal + raiz->datos.importe;
			ordArch.cantTotal=cantVentas;
		
			fwrite(&ordArch, sizeof(VentasOrdArch), 1, arch);
			generarArchivo(raiz->der);
		}
	}
}
