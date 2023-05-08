#ifndef PARTIDOS_H
#define PARTIDOS_H

//#include <tuple>
//#include <string>
#include "Equipo.h"

class Partido 
{
    public:
        std::tuple <Equipo*,Equipo*> MostrarEquipos();

        virtual void AsignarValores(Equipo* equipo1, Equipo* equipo2, int goles1, int goles2) = 0;
        virtual std::tuple<int,int> MostrarPuntos(void) = 0;
        // virtual int ValidarPartido(string linea, Mundial* mundial) = 0; 
        // virtual int ValidarPartido(string linea, Mundial* mundial) = 0;
        // virtual int CargarDatos(string linea, Lista<Partido>* partidos) = 0;
        // virtual tuple <int,int> DevolverPuntos() = 0;
        // virtual int CargarDatos(string linea, Lista<Partido>* partidos) = 0;

    private:
        Equipo* equipo1;
        Equipo* equipo2;
        int goles1;
        int goles2;
};

class PartidoGrupo: public Partido{
    public:
        PartidoGrupo();
        //~PartidoGrupo();

        //int ValidarPartido(string linea, Mundial* mundial);
        std::tuple<std::string,int,std::string,int> ValidarPartido(std::string linea);
        void AsignarValores(Equipo* equipo1, Equipo* equipo2, int goles1, int goles2);
        std::tuple<int,int> MostrarPuntos(void);
};

class PartidoEliminatoria: public Partido{
    public:
        PartidoEliminatoria();
        // ~PartidoEliminatoria();

        std::tuple<std::string,int,int,std::string,int,int> ValidarPartido(std::string linea);
        void AsignarValores(Equipo* equipo1, Equipo* equipo2, int goles1, int goles2);
        int AsignarPenales(int penales1, int penales2);

        std::tuple<int,int> MostrarPuntos(void);
        Equipo* MostrarGanador(void);
        Equipo* MostrarPerdedor(void);
    private:
        int penales1;
        int penales2;
};

#endif // PARTIDOS_H
