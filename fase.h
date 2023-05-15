#ifndef FASE_H
#define FASE_H

#include <vector>
#include <string>
#include <tuple>
#include <iostream>

#include "Equipo.h"
//class Equipo;

#include "partidos.h"
//class Partido;
//class PartidoGrupo;
//class PartidoEliminatoria;


class Fase
{
    public:
        Fase();
        ~Fase();           

        void AgregarPartido(Partido* partido);
        bool EliminarPartido(Partido* partido);
        void AsignarFase(std::string fase);

        std::string MostrarFase();
        virtual int CalcularPuntaje(Equipo* equipo) = 0;
        virtual bool PasoFase(Equipo* equipo) = 0;

        std::vector <Partido*> partidos;

    protected:
        std::string fase;
        
};


class FaseGrupo : public Fase{
    public:
        int CalcularPuntaje(Equipo* equipo);
        bool PasoFase(Equipo* equipo);
};

class FaseEliminatoria: public Fase{
    public:
        int CalcularPuntaje(Equipo* equipo);
        bool PasoFase(Equipo* equipo);
        //PartidoEliminatoria* MostrarPartido();
};


#endif // FASE_H
