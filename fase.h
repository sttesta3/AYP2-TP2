#ifndef FASE_H
#define FASE_H

#include <vector>
#include "partidos.h"

class Fase
{
    public:
        /*
        Fase();
        ~Fase();
        */
        //void AgregarPartido();
        //void EliminarPartido();
        //virtual int CalcularPuntaje() = 0;
        //virtual int AgregarPartido() = 0;
        //virtual void ModificarPartido() = 0;

    protected:
        vector <Partido*> partidos;

};

class FaseGrupos: public Fase{
    public:

    private:

};

class FaseEliminatoria: public Fase{
    public:

    private:

};
#endif // FASE_H
