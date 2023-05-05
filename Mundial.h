#ifndef MUNDIAL_H
#define MUNDIAL_H

#include <string>
#include <tuple>

#include "nodo.h"
#include "lista.h"
#include "Equipo.h"

class Mundial {
    private:
        Lista <Equipo> *equipos;
        Lista <Partido> *partidos;
        int MAXIMO_ITERACIONES;

        Nodo<Equipo> *primero;
        Nodo<Equipo> *segundo;
        Nodo<Equipo> *tercero;

    protected:

    public:
        Mundial();
        ~Mundial();

        // FUNCIONES DE MEMORIA
        int CargarEquipos(string archivo1);
        int CargarPartidos(string archivo2);

        int ValidarMundial(void);
        tuple <string, char> ValidarEquipo(string linea);
        int MostrarCantidadEquipos(void);
        int DefinirIteraciones(int a);


        // FUNCIONES DE MENU
        void Menu();
        void MostrarMenu(void);
        void ListarEquipos(void);
        void Podio(void);
        void MostrarBuscarEquipo(string equipo);
        void MenuPuntos(void);
        void ActualizarPartidos(void);
};

#endif // MUNDIAL_H
