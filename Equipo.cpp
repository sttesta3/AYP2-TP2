// #include <string> EDIT LINKER
#include "Equipo.h"

Equipo::Equipo(){
    //ctor
}

Equipo::~Equipo()
{
    //dtor
}

// METODOS DE MOSTRAR
std::string Equipo::MostrarNombre(void){
    return this->nombre;
}

char Equipo::MostrarGrupo(void){
    return this->grupo;
}

int Equipo::ValidarEquipo(std::string linea){
    int equipo_valido = 0;
    int largo = len_string(linea);

    // SI TERMINA EN ' X', entonces itera pa00ra chequear que sea alfabetico
    if (is_alfa(linea[largo - 1]) && (int)linea[largo - 2] == 32){
        int i = 0;
        while (equipo_valido == 0 && i < largo - 2){
            if (!is_alfa(linea[i]))
                equipo_valido = 1;
            i += 1;
        }
    }
    else
        equipo_valido = 1;

    // ASIGNAR VALORES A EQUIPO
    if (equipo_valido == 0){
        this->nombre = linea;
        this->nombre[largo - 1] = '\0';
        this->nombre[largo - 2] = '\0';

        this->grupo = linea[largo - 1];
    }

    return equipo_valido;
}

// METODOS DE ASIGNAR
void Equipo::AsignarNombre(std::string nombre){
    this->nombre = nombre;
}

void Equipo::AsignarGrupo(char grupo){
    this->grupo = grupo;
}

