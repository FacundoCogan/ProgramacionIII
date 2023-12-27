#include <iostream>
#include <conio.h>
#include <stdio.h> 
#include <string.h>

#define CANTREG 10

using namespace std;

//Estructuras de los archivos
typedef struct Productos
{
	int cod;
	char desc[25];
	float precio;
	int stock;
}Productos;

typedef struct Compras
{
	int codProd;
	int cantComp;
}Compras;

typedef struct Pedidos
{
	int cod;
	int nroCliente;
	int cantPedida;
}Pedidos;

typedef struct PedidosNoSatisfechos
{
	int codN;
	int nroClienteN;
	int cantPedidaN;
}PedidosNoSatisfechos;

//Prototipos
void modificarPrecio();
void actualizarArch();
void procesarPedidos();
int menu ();
int hashing(int);

//Funcion principal
int main()
{
	int opcion;
	
	while ((opcion=menu ()) != 0)
	{
		switch(opcion)
		{
			case 1:
					modificarPrecio();
			case 2:
					actualizarArch();
			case 3:
					procesarPedidos();
							
		}
	}
}

//Funciones
int hashing(int codigo)
{
	return (codigo % CANTREG);
}

// 1
void modificarPrecio()
{
	FILE*arch=fopen("Productos.dat", "rb+");
	if(arch!=NULL)
	{
		int unCod;
		float nuevoPrecio;
		
		Productos unProd;
		
		cout<<"Ingrese codigo de producto a buscar: "<<endl;
		cin>>unCod;
		
		cout<<"Ingrese nuevo precio del producto: "<<endl;
		cin>>nuevoPrecio;
		
		fseek(arch, sizeof(Productos)*hashing(unCod), 0);
		fread(&unProd, sizeof(Productos), 1, arch);
		if(unProd.cod==unCod)
		{
			cout<<"El producto con codigo "<<unProd.cod<<" tiene un precio de $"<<unProd.precio<<endl;
			unProd.precio=nuevoPrecio;
			fseek(arch, -sizeof(Productos), 1);
			fwrite(&unProd, sizeof(Productos), 1, arch);
		}
		else
		{
			fseek(arch, 0, 2);
			fread(&unProd, sizeof(Productos), 1, arch);
			while(!feof(arch) && (unProd.cod!=unCod))
				fread(&unProd, sizeof(Productos), 1, arch);
			if(feof(arch))
				cout<<"El codigo ingresado no existe en el archivo"<<endl;
			else
			{
				cout<<"El producto con codigo "<<unProd.cod<<" tiene un precio de $"<<unProd.precio<<endl;
				unProd.precio=nuevoPrecio;
				fseek(arch, -sizeof(Productos), 1);
				fwrite(&unProd, sizeof(Productos), 1, arch);
			}	
		}
		fclose(arch);
	}
}

//Funcion que devuelve la posicion de un producto si es que existe en el archivo
int buscarProducto(int codigo)
{
	int ret = -1 ; 
	FILE * arch = fopen("Productos.dat","rb");
    if ( arch != NULL)
    {
       Productos unProd;
       int pos = hashing(codigo) ;
       fseek(arch , pos * sizeof(unProd) , 0);
       fread(&unProd,sizeof(unProd),1,arch); 
	   if (unProd.cod == codigo)
	      ret = pos ; // retorno la posicion a nivel de registro 
	   else  // busqueda en el area de rebalse
	   {
	     fseek(arch, sizeof(unProd) * CANTREG , 0);
	     fread(&unProd,sizeof(unProd),1,arch); // lectura secuencial 
	     while (!feof(arch) && unProd.cod != codigo)
	        fread(&unProd,sizeof(unProd),1,arch); 
	     if ( unProd.cod == codigo )
	        ret = (ftell(arch) - sizeof(unProd)) / sizeof(unProd); 	
			// ftell retorna la posicion del puntero de R/W relativa a bytes      	
			// a ftell le resto el sizeof(regp) para obtener la posicion al comienzo del registro
			// y lo dividimos por el sizeof(regp) para convertir la posicion relativa en bytes a 
			// posicion relativa a RL
	   }	   
	   fclose(arch);
    }
    else
     cout << "Error en fopen. " << endl ;
	return ret;
}

// 2
void actualizarArch()
{
	FILE*arch=fopen("Productos.dat", "rb+");
	FILE*archC=fopen("Compras.dat", "rb");
	if((arch!=NULL) && (archC!=NULL))
	{
		Productos unProd;
		Compras unaComp;
		
		fread(&unaComp,sizeof(unaComp), 1, archC); 
		while(!feof(archC))
		{
			int posicion=buscarProducto(unaComp.codProd);
			if(posicion!=-1)
			{
				fseek(arch, posicion*sizeof(unProd) , 0);
				fread(&unProd ,sizeof(unProd) ,1 ,arch);
				unProd.stock = unProd.stock + unaComp.cantComp;
				fseek(arch, -sizeof(unProd) , 1);
				fwrite(&unProd ,sizeof(unProd) ,1 ,arch);
			}
			fread(&unaComp, sizeof(unaComp), 1, archC);
		}
		fclose(arch);
		fclose(archC);
	}
}

void procesarPedidos()
{
	FILE*arch=fopen("Productos.dat", "rb+");
	FILE*archPe=fopen("Pedidos.dat", "rb");
	FILE*archN=fopen("PedidosNoSatisfechos.dat", "wb");
	if((arch!=NULL) && (archPe!=NULL) && (archN!=NULL))
	{
		Productos unProd;
		Pedidos unPed;
		PedidosNoSatisfechos unPedN;
		
		fread(&unPed ,sizeof(unPed), 1, archPe);
		while(!feof(archPe))
		{
			int posicion=buscarProducto(unPed.cod);
			if(posicion!=-1)
			{
				if(unPed.cantPedida <= unProd.stock)
				{
					cout<<"El pedido del cliente "<<unPed.nroCliente<<" fue satisfecho en su totalidad habiendo encargado "<<unPed.cantPedida<<" unidades del producto "<<unPed.cod<<endl;
					
					fseek(arch, posicion*sizeof(unProd) , 0);
					fread(&unProd ,sizeof(unProd) ,1 ,arch);
					unProd.stock = unProd.stock - unPed.cantPedida;
					fseek(arch, -sizeof(unProd) , 1);
					fwrite(&unProd ,sizeof(unProd) ,1 ,arch);
				}
				else
					if(unPed.cantPedida>unProd.stock)
						fwrite(&unPedN ,sizeof(unPedN) ,1 ,archN);
			}
		}
	}
}

int menu () 
{
 int op ;
 cout << "*********** Menu ********** " << endl ;
 cout << "1 Modificar el precio de un producto " << endl ;
 cout << "2 Actualizar stock del archivo productos en funcion de las compras" << endl ;
 cout << "3 Actualizar stock del archivo productos en funcion de los pedidos" << endl ;
 cout << "0 Salir " << endl  ;
 cout << " Ingresar la opcion : " ;
 cin >> op ;
 return op ;	
}
