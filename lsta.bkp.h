/*#ifndef LISTA_H
#define LISTA_H

//#include <tuple>
//#include <string>

#include "Equipo.h"
#include "partidos.h"
#include "utils.h"
#include <cstring>

// using namespace std;

template <typename Tipo> 
class Nodo{
    private:
        Tipo contenido;

        Nodo<Tipo>* siguiente;
        Nodo<Tipo>* anterior;
    public:
        Nodo();
        ~Nodo();

        Tipo MostrarContenido(void);
        Tipo* MostrarDireccion(void);
        Nodo* MostrarSiguiente(void);
        Nodo* MostrarAnterior(void);

        void AsignarContenido(Tipo contenido);
        /*
        void AsignarValor(Equipo nuevo_equipo);
        void AsignarValor(PartidoGrupo nuevo_partido);
        void AsignarValor(PartidoEliminatoria nuevo_partido);
        */
        
        void AsignarSiguiente(Nodo* siguiente);
        void AsignarAnterior(Nodo* anterior);
};

template <typename Tipo>
Tipo Nodo<Tipo>::MostrarContenido(){
    return this->contenido;
};

template <typename Tipo>
Tipo* Nodo<Tipo>::MostrarDireccion(){
    return &this->contenido;
};

template <typename Tipo>
Nodo<Tipo>* Nodo<Tipo>::MostrarAnterior(){
    return this->anterior;
};

template <typename Tipo>
Nodo<Tipo>* Nodo<Tipo>::MostrarSiguiente(){
    return this->siguiente;
};

template <typename Tipo>
void Nodo<Tipo>::AsignarContenido(Tipo contenido){
    this->contenido = contenido;
};

template <typename Tipo>
void Nodo<Tipo>::AsignarSiguiente(Nodo* siguiente){
    this->siguiente = siguiente;
};

template <typename Tipo>
void Nodo<Tipo>::AsignarAnterior(Nodo* anterior){
    this->anterior = anterior;
};

template <typename Tipo>
Nodo<Tipo>::Nodo(){
    
};

template <typename Tipo>
Nodo<Tipo>::~Nodo(){
    
};

//########################################################################################################################################
//########################################################################################################################################
//########################################################################################################################################
//########################################################################################################################################
//########################################################################################################################################
//########################################################################################################################################
//########################################################################################################################################

// HASTA ACA LO DE NODO
template <typename Tipo>
class Lista {
    private:
        int cant_elementos;

        Nodo<Tipo> *inicio;
        Nodo<Tipo> *ultimo;

        Nodo<Tipo> *iterador;

    public:
        Lista();
        ~Lista();

        // MOSTRAR Y AGREGAR
        int MostrarCantElementos();
        Nodo<Tipo>* MostrarPrimerElemento();
        int AgregarElemento(Tipo nuevo_elemento);
        
        // int EliminarElemento(Nodo<Tipo>* nodo);

