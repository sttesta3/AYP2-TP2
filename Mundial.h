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
        void SolicitarEquipo(void);
        // tuple <string, char> ValidarEquipo(string linea);
        
        int MostrarCantidadEquipos(void);
        Equipo* BuscarEquipo(std::string busqueda);
        
        // FUNCIONES DE MENU
        void Menu();
        void FiguraAscii1(void);
        void MostrarMenu(void);
        void ListarEquipos(void);
        void Podio(void);
        void MostrarBuscarEquipo(std::string busqueda);
        void MenuPuntos(void);

        void MenuActualizarPartido(void);
        void AgregarPartido(void);
        void ActualizarPartido(void);
        void EliminarPartido(void);

        bool ValidarMundial(bool verbose);
        bool ValidarGrupo(char input);
        bool Guardado();

        // FUNCIONES DEBUG
        void ListarPartidos(void);
        //void ListarCantFasesPorEquipo(void);

};

#endif // MUNDIAL_H
