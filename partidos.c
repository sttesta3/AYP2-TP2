#include <tuple>
#include <string>

#include "lista.h"
#include "partidos.h"
#include "Equipo.h"

using namespace std;

Partido::Partido(){

}
Partido::~Partido(){

}
Partido::AsignarValores(Equipo* equipo1,Equipo* equipo2,int goles1,int goles2){
    this->equipo1 = equipo1;
    this->equipo1 = equipo1;
    this->goles1 = goles1;
    this->goles2 = goles2;
}

PartidoGrupo::PartidoGrupo(){

}
PartidoGrupo::~PartidoGrupo(){

}

PartidoEliminatoria::PartidoEliminatoria(){

}
PartidoEliminatoria::~PartidoEliminatoria(){

}
PartidoEliminatoria::AsignarPenales(int penales1, int penales2){
    this->penales1 = penales1;
    this->penales2 = penales2;
}

PartidoGrupo PartidoGrupo::ValidarPartido(string linea, Lista<Equipo>* equipos){
    bool partido_valido = true;
    PartidoGrupo resultado;
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

    // BUSCAR EQUIPOS Y VALIDAR GOLES
    if (argv[1] < 0 || argv[3] < 0){
        cerr << "CANTIDAD DE GOLES INCORRECTA. Linea: " << linea << endl;
        partido_valido = false;
    }

    // ASIGNACION DE ARGUMENTOS A RESULTADO DE SALIDA
    if (!partido_valido)
        resultado->AsignarValores(nullptr,nullptr,-5,-5);
    else
        resultado->AsignarValores(equipos->BuscarElemento(argv[0]),equipos->BuscarElemento(argv[2]),argv[1],argv[3]);

    return resultado;    
    // OJO, AUNQUE PARTIDO_VALIDO SEA VERDADERO, PUEDE NO ENCONTRAR EQUIPOS
}

int PartidoEliminatoria::ValidarPartido(string linea){
    bool partido_valido = true;

    // SEPARACION EN ARGUMENTOS
    string argv[6];
    int argc = 0;
    
    int largo = len_string(linea);
    for (int i = 0; i < largo && partido_valido; i++){
        if ((int)linea[i] != 44)
            argv[argc] += linea[i];
        else
            argc += 1;
        
        if (argc > 5 && linea[i] != '\n'){
            cerr << "Demasiados argumentos en partidos. Linea: " << linea << endl;
            partido_valido = false;
        }
    }

    if (partido_valido && argc != 5){
        cerr << "Pocos argumentos en partidos. Linea: " << linea << endl;
        partido_valido = false;
    }

    // ASIGNACION DE ARGUMENTOS A RESULTADO DE SALIDA
     if (argv[1] < 0 || argv[2] < -1 || argv[4] < 0 || argv[5] < -1){
        cerr << "CANTIDAD DE GOLES y/o PENALES INCORRECTA. Linea: " << linea << endl;
        partido_valido = false;
    }

    if (!partido_valido){
        resultado->AsignarValores(nullptr,nullptr,-5,-5);
        resultado->AsignarPenales(-5,-5);
    }
    else{
        resultado->AsignarValores(equipos->BuscarElemento(argv[0]),equipos->BuscarElemento(argv[2]),argv[1],argv[3]);
        resultado->AsignarPenales(argv[2],argv[5]);
    }
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
