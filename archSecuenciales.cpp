#include <iostream>
#include <conio.h>
#include <stdio.h> 
#include <string.h> 

using namespace std;

// definimos la estructura del registro del archivo productos
typedef struct regProducto
{
	int codigo;
	char desc [16];
	int stock;
	float precio;
}regProducto;

//protipos de las funciones
int menu ();
void ej_1_AgregarProducto(regProducto);
void ej_2_LeerArchivo(char []);
void ej_3_GenerarArchReposicion();
void ej_4_ModificarPrecio(regProducto);
void ej_5_ModificarVariosPrecios(regProducto);

// funcion principal de nuestro programa
int main ()
{
	int opcion;
	regProducto regp;
	while ((opcion = menu ()) != 0)
	{
		switch (opcion)
		{
			case 1: {
				regProducto regp;
				cout<<" Ingrese codigo: (0 para salir del ingreso de productos) "<<endl;
				cin>>regp.codigo;
				while (regp.codigo != 0)
				{
					cout<<" Ingrese descripcion del producto: "<<endl;
					cin>>regp.desc;
					
					cout<<" Ingrese stock del producto: "<<endl;
					cin>>regp.stock;
					
					cout<<" Ingrese precio del producto: "<<endl;
					cin>>regp.precio;
					
					ej_1_AgregarProducto(regp);
					
					cout<<" Ingrese codigo: (0 para salir del ingreso de productos) "<<endl;
					cin>>regp.codigo;
					
					
				}
				break;
				}
				
			case 2:{
				char nomArch[15];
				strcpy(nomArch,"Productos.dat");
				ej_2_LeerArchivo(nomArch);
				break;
			} 
				
			case 3: ej_3_GenerarArchReposicion(); break;	
			
			case 4: {
				char nomArch[15];
				strcpy(nomArch,"Reposicion.dat");
				ej_2_LeerArchivo(nomArch);
				break;
			}
			
			case 5: ej_4_ModificarPrecio(regp); break;
			
			case 6: ej_5_ModificarVariosPrecios(regp); break;
		}
	}
	
	
	return 0;
}



// implementacion de las funciones

void ej_1_AgregarProducto(regProducto regp)
{
	FILE * fdp = fopen("Productos.dat", "ab");
	if (fdp != NULL)
	{
		fwrite(&regp, sizeof(regp), 1, fdp);
		fclose(fdp);
	}
	else
		cout<<"Error en el open"<<endl;
}

void ej_2_LeerArchivo(char nomArch[])
{
	FILE * fdp = fopen("Productos.dat", "rb");
	if (fdp != NULL)
	{
		regProducto regp;
		fread(&regp, sizeof(regp), 1, fdp);
		while (!feof(fdp))
		{
			cout<<"El producto con codigo: "<<regp.codigo<<" tiene la descripcion: "<<regp.desc<<", un stock de: "<<regp.stock<< " unidades, y un precio de: "<<regp.precio<<endl;
			fread(&regp, sizeof(regp), 1, fdp);
		}
		fclose(fdp);
	}
	else
		cout<<"Error en el open"<<endl;
}

void ej_3_GenerarArchReposicion()
{
	FILE * arch = fopen("Reposicion.dat", "wb");
	FILE * fdp = fopen("Productos.dat", "rb");
	if ((arch!=NULL) && (fdp!=NULL))
	{
		regProducto regp;
		fread(&regp, sizeof(regp), 1, fdp);
		while (!feof(fdp))
		{
			if(regp.stock==0)
			{
				fwrite(&regp, sizeof(regp), 1, arch);
			}
			fread(&regp, sizeof(regp), 1, fdp);
		}
		fclose(arch);
		fclose(fdp);
	}
	else
		cout<<"Error en el open"<<endl;
}

void ej_4_ModificarPrecio(regProducto regp)
{
	FILE * fdp = fopen("Productos.dat", "rb+");
	if (fdp != NULL)
	{
		regProducto regp;
		int unCod;
		cout<<" Codigo del producto a buscar: "<<endl;
		cin>>unCod;
		fread(&regp, sizeof(regp), 1, fdp);
		while (!feof(fdp) && (regp.codigo!=unCod))
		{
			fread(&regp, sizeof(regp), 1, fdp);
		}
		if (feof(fdp))
			cout<<"El codigo no existe."<<endl;
		else
		{
			cout<<" El precio del producto: "<<regp.codigo<< " es de: $"<<regp.precio<<endl;	
			float nuevoPrecio;
			cout<<" El nuevo precio sera de: "<<endl;
			cin>>nuevoPrecio;
			regp.precio=nuevoPrecio;
			fseek(fdp, -sizeof(regp), SEEK_CUR);
			fwrite(&regp, sizeof(regp), 1, fdp);
		}
	}
	else
		cout<<"Error en el open"<<endl;
}

void ej_5_ModificarVariosPrecios(regProducto regp)
{
	FILE * fdp = fopen("Productos.dat", "rb+");
	if (fdp != NULL)
	{
		regProducto regp;
		int unCod;
		cout<<" Codigo del producto a buscar: (0 para salir de modificacion de precios)"<<endl;
		cin>>unCod;
		while (unCod != 0){
			
			fread(&regp, sizeof(regp), 1, fdp);
			while (!feof(fdp) && (regp.codigo!=unCod))
			{
				fread(&regp, sizeof(regp), 1, fdp);
			}
			if (feof(fdp))
				cout<<"El codigo no existe."<<endl;
			else
			{
				cout<<" El precio del producto: "<<regp.codigo<< " es de: $"<<regp.precio<<endl;	
				float nuevoPrecio;
				cout<<" El nuevo precio sera de: "<<endl;
				cin>>nuevoPrecio;
				regp.precio=nuevoPrecio;
				fseek(fdp, -sizeof(regp), SEEK_CUR);
				fwrite(&regp, sizeof(regp), 1, fdp);
			}
			
			cout<<" Codigo del producto a buscar: (0 para salir de modificacion de precios)"<<endl;
			cin>>unCod;
		
		}
	}
	else
		cout<<"Error en el open"<<endl;
}

int menu( void ) 
{
 int op ;
 cout << "*********** Menu ********** " << endl ;
 cout << "1 Agregar un producto al archivo productos.dat " << endl ;
 cout << "2 Mostrar los registros del archivo Productos.dat" << endl ;
 cout << "3 Generar archivo reposicion.dat" << endl ;
 cout << "4 Mostrar los registros del archivo Reposicion.dat" << endl ;
 cout << "5 Modificar un precio en el archivo productos.dat" << endl ;
 cout<<  "6 Modificar muchos precios" << endl; 
 cout << "0 Salir " << endl  ;
 cout << " Ingresar la opcion : " ;
 cin >> op ;
 return op ;	
}
