#ifndef _NODO_TEMPLATE_
#define _NODO_TEMPLATE_

#include <tuple>
#include <string>

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
        Nodo* MostrarSiguiente(void);
        Nodo* MostrarAnterior(void);

        void AsignarEquipo(tuple <string, char> nuevo_equipo);
        void AsignarSiguiente(Nodo* siguiente);
        void AsignarAnterior(Nodo* anterior);
};

template <typename Tipo>
Tipo Nodo<Tipo>::MostrarContenido(){
    return this->contenido;
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
void Nodo<Tipo>::AsignarEquipo(tuple <string,char> nuevo_equipo){
    this->contenido.AsignarNombre(get<0>(nuevo_equipo));
    this->contenido.AsignarGrupo(get<1>(nuevo_equipo));
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

#endif