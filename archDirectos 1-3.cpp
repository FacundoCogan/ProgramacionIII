#include <iostream>
#include <conio.h>
#include <stdio.h> 
#include <string.h>

#define CANTREG 10

using namespace std;

// definimos la estructura del registro del archivo productos
typedef struct regProducto
{
	int codigo;
	char desc [25];
	int stock;
	float precio;
}regProducto;

// definimos la estructura del registro del archivo compras
typedef struct regCompras
{
	int codProCom;
	int stockCom;
}regCompras;

// definimos la estructura del registro del archivo pedidos
typedef struct regPedidos
{
	int cod;
	int nroCliente;
	int cantPedida;
}regPedidos;

// definimos la estructura del registro del archivo pedidos no satisfechos
typedef struct regPedidosNoSatisfechos
{
	int codN;
	int nroClienteN;
	int cantPedidaN;
}regPedidosNoSatisfechos;

//protipos de las funciones
int menu ();
int hashing (int);
void generarArchivoVacio ();

// ejercicio 1
void mostrarProductos ();
void agregarProducto(regProducto);
void modificarPrecio(int, float);

// ejercicio 2
void agregarCompra(regCompras);
void mostrarCompras();
void actualizarStock(); // leer compras en forma secuencial y por cada compra, acceder en forma directa al producto y sumar la cantidad comprada al stock del producto

// ejercicio 3
void agregarPedido(regPedidos);
void mostrarPedidos();
void procesarPedidos();
void mostrarPedidosN();

// funcion principal de nuestro programa
int main ()
{
	int opcion;
	regProducto regp;
	regCompras regc;
	regPedidos regpe;
	int unCod;
	float nuevoPrecio;
	while ((opcion=menu ()) != 0)
	{
		switch (opcion)
		{
			case 1:
					generarArchivoVacio(); break;
			case 2:
					mostrarProductos(); break;
			case 3:
					agregarProducto(regp); break;
			case 4: 
					cout<<"Ingrese codigo a buscar: "<<endl;
        			cin>>unCod;
        			
        			cout<<"Ingrese nuevo precio: "<<endl;
        			cin>>nuevoPrecio;
			
					modificarPrecio(unCod, nuevoPrecio); break;
			case 5:
					agregarCompra(regc); break;
			case 6:
					mostrarCompras(); break;
			case 7:
					actualizarStock(); break;	
			case 8:
					agregarPedido(regpe); break;
			case 9:
					mostrarPedidos(); break;
			case 10:
					procesarPedidos(); break;		
			case 11:
					mostrarPedidosN(); break;			
		}
	}
	
	
	return 0;
}

// implementacion de las funciones

int hashing (int codigo)
{
	return (codigo % CANTREG);
}

void generarArchivoVacio()
{
	FILE*arch=fopen("Productos.dat", "wb");
	if (arch!=NULL)
	{
		regProducto regp;
		int i;
		regp.codigo=0;
		strcpy(regp.desc,".........................");
		regp.stock=0;
		regp.precio=0;
		
		for (i=0; i<CANTREG; i++)
		{
			fwrite(&regp, sizeof(regProducto), 1, arch);
		}
		fclose(arch);
	}
	else
		cout<<"Error en fopen."<<endl;
	
}

// ejercicio 1

void mostrarProductos()
{
	regProducto regp;
	FILE * arch = fopen("Productos.dat","rb");
    if (arch != NULL)
    {
      fread(&regp, sizeof(regProducto), 1, arch);
      while(!feof(arch))
      {
	    cout << regp.codigo << " " << regp.desc << " " << regp.precio << " " << regp.stock << endl ;
	    fread(&regp, sizeof(regProducto), 1, arch);
      }
      fclose(arch);
   }
   else
		cout<<"Error en fopen."<<endl;
}

void agregarProducto(regProducto regp)
{
	FILE*arch=fopen("Productos.dat", "rb+");
	if (arch!=NULL)
	{
		regProducto auxRegp;
		
		cout<<" Ingrese codigo: "<<endl;
		cin>>regp.codigo;
		
		cout<<"Ingrese descripcion: "<<endl;
		cin>>regp.desc;
		
		cout<<"Ingrese stock: "<<endl;
		cin>>regp.stock;
		
		cout<<"Ingrese precio: "<<endl;
		cin>>regp.precio;
		
		int pos = hashing(regp.codigo);
		fseek(arch, pos*sizeof(regProducto), 0);
		fread(&regp, sizeof(regProducto), 1, arch);
		if (auxRegp.codigo!=0) // colision, ya existe un registro en esa posicion
		{
			fseek(arch, 0, 2); // me posiciono al final del archivo
			fwrite(&regp, sizeof(regProducto), 1, arch);
		}
		else // no hay colision, la posicion en el archivo esta libre
			{
				fseek(arch, -sizeof(regProducto), 1);
				fwrite(&regp, sizeof(regProducto), 1, arch);
			}
			fclose(arch);
	}
	else
		cout<<"Error en fopen."<<endl;
}

