//#include <cmath>
//#include <fstream>
#include <iostream>
// #include <string>
#include "Mundial.h"
//#include "utils.h"
//#include "defs.h"

using namespace std;
int main(int argc, char* argv[]){
    /*
        Breve descripcion del programa:
        ° Leer archivo de equipos, cargar equipos en memoria lista.
        ° Leer archivo de partidos, cargar lista de partidos, vector de fases por equipo y vector de partidos
            por fase (punteros a nodos de lista)
        ° Formar grupos y fases finales
        ° Ofrecer menu, while usuario quiera seguir utilizando app
        ° En caso de actualizar partido, se corre funcion validar mundial y, de ser disruptivo, avisa al user
        ° Exit, guardar si usuario desea y descarga memoria dinamica
    */

    if (argc != 3){     
        cout << "Uso: ./" << argv[0] << " file1 file2"<< endl;
        return 1;
    }

    Mundial* mundial = new Mundial;
    if (!mundial){        
        cerr << "ERROR AL CREAR MUNDIAL" << endl;
        return 1;
    }

    // CARGAR EQUIPOS Y PARTIDOS, SI FALLA DESCARGAR TODO
    if(mundial->CargarEquipos(argv[1])){
        if (mundial->CargarPartidos(argv[2])){
            delete mundial;
            return 1;
        }
    }

    mundial->MostrarMenu();
    mundial->Salir();

    return 0;
}

