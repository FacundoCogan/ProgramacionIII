#include <iostream>
#include <conio.h>
#include <stdio.h> 
#include <string.h> 

using namespace std;

typedef struct Empleados{
	int legajo;
	float sueldoBasico;
}Empleados;

int main ()
{
	Empleados unEmp;
	int i, n;
	
	cout<<"Ingrese la cantidad de empleados: "<<endl;
	cin>>n;
	
	FILE*arch=fopen("Empleados.dat", "wb");
	if (arch!=NULL)
	{
		for(i=0; i<n; i++)
		{
			cout<<"Ingrese legajo del empleado: "<<endl;
			cin>>unEmp.legajo;
			
			cout<<"Ingrese el sueldo del empleado: "<<endl;
			cin>>unEmp.sueldoBasico;
			
			fwrite(&arch, sizeof(Empleados), 1, arch);
		}
		fclose(arch);
	}
	else
		cout<<"Error en fopen."<<endl;
		
	FILE*archi=fopen("SueldoBajo.dat", "wb");	
	fopen("Empleados.dat", "rb");
	if((arch!=NULL) && (archi!=NULL)) 
	{
		fread(&arch, sizeof(Empleados), 1, arch);
		while(!feof(arch))
		{
			if(unEmp.sueldoBasico<4000)
				fwrite(&archi, sizeof(Empleados), 1, archi);
				
			fread(&arch, sizeof(Empleados), 1, arch);	
		}
		fclose(arch);
		fclose(archi);
	}
	else
		cout<<"Error en fopen."<<endl;
}
