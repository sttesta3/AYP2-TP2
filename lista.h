#
#ifndef _LISTA_TEMPLATE_
#define _LISTA_TEMPLATE_

#include "defs.h"

template <typename Tipo> struct Nodo{
    Tipo contenido;
    Nodo* siguiente;
}; 

template <typename Tipo> class Lista {
    
    private:
        int cant_elementos;

        Nodo<Tipo> *inicio;
        Nodo<Tipo> *ultimo;

    public:
        Lista();
        AgregarElemento(Nodo* nuevo);
        
}

template <typename Tipo> Lista<Tipo>::Lista(){
    this->inicio = nullptr;
    this->ultimo = nullptr;
    this->cant_elementos = 0;
}

template <typename Tipo> Lista<Tipo>::~Lista(){
    Nodo* swap = nullptr;
    Nodo* iterador = this->inicio;

    while(!(iterador)){
        swap 
    }
}

template <typename Tipo> int Lista<Tipo>::AgregarElemento(Nodo* nuevo){
    Nodo* swap = this->inicio;
    this->inicio = nuevo;
    nuevo->siguiente = swap;

    // Si el nodo inicialmente apuntaba a NULL, cambialo
    if !(this->ultimo)
        this->ultimo = nuevo;
    
    this->cant_elementos += 1;
}


#endif