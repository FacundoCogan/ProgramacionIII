#include <iostream>

using namespace std;

//Estructura del arbol
typedef struct Inscripto
{
	int dni;
	char nombreApe[25]; 
	int cp;
	
}Inscripto;

typedef struct NodoA * PuntA;
typedef struct NodoA
{
	Inscripto datos;
	PuntA izq;
	PuntA der;
}NodoA;

//Prototipos
void agregarNodoArbol(PuntA & raiz, Inscripto);
void generarArchivo(PuntA &raiz);

//Funcion principal del programa
int main ()
{
	PuntA raiz=NULL;
	Inscripto datos;
	
	cout << "Ingrese dni: "<<endl;
	cin >> datos.dni;
	while(datos.dni != 0)
	{
		cout<<"Ingrese nombre y apellido: "<<endl;
		cin>>datos.nombreApe;
					
		cout<<"Ingrese codigo postal de la localidad donde reside: "<<endl;
		cin>>datos.cp;
		
		agregarNodoArbol(raiz, datos);
		
		cout << "Ingrese dni: "<<endl;
		cin >> datos.dni;
	}
	
	generarArchivo(raiz);
}

//Funciones
void agregarNodoArbol(PuntA & raiz, Inscripto datos)
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
			if(datos.dni< r->datos.dni)
				r = r->izq;
			else
				r = r->der;
		}
		if(datos.dni < padre->datos.dni)
			padre->izq = n;
		else
			padre->der = n;
	}	
}

void generarArchivo(PuntA &raiz)
{
	FILE*arch=fopen("RegistroVacunas.dat", "wb");
	if(arch!=NULL)
	{
		Inscripto datos;
		if(raiz != NULL)
		{
			generarArchivo(raiz->izq);
			
			if(raiz->datos.dni!=datos.dni)
				fwrite(&datos, sizeof(Inscripto), 1, arch);
			
			generarArchivo(raiz->der);
		}
		fclose(arch);
	}
	else
		cout<<"Error en fopen"<<endl;
}
