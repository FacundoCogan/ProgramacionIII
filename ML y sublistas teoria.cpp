#include <iostream>
#include <string.h>

using namespace std;

typedef struct Empleado
{
    int leg;
    char nom[21];
}Empleado;
typedef struct NodoSub*PuntSub;
typedef struct NodoSub
{
    Empleado info;
    PuntSub sig;
}NodoSub;

typedef struct Oficina
{
    int nro;
    char nombre[15];
    int piso;
    PuntSub listaEmple;
}Oficina;
typedef struct NodoL*PuntL;
typedef struct NodoL
{
    Oficina info;
    PuntL sigNro;
    PuntL sigNom;
    PuntL sigPiso;
}NodoL;


void agregar(PuntL &lNro,PuntL &lNom,PuntL &l1,PuntL &l2,PuntL &l3,Oficina ofi)
{
    PuntL n=new NodoL;
    n->info=ofi;
    agregarLogNro(lNro,n);
    agregarLogNom(lNom,n);
    switch(ofi.piso)
    {
        case 1:
            agregarLogPiso(l1,n);
            break;
        case 2:
            agregarLogPiso(l2,n);
            break;
        case 3:
            agregarLogPiso(l3,n);
            break;
    }
}

void agregarLogNro(PuntL &lista,PuntL n)
{
    PuntL r=lista;
    while(r!=NULL && r->info.nro<n->info.nro)
    {
        ant=r;
        r=r->sigNro;
    }
    n->sigNro=r;
    if(r!=lista)
        ant->sigNro=n;
    else
        lista=n;
}
void agregarLogNom(PuntL &lista,PuntL n)
{
    PuntL r=lista;
    while(r!=NULL && strcmp(r->info.nombre,n->info.nombre)<0)
    {
        ant=r;
        r=r->sigNom;
    }
    n->sigNom=r;
    if(r!=lista)
        ant->sigNom=n;
    else
        lista=n;
}
void agregarLogPiso(PuntL &lista,PuntL n)
{
    PuntL r=lista;
    while(r!=NULL && r->info.nro<n->info.nro)
    {
        ant=r;
        r=r->sigPiso;
    }
    n->sigPiso=r;
    if(r!=lista)
        ant->sigPiso=n;
    else
        lista=n;
}

void eliminar(PuntL &lNro,PuntL &lNom,PuntL &l1,PuntL &l2,PuntL &l3,int nroOfiElim)
{
    PuntL p;
    p=buscaElimLogNro(lNro,nroOfiElim);
    if(p!=NULL)
    {
        eliminaLogNom(lNom,p);
        switch(p->info.piso)
        {
            case 1:
                elimLogPiso(l1,p);
                break;
            case 2:
                elimLogPiso(l2,p);
                break;
        case 3:
                elimLogPiso(l3,p);
                break;
        }
    }
    eliminarLista(p->info.listaEmple);
    delete p;
}
PuntL buscaElimLogNro(PuntL &lista,int nofi)
{
    PuntL r=lista,ant;
    while(r!=NULL && r->info.nro<nofi)
    {
        ant=r;
        r=r->sigNro;
    }

    if(r==NULL || r->info.nro!=nofi)
        return NULL;
    else
    {
        if(r!=lista)
            ant->sigNro=r->sigNro;
        else
            lista=r->sigNro;
        return r;
    }
}
void eliminaLogNom(PuntL &lista,PuntL p)
{
    PuntL r=lista,ant;
    while(r!=NULL && r!=p)
    {
        ant=r;
        r=r->sigNom;
    }

    if(r==p)//r!=NULL
    {
        if(r!=lista)
            ant->sigNom=r->sigNom;
        else
            lista=r->sigNom;

    }
}
void eliminaLogPiso(PuntL &lista,PuntL p)
{
    PuntL r=lista,ant;
    while(r!=NULL && r!=p)
    {
        ant=r;
        r=r->sigPiso;
    }

    if(r==p)//r!=NULL
    {
        if(r!=lista)
            ant->sigPiso=r->sigPiso;
        else
            lista=r->sigPiso;

    }
}
void eliminarLista(PuntSub &lista)
{
    PuntSub paux;
    while(lista!=NULL)
    {
        paux=lista;
        lista=lista->sig;
        delete paux;
    }
}

void listadoPiso(PuntL l)
{
//listar las oficinas ordenadas por número
//de un piso
//el listado debe tener
//nro oficina, nombre y cantidad de empleados
    PuntL r=l;
    while(r!=NULL)
    {
        cout<<r->info.nro<<r->info.nombre<<cantidad(r->info.listaEmple)<<endl;
        r=r->sigPiso;
    }
}

int cantidad(PuntSub lis)
{
    int cont=0;
    PuntSub r=lis;
    while(r!=NULL)
    {
        cont++;
        r=r->sig;
    }
    return cont;
}

void listarNro (PuntL l1) //Horacio muesra empleados
{

   PuntL r; // variable auxiliar r para recorrer

   r = l1; // le paso a r la entrada a l1 de piso 1

   while (r != NULL) // mientras la lista del piso 1 no este vacia

   {

      //declaro una variable puntero a lista de empleados

      PuntSub s;

      //MAL s = unaOficina.listaEmple; // a s le asigno la sublista de empleados
        s=r->info.listaEmple;
      //muestro la oficina

      cout << " Oficina n° : " << r->info.nro << endl;

      cout << " Oficina Nombre: : " << r->info.nombre << endl;

      cout << " Oficina Piso n° : " << r->info.piso << endl;

      // mientras el puntero de la sublista empleados no este vacia

      while ( s != NULL )

      {

         cout << " Empleado : " << s->info.nombre << endl;

         cout << " No me acuerdo que mas tenia el nodo de un empleado : " << s->empleado.nomeacuerdo;

         //muestro el siguiente empleado

         s=s->sig;



      }
        r=r->sigPiso;
   }
}
