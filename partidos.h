#ifndef PARTIDOS_H
#define PARTIDOS_H

class Equipo;
//#include "Equipo.h"

#include <tuple>
#include <string>
#include <iostream>

#include "utils.h"

class Partido 
{
    public:
        Equipo* MostrarEquipos(bool equipo1);
        void AsignarEquipo(Equipo* equipo, bool equipo1);
        void AsignarGoles(int goles, bool equipo1);
        void AsignarLinea(int linea);
        virtual std::tuple<int,int> MostrarPuntos() = 0;
        // virtual int CalcularPuntaje(Equipo* equipo) = 0;
        virtual Equipo* MostrarGanador() = 0;
        virtual Equipo* MostrarPerdedor() = 0;

        virtual void AsignarValores(Equipo* equipo1, Equipo* equipo2, int goles1, int goles2) = 0;
        virtual std::tuple<std::string,std::string> ValidarPartido(std::string linea) = 0;

        // virtual int ValidarPartido(string linea, Mundial* mundial) = 0; 
        // virtual int ValidarPartido(string linea, Mundial* mundial) = 0;
        // virtual int CargarDatos(string linea, Lista<Partido>* partidos) = 0;
        // virtual tuple <int,int> DevolverPuntos() = 0;
        // virtual int CargarDatos(string linea, Lista<Partido>* partidos) = 0;

    protected:
        // virtual std::tuple<int,int> MostrarPuntos(void) = 0;
    
    protected:
    //private:
        Equipo* equipo1;
        Equipo* equipo2;
        int goles1;
        int goles2;

        bool original_de_archivo;
        bool editado;
        int linea;
};

class PartidoGrupo: public Partido{
    public:
        PartidoGrupo();
        //~PartidoGrupo();

        std::tuple<std::string,std::string> ValidarPartido(std::string linea);
        void AsignarValores(Equipo* equipo1, Equipo* equipo2, int goles1, int goles2);
        
        std::tuple<int,int> MostrarPuntos(void);
        std::tuple<int,int> MostrarGoles(void);
        Equipo* MostrarEquipo(bool equipo1);
        Equipo* MostrarGanador();
        Equipo* MostrarPerdedor();
        
};

class PartidoEliminatoria: public Partido{
    public:
        PartidoEliminatoria();
        void AsignarPenales(int penales1, int penales2);

        // ~PartidoEliminatoria();
        std::tuple<std::string,std::string> ValidarPartido(std::string linea);
        void AsignarValores(Equipo* equipo1, Equipo* equipo2, int goles1, int goles2);

        std::tuple<int,int> MostrarPuntos(void);
        Equipo* MostrarEquipo(bool equipo1);
        Equipo* MostrarGanador();
        Equipo* MostrarPerdedor();
        
    private:
        int penales1;
        int penales2;
};

#endif // PARTIDOS_H
