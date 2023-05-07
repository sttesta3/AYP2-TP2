#ifndef PARTIDOS_H
#define PARTIDOS_H

#include <tuple>

using namespace std;
class Partido 
{
    public:
        tuple <Equipo*,Equipo*> MostrarEquipos();

        void AsignarValores(Equipo* equipo1, Equipo* equipo2, int goles1, int goles2);
        virtual tuple<int,int> MostrarPuntos(void) = 0;
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
        ~PartidoGrupo();

        //int ValidarPartido(string linea, Mundial* mundial);
        tuple <string,int,string,int> ValidarPartido(string linea);
        void AsignarValores(Equipo* equipo1, Equipo* equipo2, int goles1, int goles2);
        tuple<int,int> MostrarPuntos(void);
    private:
};

class PartidoEliminatoria: public Partido{
    public:
        PartidoEliminatoria();
        ~PartidoEliminatoria();

        tuple<string,int,int,string,int,int> ValidarPartido(string linea);
        void AsignarValores(Equipo* equipo1, Equipo* equipo2, int goles1, int goles2);
        int AsignarPenales(int penales1, int penales2);

        tuple<int,int> MostrarPuntos(void);
        Equipo* MostrarGanador(void);
        Equipo* MostrarPerdedor(void);
    private:
        int penales1;
        int penales2;
};

#endif // PARTIDOS_H
