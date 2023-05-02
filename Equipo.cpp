#include "Equipo.h"

Equipo::Equipo(string nombre,char grupo){
    this->nombre = nombre;
    this->grupo = grupo;
    // this->fases = (Fase)nullptr;
}

Equipo::~Equipo()
{
    //dtor
}

// MÉTODOS DE MOSTRAR
string Equipo::MostrarNombre(void){
    return this->nombre;
}

char Equipo::MostrarGrupo(void){
    return this->grupo;
}