        //int EncontrarPosicionElemento(Nodo<Tipo>* nuevo_nodo);
        int PosicionarElemento(Nodo<Equipo>* nuevo_nodo){
            bool busqueda_normal = (nuevo_nodo->MostrarContenido().MostrarNombre()[0] < 110);

            if (false){
                this->IniciarIterador();
                // DEBUG cout << "ITERADOR INICIADO" << endl;
                while (this->MostrarIterador() != nullptr && comparar_alfabeticamente(nuevo_nodo->MostrarContenido().MostrarNombre(),this->iterador->MostrarContenido().MostrarNombre()) != -1)
                    this->AvanzarIterador(1); 
            }
            else{
                this->IniciarIteradorAlUltimo();

                while (this->MostrarIterador() != nullptr && comparar_alfabeticamente(nuevo_nodo->MostrarContenido().MostrarNombre(),this->iterador->MostrarContenido().MostrarNombre()) != 1)
                    this->RetrocederIterador(1); 
            }

            // ASIGNAMOS SEGUN SEA EL CASO (se hardcodea demas para evitar problemas con las puntas de la lista)
            if (this->MostrarCantElementos() == 0){                 // PRIMER ELEMENTO
                nuevo_nodo->AsignarAnterior(nullptr);
                nuevo_nodo->AsignarSiguiente(nullptr);

                this->inicio = nuevo_nodo;
                this->ultimo = nuevo_nodo;
            }
            else if (busqueda_normal){
                if (this->MostrarIterador() == this->inicio){     // INICIO DE LISTA
                    // DEBUG: cout << "ESTAMOS EN EL INICIO" << endl;
                    nuevo_nodo->AsignarAnterior(nullptr);
                    nuevo_nodo->AsignarSiguiente(this->inicio);

                    (nuevo_nodo->MostrarSiguiente())->AsignarAnterior(nuevo_nodo);
                    this->inicio = nuevo_nodo;
                }
                else if (this->MostrarIterador() == nullptr){           // FINAL DE LA LISTA
                    // DEBUG: cout << "ESTAMOS EN EL FINAL" << endl;
                    nuevo_nodo->AsignarAnterior(this->ultimo);
                    nuevo_nodo->AsignarSiguiente(nullptr);

                    (nuevo_nodo->MostrarAnterior())->AsignarSiguiente(nuevo_nodo);
                    this->ultimo = nuevo_nodo;
                }
                else{
                    nuevo_nodo->AsignarSiguiente(this->MostrarIterador());
                    nuevo_nodo->AsignarAnterior(this->iterador->MostrarAnterior());

                    (nuevo_nodo->MostrarAnterior())->AsignarSiguiente(nuevo_nodo);
                    (nuevo_nodo->MostrarSiguiente())->AsignarAnterior(nuevo_nodo);
                }
            }
            else {
                if (this->MostrarIterador() == this->ultimo){   // FINAL DE LISTA
                    nuevo_nodo->AsignarAnterior(this->ultimo);
                    nuevo_nodo->AsignarSiguiente(nullptr);

                    (nuevo_nodo->MostrarAnterior())->AsignarSiguiente(nuevo_nodo);
                    this->ultimo = nuevo_nodo;
                }
                else if (this->MostrarIterador() == nullptr){   // INICIO DE LISTA
                    nuevo_nodo->AsignarAnterior(nullptr);
                    nuevo_nodo->AsignarSiguiente(this->inicio);

                    (nuevo_nodo->MostrarSiguiente())->AsignarAnterior(nuevo_nodo);
                    this->inicio = nuevo_nodo;
                }
                else {
                    nuevo_nodo->AsignarAnterior(this->MostrarIterador());
                    nuevo_nodo->AsignarSiguiente(this->iterador->MostrarSiguiente());

                    (nuevo_nodo->MostrarAnterior())->AsignarSiguiente(nuevo_nodo);
                    (nuevo_nodo->MostrarSiguiente())->AsignarAnterior(nuevo_nodo);
                }
            }

            this->cant_elementos += 1;
            return 0;
        }

        int PosicionarElemento(Nodo<PartidoGrupo>* nuevo_nodo){
            std::cout << "AGREGANDO PG NUEVO" << std::endl;
            if (this->MostrarCantElementos() == 0){                 // PRIMER ELEMENTO
                nuevo_nodo->AsignarAnterior(nullptr);
                nuevo_nodo->AsignarSiguiente(nullptr);

                this->inicio = nuevo_nodo;
                this->ultimo = nuevo_nodo;
            }
            else{
                nuevo_nodo->AsignarAnterior(nullptr);
                nuevo_nodo->AsignarSiguiente(this->inicio);

                (nuevo_nodo->MostrarSiguiente())->AsignarAnterior(nuevo_nodo);
                this->inicio = nuevo_nodo;
            }

            this->cant_elementos += 1;
            std::cout << "AGREGADO PG" << std::endl;
            return 0;
        }

