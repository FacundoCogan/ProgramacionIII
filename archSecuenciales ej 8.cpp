#include <iostream>
#include <conio.h>
#include <stdio.h> 
#include <string.h>

using namespace std;

// definimos la estructura del registro del archivo HorasExtras

typedef struct HorasExtras
{
	int nroLegajo;
	int cantHsExtras;
	
}HorasExtras;

int main ()
{
	int i;
	HorasExtras extras;
	float valor;
	float auxMonto;
	int n;
	
	FILE*arch=fopen("HorasExtras.dat", "wb");
	if(arch!=NULL)
	{
		cout<<"Ingrese la cantidad de empleados: "<<endl;
		cin>>n;
		
		for(i=0; i<n; i++)
		{
			cout<<"Ingrese el numero de legajo: "<<endl;
			cin>>extras.nroLegajo;
			
			cout<<"Ingrese la cantidad de horas extras trabajadas: "<<endl;
			cin>>extras.cantHsExtras;
		}
		fclose(arch);
	}
	else
		cout<<"Error en el fopen."<<endl;
		
// genero archivo secuencial PagasHsExtras.dat 
		
		FILE * archP = fopen("PagasHsExtras.dat", "wb");
	fopen("HorasExtras.dat", "rb");
	if ((arch!=NULL) && (archP!=NULL))
	{
		cout<<"Ingrese el valor de cada hora extra a pagar: "<<endl;
		cin>>valor;
		
		fread(&extras, sizeof(HorasExtras), 1, arch);
		while (!feof(arch))
		{
			auxMonto=extras.cantHsExtras*valor;
			fwrite(&extras, sizeof(HorasExtras), 1, archP);
			
			cout<<"Al empleado con legajo "<<extras.nroLegajo<<" hay que pagarle un monto total de $"<<auxMonto<<" por haber trabajado un total de "<<extras.cantHsExtras<< " horas extras."<<endl;
			fread(&extras, sizeof(HorasExtras), 1, arch);
		}

		fclose(arch);
		fclose(archP);
	}
	else
		cout<<"Error en el fopen."<<endl;
		
		
		
		
		
}

