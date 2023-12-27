#include <iostream>
#include <conio.h>
#include <stdio.h> 
#include <string.h>

using namespace std;

// definimos la estructura del registro del archivo examenes
typedef struct Examenes
{
	int matricula;
	char nombre [25];
	int codMateria;
	int nota;
}Examenes;


// funcion principal del programa
int main ()
{
	Examenes exa;
	int n;
	int unaMat;
	int unCod;
	int i;
	
	FILE*archivo=fopen("Examenes.dat", "wb");
	if(archivo!=NULL)
	{
		exa.codMateria=0;
		exa.matricula=0;
		exa.nota=0;
		
		cout<<"Ingrese cantidad de alumnos: "<<endl;
		cin>>n;
		
		if (n>0)
		{
			for(int i=0; i<n; i++)
				fwrite(&exa,sizeof(Examenes),1,archivo);
		}
		fclose(archivo);
	}
	
	fopen("Examenes.dat", "rb+");
	if(archivo!=NULL)
	{
		for(int i=0; i<n; i++)
		{
			cout<<"Ingrese numero de matricula: "<<endl;
			cin>>exa.matricula;
				
			cout<<"Ingrese nombre del alumno: "<<endl;
			cin>>exa.nombre;
				
			cout<<"Ingrese el codigo de la materia: "<<endl;
			cin>>exa.codMateria;
				
			cout<<"Ingrese la nota obtenida: "<<endl;
			cin>>exa.nota;
				
			fwrite(&exa,sizeof(Examenes),1,archivo);
		}
			fclose(archivo);
		
	}
	else
		cout<<"Error en fopen."<<endl;
	
	fopen("Examenes.dat", "rb");
	if(archivo!=NULL)
	{
		cout<<"Ingrese la matricula del alumno a buscar: "<<endl;
		cin>>unaMat;
		
		cout<<"Ingrese el codigo de materia: "<<endl;
		cin>>unCod;
		
		fread(&exa,sizeof(Examenes),1,archivo);
		while(!feof(archivo) && (exa.matricula!=unaMat) && (exa.codMateria!=unCod))
		{
			fread(&exa,sizeof(Examenes),1,archivo);
			if (feof(archivo))
				cout<<"No se encontro al alumno solicitado"<<endl;
			else
				if (exa.nota>0)
					cout<<"El alumno con matricula "<<exa.matricula<<" rindio la materia con codigo "<<exa.codMateria<<" y tuvo una nota de "<<exa.nota<<endl;
				else
					cout<<"El alumno con matricula: "<<exa.matricula<<" no rindio la materia con codigo "<<exa.codMateria<<endl;	
		}
		fclose(archivo);
	}
	
	
}
