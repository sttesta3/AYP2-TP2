#ifndef EQUIPO_H
#define EQUIPO_H

#include <string>
#include <vector>
#include "fase.h"

using namespace std;

class Equipo {
    private:
        string nombre;
        char grupo;
        vector <class Fase> fases;

    protected:

    public:
        Equipo(string nombre, char grupo);
        
        string MostrarNombre(void);
        char MostrarGrupo(void);
        
        void AsignarNombre(string nombre);
        void AsignarGrupo(char grupo);

        ~Equipo();

};

#endif // EQUIPO_H
