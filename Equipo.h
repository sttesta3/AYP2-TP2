#ifndef EQUIPO_H
#define EQUIPO_H

#include "fase.h"
//class Fase;

//#include "partidos.h"
class Partido;

// EDIT POR LINK
#include <cstring>
#include <vector>

#include "utils.h"


class Equipo {
    private:
        std::string nombre;
        char grupo;
        std::vector <Fase*> fases;

    protected:

    public:
        Equipo();
        ~Equipo();

        int ValidarEquipo(std::string linea);
        std::string MostrarNombre(void);
        char MostrarGrupo(void);
        
        void AsignarNombre(std::string nombre);
        void AsignarGrupo(char grupo);

        void AgregarPartido(Partido* partido, std::string fase);
};

#endif // EQUIPO_H
