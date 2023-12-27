#include <iostream>
#include <string.h>

using namespace std;

//Estructura del arbol
typedef struct Vuelo
{
	int nroVuelo;
	char destino[25]; 
	int cantPasajesVendidos;
	
}Vuelo;

typedef struct NodoA * PuntA;
typedef struct NodoA
{
	Vuelo datos;
	PuntA izq;
	PuntA der;
}NodoA;

//Estructura de la ML
typedef struct Reserva
{
    int dni;
    char nombre[25];
    int nroVuelo;
    int cantPasajes;
}Reserva;
typedef struct NodoL*PuntL;
typedef struct NodoL
{
    Reserva datos;
    PuntL sigDni;
    PuntL sigNom;
}NodoL;

//Prototipos
void actualizarArbol(PuntA &, PuntL &, PuntL &);

//Funcion principal del programa
int main ()
{
	PuntA raiz=NULL;
	
}

//Funciones
void actualizarArbol(PuntA &raiz, PuntL &lDni, PuntL &lNombre)
{
	
}
