#ifndef EQUIPO_H
#define EQUIPO_H

class Fase;
#include "fase.h"
//class FaseGrupo;
//class FaseEliminatoria;

#include "partidos.h"

//class Partido;
//class PartidoGrupo;
//class PartidoEliminatoria;

// EDIT POR LINK
#include <cstring>
#include <vector>
#include <tuple>

#include "utils.h"


class Equipo {
    private:
        std::string nombre;
        char grupo;
        std::vector <Fase*> fases;
        bool original_de_archivo;

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

        bool ValidarMundialEquipo(bool verbose);
        std::tuple <bool,bool,bool,bool,bool,bool> MostrarFasesExistentes();
        int BuscarFase(std::string fase);
        int CalcularPuntajeGrupos();

        void NoEsOriginal(void);
};

#endif // EQUIPO_H
