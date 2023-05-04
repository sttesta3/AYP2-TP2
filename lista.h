#ifndef _LISTA_TEMPLATE_
#define _LISTA_TEMPLATE_

#include <tuple>
#include "Equipo.h"
#include "utils.h"

template <typename Tipo> 
struct Nodo{
    private:
        Tipo contenido;
        Nodo* siguiente;
    public:
        Nodo();
        ~Nodo();

        Tipo MostrarContenido(void);
        Nodo* MostrarSiguiente();

        void AsignarEquipo(tuple <string, char> nuevo_equipo);
        void AsignarSiguiente(Nodo* siguiente);

};

template <typename Tipo>
Tipo Nodo<Tipo>::MostrarContenido(){
    return this->contenido;
};

template <typename Tipo>
Nodo<Tipo>* Nodo<Tipo>::MostrarSiguiente(){
    return this->siguiente;
};

template <typename Tipo>
void Nodo<Tipo>::AsignarEquipo(tuple <string,char> nuevo_equipo){
    this->contenido->AsignarNombre(get<0>(nuevo_equipo));
    this->contenido->AsignarGrupo(get<1>(nuevo_equipo));
};

template <typename Tipo>
void Nodo<Tipo>::AsignarSiguiente(Nodo* siguiente){
    this->siguiente = siguiente;
};

template <typename Tipo>
class Lista {
    private:
        int cant_elementos;

        struct Nodo<Tipo> *inicio;
        struct Nodo<Tipo> *ultimo;
        struct Nodo<Tipo> *iterador;

    public:
        Lista();
        ~Lista();

        int MostrarCantElementos();
        Nodo<Tipo>* MostrarPrimerElemento();

        void IniciarIterador();
        Nodo<Tipo>* MostrarIterador();
        void AvanzarIterador(int ITERACIONES);
        void AsignarIterador(Nodo<Tipo>* nodo);

        int AgregarElemento(tuple <string, char> nuevo_equipo);

};

template <class Tipo>
Lista<Tipo>::Lista(void){
    this->inicio = nullptr;
    this->ultimo = nullptr;
    this->IniciarIterador();

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

template <typename Tipo>
void Lista<Tipo>::IniciarIterador(){
    this->AsignarIterador(this->inicio);
}

template <typename Tipo>
Nodo<Tipo>* Lista<Tipo>::MostrarIterador(){
    return this->iterador;
}
template <typename Tipo>
void Lista<Tipo>::AsignarIterador(Nodo<Tipo>* nodo){
    this->iterador = nodo;
}

template <typename Tipo>
void Lista<Tipo>::AvanzarIterador(int ITERACIONES){
    int i = 0;
    while (this->MostrarIterador() != nullptr && i < ITERACIONES){
        this->AsignarIterador(this->siguiente);
        i += 1;
    }
}

template <class Equipo>
int Lista<Equipo>::AgregarElemento(tuple <string, char> nuevo_equipo){
    struct Nodo<Equipo> *nuevo_nodo = new Nodo<Equipo>;
    if (!nuevo_nodo){
        delete nuevo_nodo;
        cerr << "ERROR AL AGREGAR EQUIPO: " << get<0>(nuevo_equipo) << endl;
        return 1;
    }
    nuevo_nodo->AsignarEquipo(nuevo_equipo);
    
    // Agregamos nodo en posicion correcta
    this->IniciarIterador();
    Nodo<Equipo>* anterior = nullptr;
    while (comparar_alfabeticamente(nuevo_nodo->MostrarContenido().MostrarNombre(),this->iterador->MostrarContenido().MostrarNombre()) != -1){
        anterior = iterador;
        this->AvanzarIterador(1);
    }

    nuevo_nodo->AsignarSiguiente(iterador);
    anterior->AsignarSiguiente(nuevo_nodo);

    return 0;
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

    // Agregamos nodo en posici�n correcta
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
        siguiente = iterador->MostrarSiguiente();
        delete iterador;
        iterador = siguiente;
    }

    this->inicio = nullptr;
}

#endif
