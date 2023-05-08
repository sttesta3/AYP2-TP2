#ifndef MUNDIAL_H
#define MUNDIAL_H

//#include <string>
//#include <tuple>

#include "lista.h"
#include "partidos.h"
#include "Equipo.h"

// EDIT PARA ERROR DE LINKER
// #include "utils.h"
#include <cmath>
//#include <iostream>
//#include <fstream>
#include <tuple>

class Mundial {
    private:
        Lista <Equipo> *equipos;
        Lista <PartidoGrupo> *partidos_grupos;
        Lista <PartidoEliminatoria> *partidos_eliminatoria;
        int MAXIMO_ITERACIONES;

        Equipo *primero;
        Equipo *segundo;
        Equipo *tercero;

    protected:

    public:
        Mundial();
        ~Mundial();

        // FUNCIONES DE MEMORIA
        int CargarEquipos(std::string archivo1);
        int CargarPartidos(std::string archivo2);
        // 
        // tuple <string, char> ValidarEquipo(string linea);
        
        int MostrarCantidadEquipos(void);
        void DefinirIteraciones();
        Equipo* BuscarEquipo(std::string busqueda);
        
        // FUNCIONES DE MENU
        void Menu();
        void MostrarMenu(void);
        void ListarEquipos(void);
        void Podio(void);
        void MostrarBuscarEquipo(std::string busqueda);
        void MenuPuntos(void);

        int ValidarMundial(void);
        void ActualizarPartidos(void);

};

#endif // MUNDIAL_H