void modificarPrecio (int unCod, float nuevoPrecio)
{
    FILE*arch=fopen("Productos.dat","rb+");
    if(arch!=NULL)
    {
        regProducto regp;
        
        fseek(arch,hashing(unCod)*sizeof(regProducto),SEEK_SET);
        fread(&regp,sizeof(regProducto),1,arch);
        if(regp.codigo==unCod) // lo encontre en el area de hashing
        {
            cout<<regp.codigo<<" - "<<regp.precio<<endl;
            regp.precio=nuevoPrecio;
            fseek(arch,-sizeof(regProducto),SEEK_CUR);
            fwrite(&regp,sizeof(regProducto),1,arch); 
        }

        else // lo voy a buscar al area de rebalse
        {
            fseek(arch, 0, 2);
            fread(&regp,sizeof(regProducto),1,arch);
            while(!feof(arch) && regp.codigo!=unCod)
                fread(&regp,sizeof(regProducto),1,arch);
            if(feof(arch))
                cout<<unCod<<" no existe"<<endl;
            else
            {
                cout<<regp.codigo<<" - "<<regp.precio<<endl;
                regp.precio=nuevoPrecio;
                fseek(arch,-sizeof(regProducto),SEEK_CUR);
                fwrite(&regp,sizeof(regProducto),1,arch);
            }

        }
        fclose(arch);
	}
}

