//directivas de preprocesamiento
#include <iostream>
#include <conio.h>
#include <stdio.h> 

#define TAMANIOVEC 5

using namespace std;

// prototipos de las funciones
int menu(void);
void inicializar(int []);
void completarVec(int [], int);
void leerVec(int [], int);
void sumaVec(int [], int);
void posMayor(int [], int);
void intercalar(int [], int, int); 

//funcion principal
int main(void)
{
  int vec[TAMANIOVEC] ;
  int opcion ;
  int cant=TAMANIOVEC;
  while ((opcion = menu()) != 0)
  {
  	 switch(opcion)
  	 {
        case 1 : inicializar(vec) ; break ;  	 	
        case 2 :{
        			int cant;
        			do{
        				cout<<"Ingrese la cantidad de numeros a ingresar: "<<endl;
        				cin>>cant;
        			}while (cant >= TAMANIOVEC);
        			completarVec (vec, cant);
        			break;
				}
		
				completarVec(vec, cant) ; break ; 
		 	 	
        case 3 : leerVec (vec, cant) ; break ;  	 	
        case 4 : sumaVec (vec, cant) ; break ;  	 	
        case 5 : break ;  	 	
        case 6 : posMayor (vec, cant) ; break ;  	 	
	 }
  }
  return 0 ;
}

// implementacion de las funciones
int menu( void ) 
{
 int op ;
 cout << "*********** Menu ********** " << endl ;
 cout << "1 inicializar el vector en ceros " << endl ;
 cout << "2 ingresar números al vector " << endl ;
 cout << "3 mostrar el contenido del vector " << endl ;
 cout << "4 Ejercicio 3 (Mostrar la sumatoria de los números del vector) " << endl ;
 cout << "5 Ejercicio 4 (intercalar un número en el vector ordenado y no completo) " << endl  ;
 cout << "6 Ejercicio 5 (Mostrar la posición del número mayor del vector) " << endl  ;
 cout << "0 Salir " << endl  ;
 cin >> op ;
 return op ;	
}

void inicializar (int vec[])

{
	int i;

	for (i=0; i<TAMANIOVEC; i++)
	{
		vec[i]=0;
	}
}

void completarVec (int vec[], int cant)

{
	int i;

	for (i=0; i<cant; i++)
	{
		cout<<"Ingresar para la posicion: "<<i<<endl;
		cin>>vec[i];
	}
}

void leerVec (int vec[], int cant)

{
	int i;
	
	for (i=0; i<cant; i++)
	{
		cout<<"En la posicion: "<<i<< " del vector, se encuentra el numero: "<<vec[i]<<endl; 
	}
}

void sumaVec (int vec[])

{
	int i, suma;
	
	for (i=0; i<TAMANIOVEC; i++)
	{
		suma+=vec[i];
	}
	
	cout<<"La suma del vector es de: "<<suma<<endl;
}

void posMayor (int vec[], int cant)

{
	int i;
	int pos=0;
	int may = vec[0];
	for (i=0; i<cant; i++)
	{
		if (vec[i] > may)
		{
			pos = i;
			may = vec[i];
		}
	}
	
	cout<<"La posicion del numero mayor del vector es la: "<<may<<endl;
}

void intercalar(int [], int cant, int num);

{
	int i;
	for (i=0; num > vec[i] && i < cant; i++)
	if (i==cant)
		vec[i]=num;
	else
	{
		int j;
		for (j=cant; j>i; j--)
		{
			vec[j]=vec[j-1];
		}
		vec[j]=num;
	}
}
