#include "partidos.h"
#include "Equipo.h"

// INCLUDE POR ERROR DE LINKER
#include <tuple>
#include <string>

//Partido::Partido(){}
// Partido::~Partido(){}
PartidoGrupo::PartidoGrupo():Partido(){}
//PartidoGrupo::~PartidoGrupo():Partido(){}
PartidoEliminatoria::PartidoEliminatoria():Partido(){}
//PartidoEliminatoria::~PartidoEliminatoria():Partido(){}

void Partido::AsignarEquipo(Equipo* equipo, bool equipo1){
    if (equipo1)
        this->equipo1 = equipo;
    else
        this->equipo2 = equipo;
}

void Partido::AsignarGoles(int goles, bool equipo1){
    if (equipo1)
        this->goles1 = goles;
    else
        this->goles2 = goles;
}

void PartidoGrupo::AsignarValores(Equipo* equipo1,Equipo* equipo2,int goles1,int goles2){
    this->AsignarEquipo(equipo1,true);
    this->AsignarEquipo(equipo2,false);
    this->AsignarGoles(goles1,true);
    this->AsignarGoles(goles2,false);
}

void PartidoEliminatoria::AsignarValores(Equipo* equipo1,Equipo* equipo2,int goles1,int goles2){
    this->AsignarEquipo(equipo1,true);
    this->AsignarEquipo(equipo2,false);
    this->AsignarGoles(goles1,true);
    this->AsignarGoles(goles2,false);
}

void PartidoEliminatoria::AsignarPenales(int penales1, int penales2){
    this->penales1 = penales1;
    this->penales2 = penales2;
}

Equipo* Partido::MostrarEquipos(bool equipo1){
    if(equipo1)
        return this->equipo1;
    else
        return this->equipo2;
}

std::tuple <std::string,std::string> PartidoGrupo::ValidarPartido(std::string linea){
    bool partido_valido = true;
    std::tuple <std::string,std::string> resultado;

    // SEPARACION EN ARGUMENTOS
    std::string argv[4];
    int argc = 0;
    
    int largo = len_string(linea);
    for (int i = 0; i < largo && partido_valido; i++){
        if ((int)linea[i] != 44)
            argv[argc] += linea[i];
        else
            argc += 1;
        
        if (argc > 3 && linea[i] != '\n'){
            std::cerr << "Demasiados argumentos en partidos. Linea: " << linea << std::endl;
            partido_valido = false;
        }
    }

    if (partido_valido == 0 && argc != 3){
        std::cerr << "Pocos argumentos en partidos. Linea: " << linea << std::endl;
        partido_valido = false;
    }

    // VALIDAR GOLES
    if (string_a_int(argv[1]) < 0 || string_a_int(argv[3]) < 0){
        std::cerr << "CANTIDAD DE GOLES INCORRECTA. Linea: " << linea << std::endl;
        partido_valido = false;
    }

    // ASIGNACION DE ARGUMENTOS A RESULTADO DE SALIDA
    
    if (partido_valido){
        std::get<0>(resultado) = argv[0]; std::get<1>(resultado) = argv[2];
        this->AsignarGoles(string_a_int(argv[1]),true);  this->AsignarGoles(string_a_int(argv[3]),false);
    }
    else{
        std::get<0>(resultado) = nullptr; std::get<1>(resultado) = nullptr; 
        this->AsignarGoles(-5,true);  this->AsignarGoles(-5,false);
    }

    return resultado;    
    // OJO, VALIDACION DE SINTAXIS NO DE EQUIPOS
}

