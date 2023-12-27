#include <iostream>
#include <conio.h>
#include <stdio.h> 
#include <string.h>

using namespace std;

// definimos la estructura del registro del archivo Productos y del archivo Precios Cuidados

typedef struct Productos
{
	int codigo;
	char desc[21];
	float precioComercio;
	
}Producto;

typedef struct ProdPreciosCuid
{
	int cod;
	float precioCuidado;
	
}ProdPreciosCuid;

int main ()
{
	Productos prod;
	ProdPreciosCuid precuid;
	int n; 
	int i;
	int j;
	
	FILE*arch=fopen("Productos.dat", "wb");
	if (arch!=NULL)
	{
		cout<<"Ingrese la cantidad de productos del negocio: "<<endl;
		cin>>n;
		
		for(i=0; i<n; i++)
		{
			cout<<"Ingrese el codigo del producto: "<<endl;
			cin>>prod.codigo;
			
			cout<<"Ingrese la descripcion del producto: "<<endl;
			cin>>prod.desc;
			
			cout<<"Ingrese el precio del producto: "<<endl;
			cin>>prod.precioComercio;
			
		}
		fclose(arch);
	}
	else
		cout<<"Error en fopen."<<endl;
		
	FILE*archP=fopen("PreciosCuidados.dat", "wb");	
	if (archP!=NULL)
	{
		cout<<"Ingrese la cantidad de productos en el plan de precios cuidados: "<<endl;
		cin>>j;
		
		for(i=0; i<j; i++)
		{
			cout<<"Ingrese el codigo del producto: "<<endl;
			cin>>precuid.cod;
			
			cout<<"Ingrese el precio cuidado del producto: "<<endl;
			cin>>precuid.precioCuidado;
			
		}
		fclose(archP);
	}
	else
		cout<<"Error en fopen."<<endl;	
		
// hago el listado de productos en comun		
		
	string diferencia;		
	int cont=0;
		
	fopen("PreciosCuidados.dat", "rb");
	fopen("Productos.dat", "rb");
	
	if((arch!=NULL) && (archP!=NULL))
	{
		fread(&prod, sizeof(Productos), 1, arch);
		fread(&precuid, sizeof(ProdPreciosCuid), 1, archP);
		while(!feof(arch) && (!feof(archP)))
		{
			if(prod.codigo==precuid.cod)
			{
				if (prod.precioComercio>precuid.precioCuidado)
				{
					diferencia="positiva";
					
				}else
					{
						if (prod.precioComercio<precuid.precioCuidado)
							diferencia="negativa";
					}
			}else
				cont++;	
		
			cout<<"El producto con codigo "<<prod.codigo<<" se encuentra tambien en el plan de precios cuidados, tiene la descripcion: "<<prod.desc<<" y tiene una diferencia "<<diferencia<<" con respecto al de precios cuidados"<<endl;
			cout<<"La cantidad de productos que estan en el plan de precios cuidados y que el negocio no comercializa es de: "<<cont<<endl;
			
			fread(&prod, sizeof(Productos), 1, arch);
			fread(&precuid, sizeof(ProdPreciosCuid), 1, archP);
			
		}
		fclose(arch);
		fclose(archP);
				
	}else
		cout<<"Error en fopen."<<endl;
			
		
}





