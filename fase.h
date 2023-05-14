#ifndef FASE_H
#define FASE_H

#include <vector>
#include <string>
//#include "partidos.h"
class Partido;

class Fase
{
    public:
        Fase();
        ~Fase();           

        void AgregarPartido(Partido* partido);
        bool EliminarPartido(Partido* partido);
        void AsignarFase(std::string fase);

        std::string MostrarFase();
        //virtual int CalcularPuntaje(Equipo* equipo) = 0;
        //virtual bool PasoFase(Equipo* equipo) = 0;

    protected:
        std::vector <Partido*> partidos;
        std::string fase;
        
};

/*
class FaseGrupo : public Fase{
    public:
        int CalcularPuntaje(Equipo* equipo);
        bool PasoFase(Equipo* equipo);
};

class FaseEliminatoria: public Fase{
    public:
        int CalcularPuntaje(Equipo* equipo);
        bool PasoFase(Equipo* equipo);
};
*/

#endif // FASE_H
