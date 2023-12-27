#include <iostream>

using namespace std;

typedef struct Nodo* Punt;
typedef struct Nodo
{
    int dato;
    Punt sig;
}Nodo;

int factorial(int n);
void factorial(int n,int&fact);

int main()
{
    int nro,factN;
    cin>>nro;
    factorial(nro,factN);//#
    cout<<factN;
    //cout<<factorial(nro)<<endl;
    return 0;
}

int factorial(int n) //n!
{
   if(n==0)
    return 1;
   else
    return n*factorial(n-1);
}

void factorial(int n,int&fact)
{
    if(n==0)
        fact=1;
    else
    {
        int factAnt;
        factorial(n-1,factAnt);//$
        fact=n*factAnt;
    }

}

void listar(Punt lista)
{
    if(lista!=NULL)
    {
        cout<<lista->dato<<endl;
        listar(lista->sig);//#
    }

}

void listarD(Punt lista)
{
    if(lista!=NULL)
    {
        listarD(lista->sig);//#
        cout<<lista->dato<<endl;
    }
}
