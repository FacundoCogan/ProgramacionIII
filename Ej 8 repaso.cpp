//directivas de preprocesamiento
#include <iostream>
#include <conio.h>
#include <stdio.h> 
#include <string.h> 

#define TAMANIOVEC 4

using namespace std;

typedef struct alumno 
{
	char nombre[9] ;
	int nota1 ;
	int nota2 ;
} alumno ;

// prototipos de las funciones
int menu(void);
void inicializar( alumno []) ;
void ingresar(alumno[]) ;
void mostrar( alumno []) ;
void resultados (alumno []);

//funcion principal
int main(void)
{
  alumno vec[TAMANIOVEC] ;	
  int opcion ;
  while ((opcion = menu()) != 0)
  {
  	 switch(opcion)
  	 {
        case 1 :  inicializar(vec) ; break ;  	 	
        case 2 :  break ;  	 	
        case 3 :  mostrar(vec) ; break ;  	 	
        case 4 :  break;
        case 5 :  break;
        case 6 :  break ;  	 	
	 }
  }
  return 0 ;
}

// implementacion de las funciones
int menu( void ) 
{
 int op ;
 cout << "*********** Menu ********** " << endl ;
 cout << "1 inicializar el vector alumnos " << endl ;
 cout << "2 ingresar alumnos al vector de alumnos" << endl ;
 cout << "3 mostrar el vector de alumnos " << endl ;
 cout << "0 Salir " << endl  ;
 cout << " Ingresar la opcion : " ;
 cin >> op ;
 return op ;	
}

void inicializar(alumno vec[])
{
	int i ;
	for(i = 0 ; i < TAMANIOVEC ; i++)
	  {
	  	strcpy(vec[i].nombre,"........\0") ;
	  	vec[i].nota1 = 0 ;
	  	vec[i].nota2 = 0 ;
	  }
}

void mostrar(alumno vec[])
{
	int i ;
	for(i = 0 ; i < TAMANIOVEC ; i++)
	  cout << "contenido de vec[" << i << "] = " << vec[i].nombre << " " << vec[i].nota1 << " " << vec[i].nota2 << endl ;
}

void ingresar(alumno vec[])
{
	int i ;
	for(i = 0 ; i < TAMANIOVEC ; i++)
	{
		cout<<"Ingrese nombre del alumno: "<<endl;
		cin>>vec[i].nombre;
		
		cout<<"Ingresar la nota del primer parcial: "<<endl;
		cin>>vec[i].nota1;
		
		cout<<"Ingresar la nota del segundo parcial: "<<endl;
		cin>>vec[i].nota2;
	}
}

void resultados (alumno vec[])
{
	int i ;
	for(i = 0 ; i < TAMANIOVEC ; i++)
	{
		if (vec[i].nota1 && vec[i].nota2) >=4
		cout<<"El alumno "<<vec[i].nombre<<" aprobo la cursada. "<<endl;
		else
		{
			if (vec[i].nota1 && vec[i].nota2) <4
			cout<<"El alumno "<<vec[i].nombre<<" debe recuperar ambos parciales. "<<endl;	
		}
			else{
				if (vec[i].nota1 <4) && (vec[i].nota >=4)
				cout<<"El alumno "<<vec[i].nombre<<" debe recuperar el primer parcial. "<<endl;		
			} 	else
				{
					if (vec[i].nota1 >=4) && (vec[i].nota <4)
					cout<<"El alumno "<<vec[i].nombre<<" debe recuperar el segundo parcial. "<<endl;	
				}
	}
}
