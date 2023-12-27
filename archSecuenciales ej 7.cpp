#include <iostream>
#include <conio.h>
#include <stdio.h> 
#include <string.h>

using namespace std;

// definimos la estructura del registro del archivo empleados

typedef struct Empleados
{
	int nroLegajo;
	float sueldoBas;
	
}Empleados;

int main ()
{
	Empleados emp;
	int n;
	int i;
	
	FILE*archi=fopen("Empleados.dat", "wb");
	if(archi!=NULL)
	{
		cout<<"Ingrese la cantidad de empleados: "<<endl;
		cin>>n;
		
		for(i=0; i<n; i++)
		{
			cout<<"Ingrese el numero de legajo: "<<endl;
			cin>>emp.nroLegajo;
			
			cout<<"Ingrese el sueldo del empleado: "<<endl;
			cin>>emp.sueldoBas;
		}
		fclose(archi);
	}
	else
		cout<<"Error en el fopen."<<endl;
	
	FILE * archiv = fopen("SueldoBajo.dat", "wb");
	fopen("Empleados.dat", "rb");
	if ((archi!=NULL) && (archiv!=NULL))
	{
		fread(&emp, sizeof(Empleados), 1, archi);
		while (!feof(archi))
		{
			if(emp.sueldoBas<40000)
			{
				fwrite(&emp, sizeof(Empleados), 1, archiv);
			}
			fread(&emp, sizeof(Empleados), 1, archi);
		}
		fclose(archi);
		fclose(archiv);
	}
	else
		cout<<"Error en el fopen."<<endl;
}