int buscarProducto(int codigo)
{
	int ret = -1 ; 
	FILE * arch = fopen("Productos.dat","rb");
    if ( arch != NULL)
    {
       regProducto regp;
       int pos = hashing(codigo) ;
       fseek(arch , pos * sizeof(regp) , 0);
       fread(&regp,sizeof(regp),1,arch); 
	   if (regp.codigo == codigo)
	      ret = pos ; // retorno la posicion a nivel de registro 
	   else  // busqueda en el area de rebalse
	   {
	     fseek(arch, sizeof(regp) * CANTREG , 0);
	     int nb = fread(&regp,sizeof(regp),1,arch); // lectura secuencial 
	     while (nb > 0 && regp.codigo != codigo)
	         nb = fread(&regp,sizeof(regp),1,arch); 
	     if ( regp.codigo == codigo )
	        ret = (ftell(arch) - sizeof(regp)) / sizeof(regp); 	
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

// ejercicio 2

void agregarCompra(regCompras regc)
{
	FILE * archC = fopen("Compras.dat", "ab");
	if (archC!=NULL)
	{
		cout<<" Ingrese codigo: (0 para salir del ingreso de productos) "<<endl;
		cin>>regc.codProCom;
		while (regc.codProCom != 0)
		{
			cout<<" Ingrese cantidad de unidades compradas: "<<endl;
			cin>>regc.stockCom;
			
			fwrite(&regc, sizeof(regCompras), 1, archC);
			
			cout<<" Ingrese codigo: (0 para salir del ingreso de productos) "<<endl;
			cin>>regc.codProCom;
					
		}
		fclose(archC);
	}
	else
		cout<<"Error en fopen."<<endl;
}

void mostrarCompras()
{
	FILE * archC = fopen("Compras.dat", "rb");
	if (archC != NULL)
	{
		regCompras regc;
		fread(&regc, sizeof(regCompras), 1, archC);
		while (!feof(archC))
		{
			cout<<"El producto con codigo "<<regc.codProCom<<" tiene un total de "<<regc.stockCom<<" unidades compradas."<<endl;
			fread(&regc, sizeof(regCompras), 1, archC);
		}
		fclose(archC);
	}
	else
		cout<<"Error en fopen."<<endl;
}

void actualizarStock()
{
   	regCompras    regc ;
   	regProducto  regp ;
   	FILE * arch = fopen("Productos.dat","rb+");
	FILE * archC = fopen("Compras.dat","rb");
	if (arch != NULL && archC != NULL)
	{
      fread(&regc, sizeof(regCompras), 1 , archC); // lectura secuencial de compras
      while (!feof(archC))
      {
          int posicion = buscarProducto(regc.codProCom); // obtenemos la posicion a nivel de registro en el archivo Productos.dat
		  if (posicion != -1)
		  {
		  	 fseek(arch, posicion*sizeof(regProducto), 0);
		  	 fread(&regp,sizeof(regProducto), 1, arch);
		  	 regp.stock = regp.stock + regc.stockCom ;
		  	 fseek(arch, -sizeof(regProducto), 1);
		  	 fwrite(&regp,sizeof(regProducto), 1, arch);
		  }      	
		  fread(&regc,sizeof(regCompras), 1, archC);
	  }
	  fclose(archC);
	  fclose(arch);
    }
}

// ejercicio 3

void agregarPedido(regPedidos regpe)
{
	FILE * archPe = fopen("Pedidos.dat", "ab");
	if (archPe!=NULL)
	{
		cout<<" Ingrese codigo: (0 para salir del ingreso de productos) "<<endl;
		cin>>regpe.cod;
		while (regpe.cod != 0)
		{
			cout<<"Ingrese numero de cliente: "<<endl;
			cin>>regpe.nroCliente;
			
			cout<<"Ingrese cantidad pedida: "<<endl;
			cin>>regpe.cantPedida;
			
			fwrite(&regpe, sizeof(regPedidos), 1, archPe);
			
			cout<<" Ingrese codigo: (0 para salir del ingreso de productos) "<<endl;
			cin>>regpe.cod;
					
		}
		fclose(archPe);
	}
	else
		cout<<"Error en fopen."<<endl;
}

void mostrarPedidos()
{
	FILE * archPe = fopen("Pedidos.dat", "rb");
	if (archPe != NULL)
	{
		regPedidos regpe;
		fread(&regpe, sizeof(regPedidos), 1, archPe);
		while (!feof(archPe))
		{
			cout<<"El cliente "<<regpe.nroCliente<<" pidio "<<regpe.cantPedida<<" unidades del producto "<<regpe.cod<<endl;
			fread(&regpe, sizeof(regPedidos), 1, archPe);
		}
		fclose(archPe);
	}
	else
		cout<<"Error en fopen."<<endl;
}

// a y b

void procesarPedidos()
{
	regPedidos    regpe ;
	regProducto  regp ;
	regPedidosNoSatisfechos regpeN;
	FILE * arch = fopen("Productos.dat","rb+");
	FILE * archPe = fopen("Pedidos.dat","rb");
	FILE * archPeN = fopen("PedidosNoSatisfechos.dat","wb");
	if (arch != NULL && archPe != NULL && archPeN!= NULL)
	{
      fread(&regpe, sizeof(regPedidos), 1 , archPe); // lectura secuencial de pedidos
      while (!feof(archPe))
      {
          int posicion = buscarProducto(regpe.cod); // obtenemos la posicion a nivel de registro en el archivo Productos.dat
		  if (posicion != -1)
		  {
			if (regpe.cantPedida <= regp.stock)
			{
				cout<<"El pedido del cliente "<<regpe.nroCliente<<" fue satisfecho en su totalidad habiendo encargado "<<regpe.cantPedida<<" unidades del producto "<<regpe.cod<<endl;
				
				fseek(arch, posicion*sizeof(regProducto), 0);
				fread(&regp,sizeof(regProducto), 1, arch);
				regp.stock = regp.stock - regpe.cantPedida ;
				fseek(arch, -sizeof(regProducto), 1);
				fwrite(&regp,sizeof(regProducto), 1, arch);	
			}
			else
				if(regpe.cantPedida > regp.stock)
				fwrite(&regpeN,sizeof(regPedidosNoSatisfechos), 1, archPeN);	
		  }      	
		  fread(&regpe,sizeof(regPedidos), 1, archPeN);
	  }
	  fclose(archPe);
	  fclose(arch);
    }
}

// c

void mostrarPedidosN()
{
	FILE * archPeN = fopen("PedidosNoSatisfechos.dat", "rb");
	if (archPeN != NULL)
	{
		regPedidosNoSatisfechos regpeN;
		fread(&regpeN, sizeof(regPedidosNoSatisfechos), 1, archPeN);
		while (!feof(archPeN))
		{
			cout<<"El pedido del cliente "<<regpeN.nroClienteN<<" de "<<regpeN.cantPedidaN<<" unidades pedidas del producto "<<regpeN.codN<<" no fue satisfecho."<<endl;
			fread(&regpeN, sizeof(regPedidosNoSatisfechos), 1, archPeN);
		}
		fclose(archPeN);
	}
	else
		cout<<"Error en fopen."<<endl;
}


int menu () 
{
 int op ;
 cout << "*********** Menu ********** " << endl ;
 cout << "1 Generar archivo nuevo vacio " << endl ;
 cout << "2 Mostrar archivo productos" << endl ;
 cout << "3 Agregar productos" << endl ;
 cout << "4 Modificar el precio de un producto" << endl ;
 cout << "5 Agregar compra" << endl ;
 cout << "6 Mostrar archivo compras" << endl; 
 cout << "7 Actualizar stock del archivo productos en funcion de las compras" << endl; 
 cout << "8 Agregar pedidos" << endl ;
 cout << "9 Mostrar archivo pedidos" << endl;
 cout << "10 Actualizar stock del archivo productos en funcion de los pedidos" << endl; 
 cout << "11 Mostrar archivo pedidos no satisfechos" << endl;
 cout << "0 Salir " << endl  ;
 cout << " Ingresar la opcion : " ;
 cin >> op ;
 return op ;	
}
