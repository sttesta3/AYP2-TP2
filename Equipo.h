#ifndef EQUIPO_H
#define EQUIPO_H

// #include "fase.h"

// EDIT POR LINK
#include "utils.h"


class Equipo {
    private:
        std::string nombre;
        char grupo;
        // vector <class Fase> fases;

    protected:

    public:
        Equipo();
        ~Equipo();

        int ValidarEquipo(std::string linea);
        std::string MostrarNombre(void);
        char MostrarGrupo(void);
        
        void AsignarNombre(std::string nombre);
        void AsignarGrupo(char grupo);

};

#endif // EQUIPO_H
