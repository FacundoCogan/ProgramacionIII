#include <iostream>

using namespace std;


typedef struct NodoA* PuntA;
typedef struct NodoA
{
    int dato;
    PuntA izq;
    PuntA der;
}NodoA;

typedef struct NodoP*PuntP;
typedef struct NodoP
{
    PuntA dato;
    PuntP abajo;
}NodoP;
typedef struct Pila
{
    PuntP tope;
}Pila;

void poner(Pila&,PuntA);
void sacar(Pila&,PuntA&);
void inicializar(Pila&);
bool vacia(Pila);

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
void cantNodos(PuntA raiz,int &cont)  //devuelve la cantidad de nodos que tiene árbol
{
    if(raiz!=NULL)
    {
        cantNodos(raiz->izq);
        cantNodos(raiz->der);
        cont=cont+1;
    }
}
int cantNodos(PuntA raiz)
{
    if(raiz==NULL)
        return 0;
    else
        return cantNodos(raiz->izq)+1+cantNodos(raiz->der);
}
//abb
void listarSimPila(PuntA raiz)
{
    Pila pila;
    inicializar(pila);
    PuntA r=raiz;
    while(r!=NULL || !vacia(pila))
    {
        while(r!=NULL)
        {
            poner(pila,r);
            r=r->izq;
        }
        sacar(pila,r);
        cout<<r->dato;
        r=r->der;
    }
}

PuntA buscar(PuntA raiz,int nro)
{   //devuelve el puntero al nodo encontrado
    //o NULL si no lo encontró
    PuntA r=raiz;
    while(r!=NULL && r->dato!=nro)
    {
        if(nro < r->dato)
            r=r->izq;
        else
            r=r->der;
    }
    return r;
}

PuntA buscarRec(PuntA raiz,int nro)
{
    if(raiz==NULL)
        return NULL;
    else
    {
        if(raiz->dato==nro)
            return raiz;
        else
        {
            if(nro < raiz->dato)
                buscarRec(raiz->izq);
            else
                buscarRec(raiz->der);
        }
    }
}
void agregar(PuntA&raiz,int nro)
{
    PuntA n=new NodoA;
    n->dato=nro;
    n->izq=NULL;
    n->der=NULL;
    if(raiz==NULL)
        raiz=n;
    else
    {
        PuntA ant,r=raiz;
        while(r!=NULL)
        {
            ant=r;
            if(nro < r->dato)
                r=r->izq;
            else
                r=r->der;
        }
        if(nro < ant->dato)
            ant->izq=n;
        else
            ant->der=n;
    }
}

void agregarSinRep(PuntA&raiz,int nro)
{

    if(raiz==NULL)
        raiz=new NodoA;
        raiz->dato=nro;
        raiz->izq=NULL;
        raiz->der=NULL;
    else
    {
        PuntA ant,r=raiz;
        while(r!=NULL && r->dato!=nro)
        {
            ant=r;
            if(nro < r->dato)
                r=r->izq;
            else
                r=r->der;
        }
        if(r==NULL)
        {
            PuntA n=new NodoA;
            n->dato=nro;
            n->izq=NULL;
            n->der=NULL;
            if(nro < ant->dato)
                ant->izq=n;
            else
                ant->der=n;
        }
        else
            cout<<"ya esta"<<endl;
    }
}

void agregarRec(PuntA&raiz,int nro)
{
    if(raiz==NULL)
    {
        raiz=new NodoA;
        raiz->dato=nro;
        raiz->izq=NULL;
        raiz->der=NULL;
    }
    else
    {
        if(nro < raiz->dato)
            agregarRec(raiz->izq,nro);
        else
            agregarRec(raiz->der,nro);
    }
}

void agregarRecSinRep(PuntA&raiz,int nro)
{
    if(raiz==NULL)
    {
        raiz=new NodoA;
        raiz->dato=nro;
        raiz->izq=NULL;
        raiz->der=NULL;
    }
    else
    {
        if(nro!=raiz->dato)
        {
            if(nro < raiz->dato)
                agregarRec(raiz->izq,nro);
            else
                agregarRec(raiz->der,nro);
        }
        else
            cout<<"ya esta";
    }
}
