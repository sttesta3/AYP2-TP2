#ifndef _LISTA_TEMPLATE_
#define _LISTA_TEMPLATE_

#include <tuple>
#include <string>
#include "nodo.h"
#include "Equipo.h"
#include "utils.h"

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
        void RetrocederIterador(int ITERACIONES);
        
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
        this->AsignarIterador(this->MostrarIterador()->MostrarSiguiente());
        i += 1;
    }
}

template <class Equipo>
int Lista<Equipo>::AgregarElemento(tuple <string, char> nuevo_equipo){
    // CREAMOS NODO Y ASIGNAMOS VALORES
    struct Nodo<Equipo> *nuevo_nodo = new Nodo<Equipo>;
    if (!nuevo_nodo){
        delete nuevo_nodo;
        cerr << "ERROR AL AGREGAR EQUIPO: " << get<0>(nuevo_equipo) << endl;
        return 1;
    }
    nuevo_nodo->AsignarEquipo(nuevo_equipo);
    
    // Buscamos posicion correcta del equipo
    this->IniciarIterador();
    cout << "ITERADOR INICIADO" << endl;
    while (this->MostrarIterador() != nullptr && comparar_alfabeticamente(nuevo_nodo->MostrarContenido().MostrarNombre(),this->iterador->MostrarContenido().MostrarNombre()) != -1){
        this->AvanzarIterador(1);
    }

    // ASIGNAMOS SEGUN SEA EL CASO (se hardcodea demas para evitar problemas con las puntas de la lista)
    if (this->MostrarCantElementos() == 0){                 // PRIMER ELEMENTO
        nuevo_nodo->AsignarAnterior(nullptr);
        nuevo_nodo->AsignarSiguiente(nullptr);

        this->inicio = nuevo_nodo;
        this->ultimo = nuevo_nodo;
    }
    else if (this->MostrarIterador() == this->inicio){     // INICIO DE LISTA
        cout << "ESTAMOS EN EL INICIO" << endl;
        nuevo_nodo->AsignarAnterior(nullptr);
        nuevo_nodo->AsignarSiguiente(this->inicio);

        (nuevo_nodo->MostrarSiguiente())->AsignarAnterior(nuevo_nodo);
        this->inicio = nuevo_nodo;
    }
    else if (this->MostrarIterador() == nullptr){           // FINAL DE LA LISTA
        cout << "ESTAMOS EN EL FINAL" << endl;
        nuevo_nodo->AsignarAnterior(this->ultimo);
        nuevo_nodo->AsignarSiguiente(nullptr);

        (nuevo_nodo->MostrarAnterior())->AsignarSiguiente(nuevo_nodo);
        this->ultimo = nuevo_nodo;
    }
    else{
        nuevo_nodo->AsignarSiguiente(iterador);
        nuevo_nodo->AsignarAnterior(iterador->MostrarAnterior());

        (nuevo_nodo->MostrarAnterior())->AsignarSiguiente(nuevo_nodo);
        (nuevo_nodo->MostrarSiguiente())->AsignarAnterior(nuevo_nodo);
    }

    this->cant_elementos += 1;
    return 0;
}

template <typename Tipo> 
Lista<Tipo>::~Lista(){
    this->IniciarIterador();
    this->inicio = nullptr;
    this->ultimo = nullptr;

    Nodo<Tipo>* siguiente;
    while(this->iterador != nullptr){
        siguiente = iterador->MostrarSiguiente();
        delete this->iterador;
        this->iterador = siguiente;
    }
}

#endif
