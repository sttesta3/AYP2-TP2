#ifndef MUNDIAL_H
#define MUNDIAL_H

#include "lista.h"
#include "Equipo.h"
//#include "fase.h"
#include "partidos.h"
#include "utils.h"

#include <cmath>
#include <tuple>
#include <cstring>
#include <fstream>

class Mundial {
    private:
        Lista <Equipo> *equipos;
        Lista <Partido*> *partidos;
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

        void AgregarPartido(void);
        void ActualizarPartido(void);
        void BorrarPartido(void);

        bool ValidarMundial(bool verbose);
        bool Guardado();

        // FUNCIONES DEBUG
        void ListarPartidos(void);

};

#endif // MUNDIAL_H
