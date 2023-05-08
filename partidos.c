#include "partidos.h"

/* INCLUDE POR ERROR DE LINKER
#include <tuple>
#include <string>
*/

Partido::Partido(){}
// Partido::~Partido(){}
PartidoGrupo::PartidoGrupo():Partido(){}
//PartidoGrupo::~PartidoGrupo():Partido(){}
PartidoEliminatoria::PartidoEliminatoria():Partido(){}
//PartidoEliminatoria::~PartidoEliminatoria():Partido(){}

PartidoGrupo::AsignarValores(Equipo* equipo1,Equipo* equipo2,int goles1,int goles2){
    this->equipo1 = equipo1;
    this->equipo1 = equipo1;
    this->goles1 = goles1;
    this->goles2 = goles2;
}

PartidoEliminatorioa::AsignarValores(Equipo* equipo1,Equipo* equipo2,int goles1,int goles2){
    this->equipo1 = equipo1;
    this->equipo1 = equipo1;
    this->goles1 = goles1;
    this->goles2 = goles2;
}

PartidoEliminatoria::AsignarPenales(int penales1, int penales2){
    this->penales1 = penales1;
    this->penales2 = penales2;
}


std::tuple <Equipo*,Equipo*> Partido::MostrarEquipos(){
    std::tuple <Equipo*,Equipo*> resultado;
    std::get<0>(resultado) = this->equipo1;
    std::get<1>(resultado) = this->equipo2;

    return resultado;
}


std::tuple <std::string,int,std::string,int> PartidoGrupo::ValidarPartido(std::string linea){
    bool partido_valido = true;
    std::tuple <std::string,int,std::string,int> resultado;

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
    if (argv[1] < 0 || argv[3] < 0){
        std::cerr << "CANTIDAD DE GOLES INCORRECTA. Linea: " << linea << std::endl;
        partido_valido = false;
    }

    // ASIGNACION DE ARGUMENTOS A RESULTADO DE SALIDA
    for (int i = 0; i < 4; i++){
        if (partido_valido)
            std::get<i>(resultado) = argv[i];
        else{
            if (i%2 == 0)
                std::get<i>(resultado) = "\0";
            else
                std::get<i>(resultado) = -5;
        }
            std::get<i>(resultado) = argv[i];
    }

    return resultado;    
    // OJO, AUNQUE PARTIDO_VALIDO SEA VERDADERO, PUEDE NO ENCONTRAR EQUIPOS
}

std::tuple <std::string,int,int,std::string,int,int>  PartidoEliminatoria::ValidarPartido(std::string linea){
    bool partido_valido = true;
    std::tuple <std::string,int,int,std::string,int,int> resultado;
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
     if (argv[1] < 0 || argv[2] < -1 || argv[4] < 0 || argv[5] < -1){
        std::cerr << "CANTIDAD DE GOLES y/o PENALES INCORRECTA. Linea: " << linea << std::endl;
        partido_valido = false;
    }

    for (int i = 0; i < 4; i++){
        if (partido_valido)
            std::get<i>(resultado) = argv[i];
        else{
            if (i%3 == 0)
                std::get<i>(resultado) = "\0";
            else
                std::get<i>(resultado) = -5;
        }
    }

    return resultado;    
}

Equipo* PartidoEliminatoria::MostrarGanador(){
    std::tuple <int,int> puntos = this->MostrarPuntos();
    if (std::get<0>(puntos) > std::get<1>(puntos))
        return this->equipo1;
    else
        return this->equipo2;
}

Equipo* PartidoEliminatoria::MostrarPerdedor(){
    if (this->MostrarGanador() == this->equipo1)
        return this->equipo2;
    else
        return this->equipo1;
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
