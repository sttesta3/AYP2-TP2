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
        Leer archivo de equipos, cargar equipos en memoria (vector dinamico).
        Leer archivo de partidos, cargar puntos y fase final en equipos.
        Formar grupos y fases finales
        Ofrecer menu, while usuario quiera seguir utilizando app
        Alternar entre opciones del menu
        Exit (y descarga memoria dinamica)
    */

    if (argc != 1){     // se deja hardcodeado == 1
        cout << "Uso: ./" << argv[0] << " file1 file2"<< endl;
        return 1;
    }

    Mundial* mundial = new Mundial;
    if (!mundial){        // DEBERIA HACERSE EN EL
        cerr << "ERROR AL CREAR MUNDIAL" << endl;
        return 1;
    }

    if(mundial->CargarEquipos(argv[1])){
        if (mundial->CargarPartidos(argv[2])){
            delete mundial;
            return 1;
        }
    }

    mundial->MostrarMenu();

    delete mundial;
    return 0;
}

