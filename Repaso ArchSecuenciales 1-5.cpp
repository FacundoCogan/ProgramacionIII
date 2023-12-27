#include <iostream>
#include <conio.h>
#include <stdio.h> 
#include <string.h> 

using namespace std;

typedef struct Producto{
	int cod;
	char desc[50];
	int stock;
	float precio;
}Producto;

//Prototipos
int menu();
void crearArchProd(Producto);
void leerArch();
void generarArchRepo(Producto);
void cambiarUnPrecio(Producto);
void cambiarVariosPrecios(Producto);

//Funcion principal del programa
int main ()
{
	int opcion;
	Producto prod;
	
	while ((opcion=menu())!=0)
	{
		switch(opcion)
		{
			case 1: crearArchProd(prod);
			
			case 2: leerArch();
			
			case 3: generarArchRepo(prod);
			
			case 4: cambiarUnPrecio(prod);
			
			case 5: cambiarVariosPrecios(prod);
		}
	}
}

//Funciones
//1
void crearArchProd(Producto prod)
{
	FILE*arch=fopen("Productos.dat", "ab");
	if(arch!=NULL)
	{
		cout<<"Ingrese codigo del producto a ingresar: "<<endl;
		cin>>prod.cod;
		
		while(prod.cod!=0)
		{
			cout<<"Ingrese descripcion: "<<endl;
			cin>>prod.desc;
			
			cout<<"Ingrese stock: "<<endl;
			cin>>prod.stock;
			
			cout<<"Ingrese precio: "<<endl;
			cin>>prod.precio;
			
			fwrite(&prod, sizeof(Producto), 1, arch);
		}
		fclose(arch);
	}
	else
		cout<<"Error en fopen."<<endl;
}

//2
void leerArch()
{
	FILE*arch=fopen("Productos.dat", "rb");
	if(arch!=NULL)
	{
		Producto prod;
		fread(&arch, sizeof(Producto), 1, arch);
		while(!feof(arch))
		{
			cout<<"El producto con codigo "<<prod.cod<<" tiene la descripcion: "<<prod.desc<<", un stock de "<<prod.stock<<" unidades, y un precio de $"<<prod.precio<<endl;
			fread(&arch, sizeof(Producto), 1, arch);
		}
		fclose(arch);
	}
	else
		cout<<"Error en fopen."<<endl;
}

//3
void generarArchRepo(Producto prod)
{
	FILE*archR=fopen("Reposicion.dat", "wb");
	FILE*arch=fopen("Productos.dat", "rb");
	
	if((arch!=NULL) && (archR!=NULL))
	{
		fread(&arch, sizeof(Producto), 1, arch);
		while(!feof(arch))
		{
			if(prod.stock==0)
				fwrite(&prod, sizeof(Producto), 1, archR);
			fread(&arch, sizeof(Producto), 1, arch);
		}
		fclose(arch);
		fclose(archR);
	}
	else
		cout<<"Error en fopen."<<endl;
}

//4
void cambiarUnPrecio(Producto prod)
{
	FILE*arch=fopen("Productos.dat", "rb+");
	if(arch!=NULL)
	{
		int unCod;
		cout<<"Ingresar codigo de producto con precio a modificar: "<<endl;
		cin>>unCod;
		
		fread(&arch, sizeof(Producto), 1, arch);
		while(!feof(arch) && (prod.cod!=unCod))
		{
			fread(&arch, sizeof(Producto), 1, arch);
		}
		if(feof(arch))
			cout<<"No se encontro el codigo de producto"<<endl;
		else
		{
			cout<<"El producto con codigo "<<prod.cod<<" tiene un precio de: $"<<prod.precio<<endl;
			float nuevoPrecio;
			cout<<"El nuevo precio sera de: $"<<endl;
			cin>>nuevoPrecio;
			
			prod.precio=nuevoPrecio;
			fseek(arch, -sizeof(Producto), 1);
			fwrite(&prod, sizeof(Producto), 1, arch);
		}
		fclose(arch);
	}
	else
		cout<<"Error en fopen."<<endl;
}

//5
void cambiarVariosPrecios(Producto prod)
{
	FILE*arch=fopen("Productos.dat", "rb+");
	if(arch!=NULL)
	{
		int unCod;
		cout<<"Ingresar codigo de producto con precio a modificar (0 para fin de ingreso de codigos): "<<endl;
		cin>>unCod;
		
		while(unCod!=0)
		{
			fread(&arch, sizeof(Producto), 1, arch);
			while(!feof(arch) && (prod.cod!=unCod))
			{
				fread(&arch, sizeof(Producto), 1, arch);
			}
			if(feof(arch))
				cout<<"No se encontro el codigo de producto"<<endl;
			else
			{
				cout<<"El producto con codigo "<<prod.cod<<" tiene un precio de: $"<<prod.precio<<endl;
				float nuevoPrecio;
				cout<<"El nuevo precio sera de: $"<<endl;
				cin>>nuevoPrecio;
				
				prod.precio=nuevoPrecio;
				fseek(arch, -sizeof(Producto), 1);
				fwrite(&prod, sizeof(Producto), 1, arch);
			}
			cout<<"Ingresar codigo de producto con precio a modificar (0 para fin de ingreso de codigos): "<<endl;
			cin>>unCod;
		}
		fclose(arch);
	}
	else
		cout<<"Error en fopen."<<endl;
}

int menu( void ) 
{
 int op ;
 cout << "*********** Menu ********** " << endl ;
 cout << "1 Agregar un producto al archivo productos.dat " << endl ;
 cout << "2 Mostrar los registros del archivo Productos.dat" << endl ;
 cout << "3 Generar archivo reposicion.dat" << endl ;
 cout << "4 Modificar un precio en el archivo productos.dat" << endl ;
 cout<<  "5 Modificar muchos precios" << endl; 
 cout << "0 Salir " << endl  ;
 cout << " Ingresar la opcion : " ;
 cin >> op ;
 return op ;	
}
