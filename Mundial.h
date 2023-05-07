#ifndef MUNDIAL_H
#define MUNDIAL_H

#include <string>
#include <tuple>

#include "lista.h"
#include "partidos.h"
#include "Equipo.h"

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
        int CargarEquipos(string archivo1);
        int CargarPartidos(string archivo2);
        // 
        // tuple <string, char> ValidarEquipo(string linea);
        
        int MostrarCantidadEquipos(void);
        void DefinirIteraciones();
        Equipo* BuscarEquipo(string busqueda);
        
        // FUNCIONES DE MENU
        void Menu();
        void MostrarMenu(void);
        void ListarEquipos(void);
        void Podio(void);
        void MostrarBuscarEquipo(string busqueda);
        void MenuPuntos(void);

        int ValidarMundial(void);
        void ActualizarPartidos(void);

};

#endif // MUNDIAL_H
