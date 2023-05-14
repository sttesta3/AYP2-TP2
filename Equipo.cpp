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


void Equipo::AgregarPartido(Partido* partido, std::string fase){
    if (fase.compare("grupos") == 1){
        // SI ESTA VACIO, CREAR FASE
        if (this->fases.size() == 0){
            Fase* nuevo_grupos = new Fase;
            this->fases.push_back(nuevo_grupos);
            nuevo_grupos->AsignarFase(fase);
        }
        this->fases[0]->AgregarPartido(partido);
    }
    else {
        // LOS EQUIPOS TIENEN SOLO UN PARTIDO DE ELIMINATORIA, POR LO TANTO SIEMPRE SERA NUEVO
        // SE TOMARON COMO BASE ALGUNO DE LOS EJEMPLOS DE MicrosoftLearn
        // https://learn.microsoft.com/es-es/cpp/standard-library/vector-class?view=msvc-170#insert 

        Fase* nueva_eliminatoria = new Fase;
        nueva_eliminatoria->AgregarPartido(partido);
        nueva_eliminatoria->AsignarFase(fase);

        int fase_numerica = fase_a_numero(fase);
        if (int(this->fases.size()) < fase_numerica)
            this->fases.push_back(nueva_eliminatoria);
        else 
            this->fases.insert(this->fases.begin() + fase_numerica, nueva_eliminatoria);
    }
}

