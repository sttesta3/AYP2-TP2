#include "partidos.h"
//#include "Equipo.h"

// INCLUDE POR ERROR DE LINKER
//#include <tuple>
//#include <string>

//Partido::Partido(){}
Partido::~Partido(){}
PartidoGrupo::PartidoGrupo():Partido(){}
PartidoGrupo::~PartidoGrupo(){}
PartidoEliminatoria::PartidoEliminatoria():Partido(){}
PartidoEliminatoria::~PartidoEliminatoria(){}

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
int Partido::MostrarGoles(bool equipo1){
    if (equipo1)
        return this->goles1;
    else
        return this->goles2;
}
void Partido::AsignarLinea(int linea){
    // Con esta informacion es suficiente para realizar el guardado en el archivo de texto.
    // Se iteran los partidos y se compara contra la info en la linea mencionada.
    // Si hay diferencia -> el partido ha sido actualizado y debe actualizarse en el archivo
    // Si la linea es -1, hay que encontrar la fase mencionada y agregar una linea con esta informacion
    // Nota: primero deben de actualizarse los partidos, despues eliminar los que se deban eliminar y
    // finalmente agregar los nuevos. Debido a que hacerlo en el sentido inverso modificaria el orden de las lineas
    // Si ya se, mucho texto
    this->linea = linea;
}

void Partido::NoEsOriginal(){
    this->linea = -1;
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
    //DEBGU std::cout << "SOY GRUPO, linea: " << linea << std::endl;
    bool partido_valido = true;
    std::tuple <std::string,std::string> resultado;

    // SEPARACION EN ARGUMENTOS
    std::string argv[4];
    int argc = 0;
    
    int largo = int(linea.size());
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

    if (partido_valido && argc != 3){
        std::cerr << "Pocos argumentos en partidos. Linea: " << linea << std::endl;
        
        
        partido_valido = false;
    }

    // DEBUG
    /*
    for (int i=0; i < 4; i++){
        if (i%2 == 0)
            std::cout << "i: " << i << " argv: " << argv[i] << std::endl;
        else
            std::cout << "i: " << i << " argv: " << argv[i] << " stoi " << std::stoi(argv[i]) << std::endl;

    }
    */
    // DEBUG std::cout << "TEST de -1: " << std::stoi("-1") + 1<< std::endl;
    // VALIDAR GOLES
    
    if (std::stoi(argv[1]) < 0 || std::stoi(argv[3]) < 0){
        std::cerr << "CANTIDAD DE GOLES INCORRECTA. Linea: " << linea << std::endl;
        partido_valido = false;
    }

    // ASIGNACION DE ARGUMENTOS A RESULTADO DE SALIDA
    
    if (partido_valido){
        std::get<0>(resultado) = argv[0]; std::get<1>(resultado) = argv[2];
        this->AsignarGoles(std::stoi(argv[1]),true);  this->AsignarGoles(std::stoi(argv[3]),false);
    }
    else{
        std::get<0>(resultado) = nullptr; std::get<1>(resultado) = nullptr; 
        this->AsignarGoles(-5,true);  this->AsignarGoles(-5,false);
    }

    return resultado;    
    // OJO, VALIDACION DE SINTAXIS NO DE EQUIPOS
}

std::tuple <std::string,std::string> PartidoEliminatoria::ValidarPartido(std::string linea){
    // DEBUG   std::cout << "SOY ELIMINATORIA, linea: " << linea << std::endl;
    bool partido_valido = true;
    std::tuple <std::string,std::string> resultado;
    // SEPARACION EN ARGUMENTOS
    std::string argv[6];
    int argc = 0;
    
    int largo = int(linea.size());
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
    if (std::stoi(argv[1]) < 0 || std::stoi(argv[2]) < -1 || std::stoi(argv[4]) < 0 || std::stoi(argv[5]) < -1){
        std::cerr << "CANTIDAD DE GOLES y/o PENALES INCORRECTA. Linea: " << linea << std::endl;
        partido_valido = false;
    }
    
    if (partido_valido){
        std::get<0>(resultado) = argv[0]; std::get<1>(resultado) = argv[3];
        this->AsignarGoles(std::stoi(argv[1]),true) ; this->AsignarGoles(std::stoi(argv[4]),false);
        this->AsignarPenales(std::stoi(argv[2]),std::stoi(argv[5])); 
    }
    else{
        std::get<0>(resultado) = argv[0]; std::get<1>(resultado) = argv[3];
        this->AsignarGoles(-5,true)  ; this->AsignarGoles(-5,false);
        this->AsignarPenales(-5,-5);
    }

    return resultado;    
}

