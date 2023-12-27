#include <iostream>
#include <conio.h>
#include <stdio.h> 
#include <string.h> 

using namespace std;

typedef struct Empleados{
	int legajo;
	int hsExtras;
}Empleados;

int main ()
{
	 Empleados unEmp;
	 int n, i;
	 float valor, auxMonto;
	 
	 cout<<"Ingrese la cantidad de empleados: "<<endl;
	 cin>>n;
	 
	 FILE*arch=fopen("HorasExtras.dat", "wb");
	 if(arch!=NULL)
	 {
	 	for(i=0; i<n; i++)
	 	{
	 		cout<<"Ingrese legajo del empleado: "<<endl;
	 		cin>>unEmp.legajo;
	 		
	 		cout<<"Ingrese cantidad de horas extras realizadas por el empleado: "<<endl;
	 		cin>>unEmp.hsExtras;
	 		
	 		fwrite(&arch, sizeof(Empleados), 1, arch);
	 	}
	 	fclose(arch);
	 }
	 else
	 	cout<<"Error en fopen."<<endl;
	 
	FILE*archi=fopen("PagaHsExtras.dat", "wb");
	fopen("HorasExtras.dat", "rb");
	if((arch!=NULL) && (archi!=NULL))
	{
		cout<<"Ingrese el valor a pagar por cada hora extra realizada por el empleado: "<<endl;
		cin>>valor;
		
		fread(&arch, sizeof(Empleados), 1, arch);
		while(!feof(arch))
		{
			auxMonto=unEmp.hsExtras*valor;
			fwrite(&archi, sizeof(Empleados), 1, archi);
			
			cout<<"Al empleado con legajo "<<unEmp.legajo<<" hay que pagarle un total de $"<<auxMonto<<" por haber trabajado un total de "<<unEmp.hsExtras<<" horas extras."<<endl;
			fread(&arch, sizeof(Empleados), 1, arch);
		}
		fclose(arch);
		fclose(archi);
	}
	else
		cout<<"Error en fopen."<<endl;
	
}
