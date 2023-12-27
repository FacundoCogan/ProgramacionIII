#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <string.h>

#define CANTINSCRIPTOS 10

using namespace std;

//Definición de cola
typedef struct TDato
{
	char dest;
	int nroSocio;
	char nombre[25];
	int cantPersonas;
 //completar
}TDato;

typedef struct NodoCola * PuntCola;

typedef struct NodoCola
{
	TDato info;
	PuntCola sig;
}NodoCola;

typedef struct Cola
{
	PuntCola ent,sal;
}Cola;

//agregar definición de structs necesarias
typedef struct ArchDire
{
	int nroSocio;
	char nombre[25];
	int cant;
}ArchDire;

typedef struct ArchSecu
{
	int nroSocio;
	char nombre[25];
}ArchSecu;

//Prototipos de Cola
void inicializar(Cola &);
int vacia(Cola);
void poner(Cola &, TDato);
void sacar(Cola &, TDato &);
void ver(Cola , TDato &);

//agregar prototipos necesarios
int hashing(int);
void procesarCola(Cola &, Cola &, Cola &);
void generarArchVacio(char []);
void generarArchDire(Cola &, char[]);
void generarArchSecu(Cola &);
void diferenciarCola(Cola &, Cola &, Cola &, int &, int &, TDato&);

int main()
{
	Cola cola, colaC, colaS;
	inicializar(cola);
	inicializar(colaC);
	inicializar(colaS);
	TDato info;
	char resp;
	
	do
	{
	    cout<<"Ingrese destino:"<<endl;
	    cout<<"     C: Costa Atlantica"<<endl;
	    cout<<"     S: Sierras de Cordoba"<<endl;
	    cin>>info.dest;
	    cout<<"Ingrese numero de socio: "<<endl;
	    cin>>info.nroSocio;
	    cout<<"Ingrese nombre del socio: "<<endl;
	    cin>>info.nombre;
	    cout<<"Ingrese cantidad de pasajeros: "<<endl;
	    cin>>info.cantPersonas;
	
		poner(cola, info);
	    //agregar código

	    cout<<"Continua con la inscripcion de socios para realizar viaje? (S o N) ";
	    cin>>resp;
	}while(resp=='S'|| resp=='s');
		//agregar código
		
	procesarCola(cola, colaC, colaS);	
	generarArchVacio("CostaAtl.dat");
	generarArchVacio("Cordoba.dat");
	generarArchDire(colaC, "CostaAtl.dat");
	generarArchDire(colaS, "Cordoba.dat");
	generarArchSecu(cola);
	
	 system("pause");
	 return 0;
}

// Funciones de cola

void inicializar(Cola & c)
{
	c.ent = NULL;
  	c.sal = NULL;
}

int vacia(Cola c)
{
	return c.ent == NULL && c.sal == NULL;
}

void poner(Cola & c, TDato dato)
{
	PuntCola n;
  	n = new NodoCola;
  	n->info = dato;
  	n->sig  = NULL;
  	if (c.ent == NULL)
    	c.sal = n;
  	else
    	c.ent->sig = n;
  	c.ent = n;
}

void sacar(Cola & c, TDato & dato)
{
  	if (!vacia(c))
  	{
  		PuntCola n;
    	n = c.sal;
    	dato = n->info;
    	c.sal = n->sig;
    	delete n;
    	if (c.sal == NULL)
      	c.ent = NULL;
  	}
}

void ver(Cola c, TDato & dato)
{
  	if (!vacia(c))
   	dato = c.sal->info;
}

//agregar definición de funciones necesarias
int hashing (int codigo)
{
	return (codigo % CANTINSCRIPTOS);
}

