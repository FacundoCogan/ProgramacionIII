#include <iostream>
#include <string.h>
#include <conio.h>
#include <stdio.h>

using namespace std;

//definición de struct para "Paquetes.dat"
typedef struct RegPaquete
{
	int codPaq;
	char descr[46];
	int cant=0;
}RegPaquete;
//definición de struct para "Pasajeros.dat"
typedef struct RegPasaj
{
	int dni;
	char nombre[21];
    int codPaq;
}RegPasaj;
//definición sublista
typedef struct TDatoLista
{
	int dni;
	char nombre[21];
}TDatoLista;
typedef struct NodoLista * PuntLista;
typedef struct NodoLista
{
	TDatoLista info;
	PuntLista sig;
}NodoLista;
//definición árbol de paquetes
typedef struct TDatoArbol
{
	int codPaq;
	PuntLista priPasaj;
}TDatoArbol;
typedef struct NodoArbol * PuntArbol;
typedef struct NodoArbol
{
	TDatoArbol info;
	PuntArbol izq, der;
}NodoArbol;
//Prototipos de funciones de Lista
void agregar(PuntLista &, TDatoLista);
void mostrar(PuntLista);
int contar(PuntLista);
//Prototipos de funciones de Arbol
void buscarAgregar(PuntArbol &, int, PuntArbol &);
void generarArbolYSubLista(PuntArbol &);
void actualizarArchivo(PuntArbol, FILE*);
void listar(PuntArbol);
//funcion de hashing para acceder al archivo directo
int hashing(int);

int main()
{
	PuntArbol raiz=NULL;
	FILE*a=fopen("Paquetes.dat", "rb+");
	
	generarArbolYSubLista(raiz);
	actualizarArchivo(raiz, a);
	listar(raiz);

    return 0;
}
//Funciones de lista simple
void agregar(PuntLista & pri, TDatoLista dato)
{
     //inserta un pasajero en la lista ordenada por dni
   PuntLista r, ant, n;
   r = pri;
   n = new NodoLista;
   n->info = dato;
   while (r!= NULL && r->info.dni < dato.dni)
   {
      ant = r;
      r = r->sig;
   }
   n->sig = r;
   if(r == pri)
   	pri = n;
   else
   	ant->sig = n;
}

void mostrar(PuntLista pri)
{
   //muestra los elementos de la lista de personas
   PuntLista r;
   r = pri;
   while (r!= NULL)
   {
      cout<<r->info.dni<<" - "<<r->info.nombre<<endl;
      r = r->sig;
   }
 }
int contar(PuntLista pri)
{
   //devuelve la cantidad de elementos de la lista
   PuntLista r;
   int cont=0;
   r = pri;
   while (r!= NULL)
   {
      cont++;
      r = r->sig;
   }
   return cont;
 }


//Funciones de árbol
void buscarAgregar(PuntArbol & raiz, int unCod, PuntArbol & r)
{
   //Devuelve el puntero al nodo correspondiente al paquete con código igual a unCod
   //Si el paquete no está en el árbol, agrega el nodo y devuelve su puntero
   PuntArbol ant;
   r = raiz;
   while (r!=NULL && r->info.codPaq != unCod)
   {
      ant = r;
      if(unCod < r->info.codPaq)
      	r = r->izq;
      else
      	r = r->der;
   }
   if(r == NULL)
   {
   	r = new NodoArbol;
   	r->info.codPaq = unCod;
   	r->info.priPasaj = NULL;
   	r->izq = r->der = NULL;
   	if(raiz == NULL)
   		raiz = r;
    else
   	{
   		if(unCod < ant->info.codPaq)
      		ant->izq = r;
      	else
      		ant->der = r;
     }
   }
}
//función de hashig
int hashing(int clave)
{
    return clave % 10;
}

void generarArbolYSubLista(PuntArbol &raiz)
{
	FILE*arch=fopen("Pasajeros.dat", "rb");
	if(arch!=NULL)
	{
		RegPasaj pasaj;
		PuntArbol r=raiz;
		TDatoLista info;
		
		fread(&pasaj, sizeof(RegPasaj), 1, arch);
		while(!feof(arch))
		{
			buscarAgregar(raiz, pasaj.codPaq, r);
			info.dni=pasaj.dni;
			strcpy(info.nombre,pasaj.nombre);
			agregar(r->info.priPasaj, info);
			fread(&pasaj, sizeof(RegPasaj), 1, arch);
		}
		fclose(arch);
	}
	else
		cout<<"Error en fopen."<<endl;
}

void actualizarArchivo(PuntArbol raiz, FILE*a)
{
	if(a!=NULL)
	{
		RegPaquete paq;
		
		if(raiz!=NULL)
		{
			actualizarArchivo(raiz->izq, a);
			
			fseek(a,hashing(paq.codPaq)*sizeof(RegPaquete),SEEK_SET);
	        fread(&paq,sizeof(RegPaquete),1,a);
	        if(raiz->info.codPaq==paq.codPaq) // lo encontre en el area de hashing
	        {
	            paq.cant=contar(raiz->info.priPasaj);
	            fseek(a,-sizeof(RegPaquete),SEEK_CUR);
	            fwrite(&paq,sizeof(RegPaquete),1,a); 
	        }
	
	        else // lo voy a buscar al area de rebalse
	        {
	            fseek(a, 0, 2);
	            fread(&paq,sizeof(RegPaquete),1,a);
	            while(!feof(a) && raiz->info.codPaq!=paq.codPaq)
	                fread(&paq,sizeof(RegPaquete),1,a);
	            if(feof(a))
	                cout<<paq.codPaq<<" no existe"<<endl;
	            else
	            {
	                paq.cant=contar(raiz->info.priPasaj);
	                fseek(a,-sizeof(RegPaquete),SEEK_CUR);
	                fwrite(&paq,sizeof(RegPaquete),1,a); 
	            }
	        }
			actualizarArchivo(raiz->der, a);
		}
		fclose(a);
	}
	else
		cout<<"Error en fopen."<<endl;
}

void listar(PuntArbol raiz)
{
	if(raiz!=NULL)
	{
		listar(raiz->izq);
		
		cout<<"Codigo: "<<raiz->info.codPaq<<endl;
		mostrar(raiz->info.priPasaj);
		
		listar(raiz->der);
	}
}
