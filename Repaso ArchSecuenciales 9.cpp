#include <iostream>
#include <conio.h>
#include <stdio.h> 
#include <string.h> 

using namespace std;

typedef struct Producto
{
	int codigo;
	char desc[21];
	float precioComercio;
}Producto;

typedef struct ProdPreciosCuid
{
	int codigo;
	float precioCuidado;
}ProdPreciosCuid;

int main ()
{
	Producto unProd;
	ProdPreciosCuid unPre;
	string diferencia;
	int i, n, j, cont=0;
	
	FILE*arch=fopen("Productos.dat", "wb");
	if(arch!=NULL)
	{
		cout<<"Ingrese la cantidad de productos del negocio: "<<endl;
		cin>>n;
		
		for(i=0; i<n; i++)
		{
			cout<<"Ingrese codigo del producto: "<<endl;
			cin>>unProd.codigo;
			
			cout<<"Ingrese la descripcion del producto: "<<endl;
			cin>>unProd.desc;
			
			cout<<"Ingrese el precio de comercio del producto: "<<endl;
			cin>>unProd.precioComercio;
			
			fwrite(&arch, sizeof(Producto), 1, arch);
		}
		fclose(arch);
	}
	else
		cout<<"Error en fopen."<<endl;
		
	FILE*archi=fopen("PreciosCuidados.dat", "wb");
	if(archi!=NULL)
	{
		cout<<"Ingrese la cantidad de productos con precios cuidados: "<<endl;
		cin>>j;
		
		for(i=0; i<j; i++)
		{
			cout<<"Ingrese codigo del producto: "<<endl;
			cin>>unPre.codigo;
			
			cout<<"Ingrese el precio cuidado del producto: "<<endl;
			cin>>unPre.precioCuidado;
			
			fwrite(&archi, sizeof(ProdPreciosCuid), 1, archi);
		}
		fclose(archi);
	}
	else
		cout<<"Error en fopen."<<endl;
		
	fopen("Productos.dat", "rb");
	fopen("PreciosCuidados.dat", "rb");
	
	if((arch!=NULL) && (archi!=NULL))
	{
		fread(&arch, sizeof(Producto), 1, arch);
		fread(&archi, sizeof(ProdPreciosCuid), 1, archi);
		
		while((!feof(arch)) && (!feof(archi)))
		{
			if(unProd.codigo==unPre.codigo)
			{
				if(unProd.precioComercio>unPre.precioCuidado)
					diferencia="positiva";
				else
				{
					if(unProd.precioComercio<unPre.precioCuidado)
						diferencia="negativa";
				}
			}
			else
				cont++;	
			
			
			cout<<"El producto con codigo "<<unProd.codigo<<" se encuentra tambien en el plan de precios cuidados, tiene la descripcion: "<<unProd.desc<<" y tiene una diferencia "<<diferencia<<" con respecto al de precios cuidados"<<endl;
			cout<<"La cantidad de productos que estan en el plan de precios cuidados y que el negocio no comercializa es de: "<<cont<<endl;
			
		}
		fclose(arch);
		fclose(archi);
	}
	else
		cout<<"Error en fopen."<<endl;
}
