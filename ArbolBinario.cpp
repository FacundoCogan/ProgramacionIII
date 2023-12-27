#include <iostream>

using namespace std;


typedef struct NodoA* PuntA;
typedef struct NodoA
{
    int dato;
    PuntA izq;
    PuntA der;
}NodoA;

void listarSim(PuntA raiz)
{
    if(raiz!=NULL)
    {
        listarSim(raiz->izq);//#
        cout<<raiz->dato<<endl;
        listarSim(raiz->der);//$
    }
}

void listarPre(PuntA raiz)
{
    if(raiz!=NULL)
    {
        cout<<raiz->dato<<endl;
        listarPre(raiz->izq);
        listarPre(raiz->der);
    }
}

void listarPost(PuntA raiz)
{
   if(raiz!=NULL)
    {
        listarPost(raiz->izq);
        listarPost(raiz->der);
        cout<<raiz->dato<<endl;
    }
}
int cantNodos(PuntA raiz)
{
    //devuelve la cantidad de nodos que tiene árbol
}
