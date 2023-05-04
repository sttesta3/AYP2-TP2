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

// METODOS DE MOSTRAR
string Equipo::MostrarNombre(void){
    return this->nombre;
}

char Equipo::MostrarGrupo(void){
    return this->grupo;
}

// METODOS DE ASIGNAR
void Equipo::AsignarNombre(string nombre){
    this->nombre = nombre;
}

void Equipo::AsignarGrupo(char grupo){
    this->grupo = grupo;
}

