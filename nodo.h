#ifndef _NODO_TEMPLATE_
#define _NODO_TEMPLATE_
/*
#include <tuple>
#include <string>

#include "Equipo.h"
#include "partidos.h"

using namespace std;

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

        */
        /*
        void AsignarValor(Equipo nuevo_equipo);
        void AsignarValor(PartidoGrupo nuevo_partido);
        void AsignarValor(PartidoEliminatoria nuevo_partido);
        
        
        void AsignarSiguiente(Nodo* siguiente);
        void AsignarAnterior(Nodo* anterior);
        */
       /*
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
*/
/*
template <typename Tipo>
void Nodo<Tipo>::AsignarValor(Equipo nuevo_equipo){
    this->contenido.AsignarNombre(nuevo_equipo->MostrarNombre());
    this->contenido.AsignarGrupo(nuevo_equipo->MostrarGrupo());
};

template <typename Tipo>
void Nodo<Tipo>::AsignarValor(Partido nuevo_partido){
    this->contenido.AsignarValores(valor);
};

template <typename Tipo>
void Nodo<Tipo>::AsignarValor(tuple <string,int,int,string,int,int> valor){
    this->contenido.AsignarValores(valor);
};

*/

#endif