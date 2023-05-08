#include "Mundial.h"

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
        std::cout << "Uso: ./" << argv[0] << " file1 file2"<< std::endl;
        return 1;
    }

    Mundial* mundial = new Mundial;
    if (!mundial){        
        std::cerr << "ERROR AL CREAR MUNDIAL" << std::endl;
        return 1;
    }

    // CARGAR EQUIPOS Y PARTIDOS, SI FALLA DESCARGAR TODO
    int resultado = 0;
    if(mundial->CargarEquipos(argv[1]) == 1)
        resultado = 1;
    else if (mundial->CargarPartidos(argv[2]) == 1)
        resultado = 1;
    else
        mundial->MostrarMenu();
        
    delete mundial;
    return resultado;
}

