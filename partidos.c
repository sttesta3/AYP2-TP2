#include <tuple>
#include "partidos.h"
#include "Mundial.h"

using namespace std;

Partido::Partido(){}
Partido::~Partido(){}

PartidoGrupo::PartidoGrupo(){}
PartidoGrupo::~PartidoGrupo(){}

PartidoEliminatoria::PartidoEliminatoria(){}
PartidoEliminatoria::~PartidoEliminatoria(){}

tuple<Equipo*,int,Equipo*,int> PartidoGrupo::ValidarPartido(string linea){
    bool partido_valido = true;
    tuple<Equipo*,int,Equipo*,int> resultado;

    // SEPARACION EN ARGUMENTOS
    string argv[4];
    int argc = 0;
    
    int largo = len_string(linea);
    for (int i = 0; i < largo && partido_valido; i++){
        if ((int)linea[i] != 44)
            argv[argc] += linea[i];
        else
            argc += 1;
        
        if (argc > 3 && linea[i] != '\n'){
            cerr << "Demasiados argumentos en partidos. Linea: " << linea << endl;
            partido_valido = false;
        }
    }

    if (partido_valido && argc != 3){
        cerr << "Pocos argumentos en partidos. Linea: " << linea << endl;
        partido_valido = false;
    }

    // BUSCAR EQUIPO
    Equipo* equipo1 = mundial->BuscarEquipo   
    
    
    if (partido_valido){

    }
    else{
        get<0>(resultado) = nullptr;
        get<1>(resultado) = -5;
                get<0>(resultado) = nullptr;
        get<1>(resultado) = -5        
    }

    return resultado; 
}