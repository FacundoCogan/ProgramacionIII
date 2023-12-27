#include <iostream>
#include <conio.h>
#include <stdio.h> 
#include <string.h> 

using namespace std;

typedef struct Alumnos{
	int mat;
	char nombre[20];
	int codMat;
	int nota;
};

int main () 
{
	Alumnos alu;
	int n, i, unaMat, unCod;
	
	FILE*arch=fopen("Examenes.dat", "wb");
	if(arch!=NULL)
	{
		alu.codMat=0;
		alu.mat=0;
		alu.nota=0;
		
		cout<<"Ingrese cantidad de alumnos: "<<endl;
		cin>>n;
		
		if(n>0)
		{
			for(i=0; i<n; i++)
				fwrite(&arch, sizeof(Alumnos), 1, arch);	
		}
		fclose(arch);
	}
	else
		cout<<"Error en fopen."<<endl;
		
	fopen("Examenes.dat", "rb+");
	if(arch!=NULL)
	{
		for(i=0; i<n; i++)
		{
			cout<<"Ingrese codigo de materia: "<<endl;
			cin>>alu.codMat;
			
			cout<<"Ingrese matricula: "<<endl;
			cin>>alu.mat;
			
			cout<<"Ingrese nombre del alumno: "<<endl;
			cin>>alu.nombre;
			
			cout<<"Ingrese nota del alumno: "<<endl;
			cin>>alu.nota;
			
			fwrite(&arch, sizeof(Alumnos), 1, arch);
		}
		fclose(arch);
	}
	else
		cout<<"Error en fopen."<<endl;
	
	fopen("Examenes.dat", "rb");
	if(arch!=NULL)
	{
		cout<<"Ingrese una matricula: "<<endl;
		cin>>unaMat;
		
		cout<<"Ingrese un codigo de materia: "<<endl;
		cin>>unCod;
		
		fread(&arch, sizeof(Alumnos), 1, arch);
		while(!feof(arch) && (alu.mat!=unaMat) && (alu.codMat!=unCod))
		{
			fread(&arch, sizeof(Alumnos), 1, arch);
			
			if(feof(arch))
				cout<<"No se encontro el alumno. "<<endl;
			else
				if(alu.nota>0)
					cout<<"El alumno con matricula "<<alu.mat<<" rindio la materia con codigo: "<<alu.codMat<<endl;
				else
					cout<<"El alumno con matricula "<<alu.mat<<" no rindio la materia con codigo: "<<alu.codMat<<endl;	
		}
		fclose(arch);
		
	}
	else
		cout<<"Error en fopen."<<endl;
}



	

