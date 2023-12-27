#include <iostream>
#include <stdio.h>

using namespace std;

typedef struct TRegCuota
{
        int codCli;
        int cuota; //1 a 5
}TRegCuota;

typedef struct TRegCli
{
        int codCli;
        char nombre[31];
        long dni;
}TRegCli;

typedef struct TDatoLista
{
        int codCli;
        int cuotas;
}TDatoLista;
typedef struct Nodo * Punt;
typedef struct Nodo
{
        TDatoLista info;
        Punt sig;
}Nodo ;


void armarLista(Punt &); //Genera la lista con los datos de "CuotasPagas.dat"
void buscarInsertar(Punt &,TDatoLista,Punt &); //hecho
void actualizarArchivo(Punt); //Elimina los clientes que cancelaron el préstamo de "Prestamos.dat"
void listar(Punt); //hecho
void mostrar(TDatoLista); //Muestra TDatoList: codCli y cuotas

int hashing(int);

int main()
{
	Punt pri=NULL;
	
	armarLista(pri);
	actualizarArchivo(pri);
	listar(pri);

  return 0;
}

// ------------------- FUNCIONES DADAS POR EL EJERCICIO -------------------

void buscarInsertar(Punt & pri,TDatoLista dato,Punt & p)
{
     //Devuelve en p la drección de memoria del nodo que tenga el código de cliente correspondiente al de dato
     //si no está lo agrega y devuelve la dirección de memoria del nodo agregado
     Punt ant, r = pri;
     while(r!=NULL && r->info.codCli < dato.codCli)
     {
                   ant=r;
                   r=r->sig;
     }
     if(r!=NULL && r->info.codCli==dato.codCli)
                p=r;
     else
     {
         p=new Nodo;
         p->info=dato;
         p->sig = r;
         if(r == pri)
   	          pri = p;
         else
   	         ant->sig = p;

     }
}

void listar(Punt pri)
{
     //Lista los clientes que todabía adeudan cuotas
     Punt r=pri;
     while(r!=NULL)
     {
          mostrar(r->info);
          r=r->sig;
     }
}

int hashing(int clave)
{
    return clave % 10;
}

// ------------------- FUNCIONES HECHAS POR MI -------------------

void armarLista(Punt & pri) //Genera la lista con los datos de "CuotasPagas.dat"
{
	FILE*arch=fopen("CuotasPagas.dat", "rb");
	if(arch!=NULL)
	{
		TRegCuota cuota;
		TDatoLista info;
		Punt p=pri;
		fread(&cuota, sizeof(TRegCuota), 1, arch);
		while(!feof(arch))
		{
			info.codCli=cuota.codCli;
			buscarInsertar(pri, info, p);
			p->info.cuotas++;
			fread(&cuota, sizeof(TRegCuota), 1, arch);
		}
		fclose(arch);
	}
	else
		cout<<"Error en fopen."<<endl;
}

void actualizarArchivo(Punt pri) //Elimina los clientes que cancelaron el préstamo de "Prestamos.dat"
{
	FILE*archi=fopen("Prestamos.dat", "rb+");
	if(archi!=NULL)
	{
		TRegCli cli;
		Punt r=pri; 
	    
	    while (r!=NULL) 
	    {
	        fseek(archi,hashing(cli.codCli)*sizeof(TRegCli),SEEK_SET);
	        fread(&cli,sizeof(TRegCli),1,archi);
	        if(r->info.codCli==cli.codCli) // lo encontre en el area de hashing
	        {
	            if(r->info.cuotas==5)
	            	cli.codCli=0;
	            fseek(archi,-sizeof(TRegCli),SEEK_CUR);
	            fwrite(&cli,sizeof(TRegCli),1,archi); 
	        }
	
	        else // lo voy a buscar al area de rebalse
	        {
	            fseek(archi, 0, 2);
	            fread(&cli,sizeof(TRegCli),1,archi);
	            while(!feof(archi) && r->info.codCli!=cli.codCli)
	                fread(&cli,sizeof(TRegCli),1,archi);
	            if(feof(archi))
	                cout<<cli.codCli<<" no existe"<<endl;
	            else
	            {
	                if(r->info.cuotas==5)
	            		cli.codCli=0;
	                fseek(archi,-sizeof(TRegCli),SEEK_CUR);
	                fwrite(&cli,sizeof(TRegCli),1,archi); 
	            }
	        }
	        r=r->sig;
	    }
	    fclose(archi);
	}
	else
		cout<<"Error en fopen."<<endl;
}

void mostrar(TDatoLista info) //Muestra TDatoList: codCli y cuotas
{
	cout<<"Codigo: "<<info.codCli<<" Cuotas: "<<info.cuotas<<endl;
}