void procesarCola(Cola &cola, Cola &colaC, Cola &colaS)
{
	TDato info;
	int dispoC, dispoS;
	
	cout<<"Ingrese disponibilidad de vuelo a Costa Atlantica: "<<endl;
	cin>>dispoC;
	
	cout<<"Ingrese disponibilidad de vuelo a Sierras de Cordoba: "<<endl;
	cin>>dispoS;
	
	int primero;
	if(!vacia(cola))
	{
		sacar(cola, info);
		primero=info.nroSocio;
		diferenciarCola(cola, colaC, colaS, dispoC, dispoS, info);
		while(info.nroSocio!=primero && !vacia(cola))
		{
			diferenciarCola(cola, colaC, colaS, dispoC, dispoS, info);
		}
	}
}

void generarArchVacio(char nomArch[])
{
	FILE*arch=fopen(nomArch, "wb");
	if (arch!=NULL)
	{
		ArchDire dire;
		int i;
		dire.cant=0;
		strcpy(dire.nombre,".........................");
		dire.nroSocio=0;
		
		for (i=0; i<CANTINSCRIPTOS; i++)
		{
			fwrite(&dire, sizeof(ArchDire), 1, arch);
		}
		fclose(arch);
	}
	else
		cout<<"Error en fopen."<<endl;
}

void generarArchDire(Cola &cola, char nomArch[]) 
{
	FILE*arch=fopen(nomArch, "rb+");
	if(arch!=NULL)
	{
		TDato info;
		ArchDire dire;
		
		ver(cola, info);
		while(!vacia(cola))
		{
			fseek(arch,hashing(dire.nroSocio)*sizeof(ArchDire),SEEK_SET);
	        fread(&dire,sizeof(ArchDire),1,arch);
	        if(info.nroSocio==dire.nroSocio) // lo encontre en el area de hashing
	        {
	            dire.cant++;
	            dire.nroSocio=info.nroSocio;
	            strcpy(dire.nombre,info.nombre);
	            
	            fseek(arch,-sizeof(ArchDire),SEEK_CUR);
	            fwrite(&dire,sizeof(ArchDire),1,arch); 
	        }
	
	        else // lo voy a buscar al area de rebalse
	        {
	            fseek(arch, 0, 2);
	            fread(&dire,sizeof(ArchDire),1,arch);
	            while(!feof(arch) && info.nroSocio!=dire.nroSocio)
	                fread(&dire,sizeof(ArchDire),1,arch);
	            if(feof(arch))
	                cout<<dire.nroSocio<<" no existe"<<endl;
	            else
	            {
	                dire.cant++;
	            	dire.nroSocio=info.nroSocio;
	            	strcpy(dire.nombre,info.nombre);
	            	
	                fseek(arch,-sizeof(ArchDire),SEEK_CUR);
	                fwrite(&dire,sizeof(ArchDire),1,arch);   
	            }
	        }
	        ver(cola, info);
		}
		fclose(arch);
	}
	else
		cout<<"Error en fopen."<<endl;
}

void generarArchSecu(Cola &cola)
{
	FILE*archi=fopen("ColaCosta.dat", "wb");
	FILE*archivo=fopen("ColaCord.dat", "wb");
	if(archi!=NULL && archivo!=NULL)
	{
		TDato info;
		ArchSecu secu;
		
		ver(cola, info);
		while(!vacia(cola))
		{
			if(info.dest=='c')
			{
				secu.nroSocio=info.nroSocio;
				strcpy(secu.nombre,info.nombre);
				fwrite(&secu, sizeof(ArchSecu), 1, archi);
			}
			if(info.dest=='s')
			{
				secu.nroSocio=info.nroSocio;
				strcpy(secu.nombre,info.nombre);
				fwrite(&secu, sizeof(ArchSecu), 1, archivo);
			}
			sacar(cola, info);
			ver(cola, info);
		}
	}
}

void diferenciarCola(Cola &cola, Cola &colaC, Cola &colaS, int &dispoC, int &dispoS, TDato &info)
{
	if(info.dest=='c' && dispoC>0)
		{
			sacar(cola, info);
			poner(colaC, info);
			dispoC--;
		}
		if(info.dest=='s' && dispoS>0)
		{
			sacar(cola, info);
			poner(colaS, info);
			dispoS--;
		}
		ver(cola, info);
}
