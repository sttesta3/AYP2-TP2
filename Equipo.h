#ifndef EQUIPO_H
#define EQUIPO_H

#include <string>
#include <vector>

// #include "fase.h"

using namespace std;

class Equipo {
    private:
        string nombre;
        char grupo;
        // vector <class Fase> fases;

    protected:

    public:
        Equipo();
        ~Equipo();

        int ValidarEquipo(string linea);
        string MostrarNombre(void);
        char MostrarGrupo(void);
        
        void AsignarNombre(string nombre);
        void AsignarGrupo(char grupo);

};

#endif // EQUIPO_H
