#ifndef PARTIDOS_H
#define PARTIDOS_H

#include <tuple>

#include "Equipo.h"

class Partido
{
    public:
        Partido();
        ~Partido();
        virtual int AsignarValor(void);
        virtual void ValidarPartido(string linea);
        virtual Equipo* DevolverGanador() = 0;
        virtual tuple <int,int> DevolverPuntos() = 0;

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
    private:

};

class PartidoEliminatoria: public Partido{
    public:
        PartidoEliminatoria();
        ~PartidoEliminatoria();

    private:
        int penales1;
        int penales2;
};

#endif // PARTIDOS_H
