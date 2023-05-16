#include "fase.h"

Fase::Fase()
{
    //ctor
}

Fase::~Fase()
{
    // for (int i = 0; i < int(this->partidos.size()); i++)
        // delete this->partidos[i];

    // delete this->partidos;
    //dto
}

std::string
Fase::MostrarFase(void){
    return this->fase;
}

void
Fase::AgregarPartido(Partido* partido){
    this->partidos.push_back(partido);
}

void 
Fase::AsignarFase(std::string fase){
    this->fase = fase;
}

bool 
Fase::EliminarPartido(Partido* partido){
/*
    bool eliminado = false;
    if (!(this->partidos.size() > 0))
        std::cerr << "VECTOR VACIO" << std::endl;
    else{

        this->iterador = this->partidos.begin();
        bool encontrado = false;
        while (!encontrado && this->partidos.end() != this->iterador){
            if (this->iterador)
                encontrado = true;
            else
                this->iterador += 1;
        }

        if (encontrado){
            this->partidos.erase();
            eliminado = true;
        }
        else
            std::cerr << "ELEMENTO NO ENCONTRADO: " << partido->MostrarEquipos(true) << " vs " << partido->MostrarEquipos(false) << std::endl;
    }

    return eliminado;
*/  
    return true;
}

int FaseGrupo::CalcularPuntaje(Equipo* equipo){
    int CANT_PARTIDOS = int(this->partidos.size());
    int puntos = 0;

    for (int i = 0; i < CANT_PARTIDOS; i++){
        bool equipo1 = (this->partidos[i]->MostrarEquipos(true) == equipo);
        
        if (equipo1)
            puntos += std::get<0>(this->partidos[i]->MostrarPuntos());
        else
            puntos += std::get<1>(this->partidos[i]->MostrarPuntos());
    }
    return puntos;
}

int FaseEliminatoria::CalcularPuntaje(Equipo* equipo){
    bool equipo1 = (this->partidos[0]->MostrarEquipos(true) == equipo);
    int puntos = 0;

    if (equipo1)
        puntos += std::get<0>(this->partidos[0]->MostrarPuntos());
    else
        puntos += std::get<1>(this->partidos[0]->MostrarPuntos());
    return puntos;
}

bool FaseGrupo::PasoFase(Equipo* equipo){
    // DEBUG    std::cout << "DENTRO PASO FASE GRUPO" << std::endl;

    int cant_equipos_con_mas_puntos = 0;
    int puntos = this->CalcularPuntaje(equipo);
    int CANT_EQUIPOS = int(this->partidos.size());
    
    int i = 0;
    
    while (i < CANT_EQUIPOS && cant_equipos_con_mas_puntos < 2){
        bool equipo1 = (this->partidos[i]->MostrarEquipos(true) == equipo);

        Equipo* contrario = this->partidos[i]->MostrarEquipos(!equipo1);
        if (puntos < contrario->CalcularPuntajeGrupos())
            cant_equipos_con_mas_puntos += 1;

        i += 1;
    }

    return (cant_equipos_con_mas_puntos < 2);
}

bool FaseEliminatoria::PasoFase(Equipo* equipo){
    // SI GANO, SUS PUNTOS SERAN 2 o 3. Entonces si es mayor que 1 significa que gano
    int puntos = this->CalcularPuntaje(equipo);

    return (puntos > 1);    
}
/*
FaseGrupos::FaseGrupos() : Fase(){

}

FaseGrupos::FaseGrupos() : Fase(){
    
}

int FaseGrupos::CalcularPuntaje(){
    int suma = 0;
    std::tuple<int,int> puntos;
    for (int i=0; i < this->partidos.size(); i++)
        suma += std::get< (this->partidos[i]->MostrarEquipos(false) == this->equipo) > (this->partidos[0]->MostrarPuntos());
    return suma;
}

int FaseEliminatoria::CalcularPuntaje(){
    // std::tuple<int,int> puntos = this->partidos[0]->MostrarPuntos();
    return std::get< (this->partidos[0]->MostrarEquipos(false) == this->equipo) > (this->partidos[0]->MostrarPuntos());
    // DEBUG POR LAS DUDAS
    
    if (this->partidos[0]->MostrarEquipos(true) == this->equipo)
        return std::get<0>(puntos);
    else
        return std::get<1>(puntos);
    
}

*/