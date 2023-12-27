#include <iostream>

#define CANTLOCALIDADES 10

using namespace std;

//Estructura del archivo de acceso directo
typedef struct LocalidadesArch
{
	int cp;
	char localidad[25];
	int cantRegistrados;
}LocalidadesArch;

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
int hashing(int);
void agregarNodoArbol(PuntA &, Inscripto);
void generarArchivo(PuntA &);
void generarArbol(PuntA &);
void agregarNodoArbolLocalidades(PuntA &, Inscripto);
void actualizarArch(PuntA &);

//Funcion principal del programa
int main ()
{
	PuntA raiz=NULL;
	Inscripto datos;
	int unCp;
	
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
	
	//ej 1
	generarArchivo(raiz);
	
	//ej 4
	generarArbol(raiz);
	actualizarArch(raiz);
}

//Funciones
int hashing(int codigo)
{
	return (codigo % CANTLOCALIDADES);
}

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

void generarArbol(PuntA &raizL)
{
	FILE*arch=fopen("RegistroVacunas.dat", "rb");
	if(arch!=NULL)
	{
		Inscripto datos;
		
		fread(&datos, sizeof(Inscripto), 1, arch);
		while(!feof(arch))
		{
			agregarNodoArbolLocalidades(raizL, datos);
			fread(&datos, sizeof(Inscripto), 1, arch);
		}
	}
}

void agregarNodoArbolLocalidades(PuntA & raizL, Inscripto datos)
{
	PuntA n = new NodoA;
	n->datos = datos;
	n->izq = NULL;
	n->der = NULL;
	
	if(raizL == NULL)
	{
		raizL = n;
	}
	else
	{
		PuntA padre , r ;
		r = raizL;
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

void actualizarArch(PuntA &raizL)
{
    FILE*archL=fopen("Localidades.dat","rb+");
    if(archL!=NULL)
    {
    	if(raizL!=NULL)
    	{
    		LocalidadesArch locArch;
    		int cantRegistrados=0;
    		
    		actualizarArch(raizL->izq);
	        
	        fseek(archL,hashing(locArch.cp)*sizeof(LocalidadesArch),SEEK_SET);
	        fread(&locArch,sizeof(LocalidadesArch),1,archL);
	        if(raizL->datos.cp==locArch.cp) // lo encontre en el area de hashing
	        {
	        	cantRegistrados++;
	        	locArch.cp=raizL->datos.cp;
	        	locArch.cantRegistrados=cantRegistrados;
	            fseek(archL,-sizeof(LocalidadesArch),SEEK_CUR);
	            fwrite(&locArch,sizeof(LocalidadesArch),1,archL); 
	        }
	
	        else // lo voy a buscar al area de rebalse
	        {
	            fseek(archL, 0, 2);
	            fread(&locArch,sizeof(LocalidadesArch),1,archL);
	            while(!feof(archL) && raizL->datos.cp!=locArch.cp)
	                fread(&locArch,sizeof(LocalidadesArch),1,archL);
	            if(feof(archL))
	                cout<<locArch.cp<<" no existe"<<endl;
	            else
	            {
	                cantRegistrados++;
	        		locArch.cp=raizL->datos.cp;
	        		locArch.cantRegistrados=cantRegistrados;
	                fseek(archL,-sizeof(LocalidadesArch),SEEK_CUR);
	                fwrite(&locArch,sizeof(LocalidadesArch),1,archL);
	            }
	
	        }
	        actualizarArch(raizL->der);
	    }
	}	fclose(archL);
}

