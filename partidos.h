#ifndef PARTIDOS_H
#define PARTIDOS_H

#include <tuple>

#include "lista.h"
#include "Equipo.h"

class Partido 
{
    public:
        int AsignarValores(Equipo* equipo1, Equipo* equipo2, int goles1, int goles2);
        virtual int ValidarPartido(string linea, Lista<Equipo>* equipos);
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
        ~PartidoGrupo();


        // PartidoGrupo ValidarPartido(string linea);
    private:
};

class PartidoEliminatoria: public Partido{
    public:
        PartidoEliminatoria();
        ~PartidoEliminatoria();

        // PartidoEliminatoria ValidarPartido(string linea);
        int AsignarPenales(int penales1, int penales2);
    private:
        int penales1;
        int penales2;
};

#endif // PARTIDOS_H