        int PosicionarElemento(Nodo<PartidoEliminatoria>* nuevo_nodo){
            if (this->MostrarCantElementos() == 0){                 // PRIMER ELEMENTO
                nuevo_nodo->AsignarAnterior(nullptr);
                nuevo_nodo->AsignarSiguiente(nullptr);

                this->inicio = nuevo_nodo;
                this->ultimo = nuevo_nodo;
            }
            else{
                nuevo_nodo->AsignarAnterior(this->ultimo);
                nuevo_nodo->AsignarSiguiente(nullptr);

                (nuevo_nodo->MostrarAnterior())->AsignarSiguiente(nuevo_nodo);
                this->ultimo = nuevo_nodo;
            }

            this->cant_elementos += 1;
            return 0;
        }

        //int EncontrarPosicionPartido(Nodo<Partido>* nuevo_nodo);

        Tipo* BuscarElemento(std::string busqueda);

        // FUNCIONES DE ITERADOR
        void IniciarIterador();
        void IniciarIteradorAlUltimo();
        Nodo<Tipo>* MostrarIterador();
        void AvanzarIterador(int ITERACIONES);
        void RetrocederIterador(int ITERACIONES);
        void AsignarIterador(Nodo<Tipo>* nodo);

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
void Lista<Tipo>::IniciarIteradorAlUltimo(){
    this->AsignarIterador(this->ultimo);
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

template <typename Tipo>
void Lista<Tipo>::RetrocederIterador(int ITERACIONES){
    int i = 0;
    while (this->MostrarIterador() != nullptr && i < ITERACIONES){
        this->AsignarIterador(this->MostrarIterador()->MostrarAnterior());
        i += 1;
    }
}

template <typename Tipo>
int Lista<Tipo>::AgregarElemento(Tipo nuevo_elemento){
    // CREAMOS NODO Y ASIGNAMOS VALORES
    Nodo<Tipo> *nuevo_nodo = new Nodo<Tipo>;
    if (!nuevo_nodo){
        delete nuevo_nodo;
        std::cerr << "ERROR DE MEMORIA AL AGREGAR NUEVO NODO: " << std::endl;
        return 1;
    }
    nuevo_nodo->AsignarContenido(nuevo_elemento);
    /*
    ACA ESTABA EL CODIGO DE ENCONTRAR POSICION A EQUIPO
    */
    return this->PosicionarElemento(nuevo_nodo);
}

/*
int Lista<Equipo>::PosicionarElemento(Nodo<Equipo>* nuevo_nodo){
// BUSCAMOS POSICION CORRECTA, EMPEZANDO POR INICIO O FINAL SEGUN LA LETRA CON QUE EMPIECE EL EQUIPO    
    bool busqueda_normal = (nuevo_nodo->MostrarContenido().MostrarNombre()[0] < 110);
    if (busqueda_normal){
        this->IniciarIterador();
        // DEBUG cout << "ITERADOR INICIADO" << endl;
        while (this->MostrarIterador() != nullptr && comparar_alfabeticamente(nuevo_nodo->MostrarContenido().MostrarNombre(),this->iterador->MostrarContenido().MostrarNombre()) != -1)
            this->AvanzarIterador(1);
    }
    else{
        this->IniciarIteradorAlUltimo();

        while (this->MostrarIterador() != nullptr && comparar_alfabeticamente(nuevo_nodo->MostrarContenido().MostrarNombre(),this->iterador->MostrarContenido().MostrarNombre()) != 1)
            this->RetrocederIterador(1);
    }

    // ASIGNAMOS SEGUN SEA EL CASO (se hardcodea demas para evitar problemas con las puntas de la lista)
    if (this->MostrarCantElementos() == 0){                 // PRIMER ELEMENTO
        nuevo_nodo->AsignarAnterior(nullptr);
        nuevo_nodo->AsignarSiguiente(nullptr);

        this->inicio = nuevo_nodo;
        this->ultimo = nuevo_nodo;
    }
    else if (this->MostrarIterador() == this->inicio){     // INICIO DE LISTA
        // DEBUG: cout << "ESTAMOS EN EL INICIO" << endl;
        nuevo_nodo->AsignarAnterior(nullptr);
        nuevo_nodo->AsignarSiguiente(this->inicio);

        (nuevo_nodo->MostrarSiguiente())->AsignarAnterior(nuevo_nodo);
        this->inicio = nuevo_nodo;
    }
    else if (this->MostrarIterador() == nullptr){           // FINAL DE LA LISTA
        // DEBUG: cout << "ESTAMOS EN EL FINAL" << endl;
        nuevo_nodo->AsignarAnterior(this->ultimo);
        nuevo_nodo->AsignarSiguiente(nullptr);

        (nuevo_nodo->MostrarAnterior())->AsignarSiguiente(nuevo_nodo);
        this->ultimo = nuevo_nodo;
    }
    else{
        nuevo_nodo->AsignarSiguiente(this->MostrarIterador());
        nuevo_nodo->AsignarAnterior(this->iterador->MostrarAnterior());

        (nuevo_nodo->MostrarAnterior())->AsignarSiguiente(nuevo_nodo);
        (nuevo_nodo->MostrarSiguiente())->AsignarAnterior(nuevo_nodo);
    }

    this->cant_elementos += 1;
    return 0;
}


int Lista<PartidoGrupo>::PosicionarElemento(Nodo<PartidoGrupo>* nuevo_nodo){
    if (this->MostrarCantElementos() == 0){                 // PRIMER ELEMENTO
        nuevo_nodo->AsignarAnterior(nullptr);
        nuevo_nodo->AsignarSiguiente(nullptr);

        this->inicio = nuevo_nodo;
        this->ultimo = nuevo_nodo;
    }
    else{     // INICIO DE LISTA
        // DEBUG: cout << "ESTAMOS EN EL INICIO" << endl;
        nuevo_nodo->AsignarAnterior(nullptr);
        nuevo_nodo->AsignarSiguiente(this->inicio);

        (nuevo_nodo->MostrarSiguiente())->AsignarAnterior(nuevo_nodo);
        this->inicio = nuevo_nodo;
    }
}

template <class PartidoEliminatoria>
int Lista<PartidoEliminatoria>::PosicionarElemento(Nodo<PartidoEliminatoria>* nuevo_nodo){
    if (this->MostrarCantElementos() == 0){                 // PRIMER ELEMENTO
        nuevo_nodo->AsignarAnterior(nullptr);
        nuevo_nodo->AsignarSiguiente(nullptr);

        this->inicio = nuevo_nodo;
        this->ultimo = nuevo_nodo;
    }
    else{     // FINAL DE LISTA
        // DEBUG: cout << "ESTAMOS EN EL INICIO" << endl;
        nuevo_nodo->AsignarAnterior(this->ultimo);
        nuevo_nodo->AsignarSiguiente(nullptr);

        (nuevo_nodo->MostrarAnterior())->AsignarSiguiente(nuevo_nodo);
        this->ultimo = nuevo_nodo;
    }
}
*/

/*
template <class Partido>
int Lista<Partido>::AgregarElemento(tuple <string, int, string, int> nuevo_partido_grupo){
    Nodo<PartidoGrupo> *nuevo_nodo = new Nodo<PartidoGrupo>;
    if (!nuevo_nodo){
        delete nuevo_nodo;
        cerr << "ERROR AL AGREGAR PARTIDO: " << get<0>(nuevo_partido_grupo) "vs" << get<2>(nuevo_partido_grupo) << endl;
        return 1;
    }
    nuevo_nodo->AsignarPartido(nuevo_partido_grupo);
}


template <typename Tipo> 
Lista<Tipo>::~Lista(){
    this->IniciarIterador();
    this->inicio = nullptr;
    this->ultimo = nullptr;

    Nodo<Tipo>* siguiente;
    while(this->iterador != nullptr){
        siguiente = this->iterador->MostrarSiguiente();
        delete this->iterador;
        this->iterador = siguiente;
    }
}

#endif // LISTA_H
*/