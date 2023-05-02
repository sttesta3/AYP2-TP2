#ifndef _LISTA_TEMPLATE_
#define _LISTA_TEMPLATE_

#include <tuple>
#include "Equipo.h"

template <typename Tipo> struct Nodo{
    Tipo contenido;
    Nodo* siguiente;
};

template <typename Tipo>
class Lista {
    private:
        int cant_elementos;

        Nodo<Tipo> *inicio;
        Nodo<Tipo> *ultimo;

    public:
        Lista();
        ~Lista();

        int MostrarCantElementos();
        Nodo<Tipo>* MostrarPrimerElemento();

        int AgregarElemento(tuple <string, char> nuevo_equipo);
};

template <class Tipo>
Lista<Tipo>::Lista(void){
    this->inicio = nullptr;
    this->ultimo = nullptr;
    this->cant_elementos = 0;
}

template <typename Tipo>
int Lista<Tipo>::MostrarCantElementos(){
    return this->cant_elementos;
}

template <typename Tipo>
Nodo<Tipo>* Lista<Tipo>::MostrarPrimerElemento(){
    return this->inicio;
}

template <class Equipo>
int Lista<Equipo>::AgregarElemento(tuple <string, char> nuevo_equipo){
    Nodo<Equipo> *nuevo_nodo = new Nodo<Equipo>;
    if (!nuevo_nodo){
        delete nuevo_nodo;
        cerr << "ERROR AL AGREGAR EQUIPO: " << get<0>(nuevo_equipo) << endl;
        return 1;
    }
    nuevo_nodo->contenido->nombre = get<0>(nuevo_equipo);
    nuevo_nodo->contenido->grupo = get<1>(nuevo_equipo);

    // Agregamos nodo en posición correcta
    Nodo<Equipo>* iterador = this->inicio;
    Nodo<Equipo>* anterior = nullptr;
    while (comparar_alfabeticamente(nuevo_nodo->nombre,iterador->contenido->nombre) != -1){
            anterior = iterador;
            iterador = iterador->siguiente;
    }

    nuevo_nodo->siguiente = iterador;
    anterior->siguiente = nuevo_nodo;

    return 0;
    // AGREGAMOS N
}

/*
template <typename Tipo>
int Lista<Tipo>::AgregarElemento(Tipo nuevo_elemento){
    // Inicializamos nuevo nodo
    Nodo<Tipo>* nuevo = new Nodo<Tipo>;
    if (!nuevo){
        delete nuevo;
        return 1;
    }
    nuevo->contenido = nuevo_elemento;

    // Agregamos nodo en posición correcta
    Nodo<Tipo>* iterador = this->inicio;
    Nodo<Tipo>* anterior = nullptr;
    while (comparar_alfabeticamente(nuevo_elemento->nombre,iterador->contenido->nombre) != -1){
            anterior = iterador;
            iterador = iterador->siguiente;
    }
    nuevo->siguiente = iterador;
    anterior->siguiente = nuevo;


    return 0;
    // AGREGAMOS NODO AL PRINCIPIO
    // Nodo<Tipo>* auxiliar = this->inicio;
    // this->inicio = nuevo;
    // nuevo->siguiente = auxiliar;

}
*/

template <typename Tipo> Lista<Tipo>::~Lista(){
    Nodo<Tipo>* siguiente = nullptr;
    Nodo<Tipo>* iterador = this->inicio;

    while(!(iterador)){
        siguiente = iterador->siguiente;
        delete iterador;
        iterador = siguiente;
    }

    this->inicio = nullptr;
}

#endif
