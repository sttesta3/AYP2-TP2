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

        //int CalcularPuntaje();
        //bool PasoFase();

    private:
        std::vector <Partido*> partidos;
        std::string fase;
        //std::vector <Partido*>::iterator iterador;
        
};
#endif // FASE_H