Equipo* PartidoGrupo::MostrarGanador(){
    // MostrarEquipos devuelve el equipo 1 si es true, y el equipo 2 en caso contrario
    std::tuple <int,int> puntos = this->MostrarPuntos();
    if (std::get<0>(puntos) == std::get<1>(puntos))
        return nullptr;
    else
        return this->MostrarEquipos(std::get<0>(puntos) > std::get<1>(puntos));
}

Equipo* PartidoEliminatoria::MostrarGanador(){
    std::tuple <int,int> puntos = this->MostrarPuntos();
    return this->MostrarEquipos(std::get<0>(puntos) > std::get<1>(puntos));
}

Equipo* PartidoGrupo::MostrarPerdedor(){
    std::tuple <int,int> puntos = this->MostrarPuntos();
    if (std::get<0>(puntos) == std::get<1>(puntos))
        return nullptr;
    else
        return this->MostrarEquipos(std::get<0>(puntos) < std::get<1>(puntos));
}

Equipo* PartidoEliminatoria::MostrarPerdedor(){
    std::tuple <int,int> puntos = this->MostrarPuntos();
    return this->MostrarEquipos(std::get<0>(puntos) < std::get<1>(puntos));
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
    std::get<1>(resultado) = 3*(this->goles1 < this->goles2) + 1*(this->goles1 == this->goles2) + 1*(this->penales1 < this->penales2);

    return resultado;
}

Equipo* PartidoGrupo::MostrarEquipo(bool equipo1){
    if (equipo1)
        return this->equipo1;
    else
        return this->equipo2;
}

Equipo* PartidoEliminatoria::MostrarEquipo(bool equipo1){
    if (equipo1)
        return this->equipo1;
    else
        return this->equipo2;
}

void PartidoGrupo::SolicitarValores(Equipo* equipo1, Equipo* equipo2, std::string nombre1, std::string nombre2){

    int goles1 = -5;
    while (goles1 < 0){
        std::cout << "Ingrese goles de " << nombre1 << ": " << std::endl; std::cin >> goles1;
    }
    int goles2 = -5;
    while (goles2 < 0){
        std::cout << "Ingrese goles de " << nombre2 << ": " << std::endl; std::cin >> goles2;
    }

    this->equipo1 = equipo1;
    this->equipo2 = equipo2;
    this->goles1 = goles1;
    this->goles2 = goles2;
}

void PartidoEliminatoria::SolicitarValores(Equipo* equipo1, Equipo* equipo2, std::string nombre1, std::string nombre2){
    int goles1 = -5;
    while (goles1 < 0){
        std::cout << "Ingrese goles de " << nombre1 << ": " << std::endl; std::cin >> goles1;
    }
    int goles2 = -5;
    while (goles2 < 0){
        std::cout << "Ingrese goles de " << nombre2 << ": " << std::endl; std::cin >> goles2;
    }

    int penales1 = -5;
    int penales2 = -5;
    if (goles1 != goles2){
        penales1 = -1;
        penales2 = -1;
    }
    else {
        while (penales1 == penales2){
            while (penales1 < 0){
                std::cout << "Ingrese penales de " << nombre1 << ": " << std::endl; std::cin >> penales1;
            }
            while (penales2 < 0){
                std::cout << "Ingrese penales de " << nombre2 << ": " << std::endl; std::cin >> penales2;
            }

            if (penales1 == penales2){
                std::cout << "Los penales ingresados son iguales, favor reingresar" << std::endl;
            }
        }
    }

    this->equipo1 = equipo1;
    this->equipo2 = equipo2;
    this->goles1 = goles1;
    this->goles2 = goles2;
    this->penales1 = penales1;
    this->penales2 = penales2;

}