std::tuple <std::string,std::string> PartidoEliminatoria::ValidarPartido(std::string linea){
    bool partido_valido = true;
    std::tuple <std::string,std::string> resultado;
    // SEPARACION EN ARGUMENTOS
    std::string argv[6];
    int argc = 0;
    
    int largo = len_string(linea);
    for (int i = 0; i < largo && partido_valido; i++){
        if ((int)linea[i] != 44)
            argv[argc] += linea[i];
        else
            argc += 1;
        
        if (argc > 5 && linea[i] != '\n'){
            std::cerr << "Demasiados argumentos en partidos. Linea: " << linea << std::endl;
            partido_valido = false;
        }
    }

    if (partido_valido && argc != 5){
        std::cerr << "Pocos argumentos en partidos. Linea: " << linea << std::endl;
        partido_valido = false;
    }

    // ASIGNACION DE ARGUMENTOS A RESULTADO DE SALIDA
     if (string_a_int(argv[1]) < 0 || string_a_int(argv[2]) < -1 || string_a_int(argv[4]) < 0 || string_a_int(argv[5]) < -1){
        std::cerr << "CANTIDAD DE GOLES y/o PENALES INCORRECTA. Linea: " << linea << std::endl;
        partido_valido = false;
    }
    
    if (partido_valido){
        std::get<0>(resultado) = argv[0]; std::get<1>(resultado) = argv[3];
        this->AsignarGoles(string_a_int(argv[1]),true)  ; this->AsignarGoles(string_a_int(argv[4]),false);
        this->AsignarPenales(string_a_int(argv[2]),string_a_int(argv[5])); 
    }
    else{
        std::get<0>(resultado) = argv[0]; std::get<1>(resultado) = argv[3];
        this->AsignarGoles(-5,true)  ; this->AsignarGoles(-5,false);
        this->AsignarPenales(-5,-5);
    }

    return resultado;    
}

Equipo* PartidoGrupo::MostrarGanador(){
    std::tuple <int,int> puntos = this->MostrarPuntos();
    if (std::get<0>(puntos) == std::get<1>(puntos))
        return nullptr;
    else
        return this->MostrarEquipos(std::get<0>(puntos) > std::get<1>(puntos));
}

Equipo* PartidoEliminatoria::MostrarGanador(){
    // NO SE DEBE COMPARAR QUE SEAN IGUALES, JAMAS PASARA
    std::tuple <int,int> puntos = this->MostrarPuntos();
    return this->MostrarEquipos(std::get<0>(puntos) > std::get<1>(puntos));
}

Equipo* PartidoGrupo::MostrarPerdedor(){
    std::tuple <int,int> puntos = this->MostrarPuntos();
    if (std::get<0>(puntos) == std::get<1>(puntos))
        return nullptr;
    else
        return this->MostrarEquipos(!(std::get<0>(puntos) > std::get<1>(puntos)));
}

Equipo* PartidoEliminatoria::MostrarPerdedor(){
    std::tuple <int,int> puntos = this->MostrarPuntos();
    return this->MostrarEquipos(!(std::get<0>(puntos) > std::get<1>(puntos)));
}


std::tuple<int,int> PartidoGrupo::MostrarPuntos(){
    std::tuple<int,int> resultado;
    
    std::get<0>(resultado) = 3*(this->goles1 > this->goles2) + 1*(this->goles1 == this->goles2);
    std::get<1>(resultado) = 3*(this->goles1 < this->goles2) + 1*(this->goles1 == this->goles2);

    return resultado;
}

std::tuple<int,int> PartidoEliminatoria::MostrarPuntos(){
    std::tuple<int,int> resultado;
    
    std::get<0>(resultado) = 3*(this->goles1 > this->goles2) + 1*(this->goles1 == this->goles2) + 1*(this->penales1 > this->penales2);
    std::get<1>(resultado) = 3*(this->goles1 < this->goles2) + 1*(this->goles1 == this->goles2) + 1*(this->penales1 > this->penales2);

    return resultado;
}

/*
int PartidoGrupo::CargarDatos(string linea, Lista<Partido>* partidos){
    tuple <string,int,string,int> resultado = this->ValidarPartido(linea);
    if (!get<0>(resultado) || !get<2>(resultado))
        return 1;
    else{
        partidos->AgregarElemento(resultado,partidos);
        return 0;
    }
}

int PartidoEliminatoria::CargarDatos(string linea, Lista<Partido>* partidos){
    tuple <string,int,int,string,int,int> resultado = this->ValidarPartido(linea);
    if (!get<0>(resultado) || !get<3>(resultado))
        return 1;
    else{
        partidos->AgregarElemento(resultado,partidos);
        return 0;
    }
}
*/
