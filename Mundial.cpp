#include "Mundial.h"
#include "utils.h"
#include "lista.h"
#include "Equipo.h"
#include "partidos.h"

//EDIT POST 
#include <cstring>
#include <fstream>

//using namespace std;
Mundial::Mundial()
{
    // CONSTRUCTOR
    this->equipos = new Lista<Equipo>;
    this->partidos_grupos = new Lista<PartidoGrupo>;
    this->partidos_eliminatoria = new Lista<PartidoEliminatoria>;

    this->primero = nullptr;
    this->segundo = nullptr;
    this->tercero = nullptr;
}

Mundial::~Mundial()
{
    // DESTRUCTOR
    delete this->equipos;
    delete this->partidos_grupos;
    delete this->partidos_eliminatoria;
}

int Mundial::CargarEquipos(std::string archivo1){
    std::ifstream entrada(archivo1);
    if (!entrada){
        std::cerr << "ERROR AL ABRIR ARCHIVO DE EQUIPOS" << std::endl;
        return 1;
    }

    std::string linea;
    Equipo nuevo_equipo;
    while (getline(entrada, linea)){
        linea = to_lower(linea);
        if (nuevo_equipo.ValidarEquipo(linea) == 1){
            std::cerr << "ERROR AL CARGAR EQUIPO, linea invalida: " << linea << std::endl;
            entrada.close();
            return 1;
        }
        else
        {
            // cout << "POR CARGAR EQUIPO" << endl; 
            this->equipos->AgregarElemento(nuevo_equipo); 
            // cout << "EQUIPO CARGADO" << endl;
        }
    }
    entrada.close();
    
    this->DefinirIteraciones();
    return 0;
}

void Mundial::DefinirIteraciones(){
    // Divido por Log(2) debido a que debemos calcular Log(equipos) en base 2.
    // Se define el maximo de iteraciones como el doble para dar changui en caso de error
    this->MAXIMO_ITERACIONES = 2*int(round(log(this->MostrarCantidadEquipos())/log(2)));
}

int Mundial::MostrarCantidadEquipos(){
    return this->equipos->MostrarCantElementos();
}

int Mundial::CargarPartidos(std::string archivo2){
    std::ifstream entrada(archivo2);
    if (!entrada){
        std::cerr << "ERROR AL ABRIR ARCHIVO DE PARTIDOS" << std::endl;
        return 1;
    }

    std::string fase;
    std::string linea;
    
    while (getline(entrada, linea)){
        linea = to_lower(linea);
        if (divisor_de_fase(linea))
            fase = linea;
        else {
            std::tuple <std::string,std::string> encontrado;
            if (fase.compare("grupos")){
                PartidoGrupo nuevo_partido;
                encontrado = nuevo_partido.ValidarPartido(linea);
                if ( std::get<0>(nuevo_partido.MostrarPuntos() ) == -5){
                    std::cerr << "LINEA PARTIDO INVALIDA: " << linea << std::endl;
                    entrada.close();
                    return 1;
                }
                Equipo* equipo1 = this->BuscarEquipo(std::get<0>(encontrado));
                if (!equipo1){
                    std::cerr << "EQUIPO NO ENCONTRADO: " << std::get<0>(encontrado) << " Partido: " << linea << std::endl;
                    entrada.close();
                    return 1;
                }
                Equipo* equipo2 = this->BuscarEquipo(std::get<1>(encontrado));
                if (!equipo2){
                    std::cerr << "EQUIPO NO ENCONTRADO: " << std::get<1>(encontrado) << " Partido: " << linea << std::endl;
                    entrada.close();
                    return 1;
                }

                nuevo_partido.AsignarEquipo(equipo1,true); nuevo_partido.AsignarEquipo(equipo2,false);
                this->partidos_grupos->AgregarElemento(nuevo_partido);
            }
            else{
                PartidoEliminatoria nuevo_partido;
                encontrado = nuevo_partido.ValidarPartido(linea);
                if ( std::get<0>(nuevo_partido.MostrarPuntos() ) == -5){
                    std::cerr << "LINEA PARTIDO INVALIDA: " << linea << std::endl;
                    entrada.close();
                    return 1;
                }
                Equipo* equipo1 = this->BuscarEquipo(std::get<0>(encontrado));
                if (!equipo1){
                    std::cerr << "EQUIPO NO ENCONTRADO: " << std::get<0>(encontrado) << " Partido: " << linea << std::endl;
                    entrada.close();
                    return 1;
                }
                Equipo* equipo2 = this->BuscarEquipo(std::get<1>(encontrado));
                if (!equipo2){
                    std::cerr << "EQUIPO NO ENCONTRADO: " << std::get<1>(encontrado) << " Partido: " << linea << std::endl;
                    entrada.close();
                    return 1;
                }

                nuevo_partido.AsignarEquipo(equipo1,true);
                nuevo_partido.AsignarEquipo(equipo2,false);
                this->partidos_eliminatoria->AgregarElemento(nuevo_partido);

                if (fase.compare("final")){
                    this->primero = nuevo_partido.MostrarGanador();
                    this->segundo = nuevo_partido.MostrarPerdedor();
                }
                else if (fase.compare("tercer puesto"))
                    this->tercero = nuevo_partido.MostrarGanador();
            }
        }
    }

    entrada.close();
    return 0;
}

// FUNCIONES DE MENU
void Mundial::MostrarMenu(void){
    bool mostrar_menu = true;

    while (mostrar_menu){
        std::cout << "Opciones (ingresar numero de opcion)" << std::endl;
        std::cout << "1. Listar equipos" << std::endl;
        std::cout << "2. Mostrar los equipos en primer segundo y tercer lugar" << std::endl;
        std::cout << "3. Buscar equipo por nombre" << std::endl;
        std::cout << "4. Mostrar por fase los paises ordenados por puntaje" << std::endl;
        std::cout << "5. Actualizar partido" << std::endl;
        std::cout << "6. Salir" << std::endl;

        char input; std::cin >> input;
        if (int(input) < 49 || int(input) > 57)
            input = '0';

        switch ((int)input%48 *((int)input < 58)){
        case 1:
            this->ListarEquipos(); break;
        case 2:
            this->Podio();break;
        case 3:
            { std::cout << "Ingrese nombre del equipo:" << std::endl; std::string busqueda; std::cin >> busqueda; this->MostrarBuscarEquipo(busqueda); break; }
        case 4: 
            this->MenuPuntos(); break;
        case 5:
            this->ActualizarPartidos(); break;
        case 6:
            mostrar_menu = false; break;
        default:
            std::cout << "Opcion invalida, favor reingresar" << std::endl; break;
        }
    }
}

void Mundial::ListarEquipos(void){
    std::cout << "EQUIPOS" << std::endl;

    this->equipos->IniciarIterador();
    while (this->equipos->MostrarIterador() != nullptr){
        std::cout << 
        "Grupo: "  << char(toupper(this->equipos->MostrarIterador()->MostrarContenido().MostrarGrupo()))  << " " <<
        "Equipo: " << to_upper(this->equipos->MostrarIterador()->MostrarContenido().MostrarNombre()) << std::endl;
        this->equipos->AvanzarIterador(1);
    }
}

void Mundial::Podio(void){
    std::cout << "PODIO" << std::endl;

    std::cout << "1ro: " << this->primero->MostrarNombre() << std::endl;
    std::cout << "2do: " << this->segundo->MostrarNombre() << std::endl;
    std::cout << "3ro: " << this->tercero->MostrarNombre() << std::endl;
}

Equipo* Mundial::BuscarEquipo(std::string busqueda){
    /*
    Se realiza busqueda lineal, no se me ocurrio un metodo mejor
    La mayor optimizacion que se me ocurrio (sin iterar la lista) es iterar desde el principio o el final segun primer letra 
    */
    busqueda = to_lower(busqueda);
    bool busqueda_normal = !(busqueda[0] > 110);

    if (busqueda_normal){
        this->equipos->IniciarIterador();

        while (this->equipos->MostrarIterador() != nullptr && comparar_alfabeticamente(busqueda,this->equipos->MostrarIterador()->MostrarContenido().MostrarNombre()) != 0){
            this->equipos->AvanzarIterador(1);
        }
    }
    else{
        this->equipos->IniciarIteradorAlUltimo();

        while (this->equipos->MostrarIterador() != nullptr && comparar_alfabeticamente(busqueda,this->equipos->MostrarIterador()->MostrarContenido().MostrarNombre()) != 0){
            this->equipos->RetrocederIterador(1);
        }
    }
    if (!this->equipos->MostrarIterador())
        return nullptr;
    else
        return this->equipos->MostrarIterador()->MostrarDireccion();
}

void Mundial::MostrarBuscarEquipo(std::string busqueda){
    Equipo* equipo = this->BuscarEquipo(busqueda);
    if (equipo == nullptr)
        std::cout << "NO HAY COINCIDENCIAS" << std::endl;
    else{
        std::cout << "EQUIPO: " << to_upper(equipo->MostrarNombre());
        std::cout << "GRUPO: " << char(toupper(equipo->MostrarGrupo()));
        std::cout << "FASE HASTA LA QUE LLEGO" << std::endl;
    }
}
void Mundial::MenuPuntos(void){   

}

void Mundial::ActualizarPartidos(void){

}

/*
tuple <string, char> Mundial::ValidarEquipo(string linea){
    int equipo_valido = 0;
    int largo = len_string(linea);
    tuple <string, char> resultado;

    if (isalpha(linea[largo - 1]) && (int)linea[largo - 2] == 32){
        int i = 0;
        while (equipo_valido == 0 && i < largo - 2){
            if (isalpha(linea[i]) == false)
                equipo_valido = 1;
            i += 1;
        }
    }
    else
        equipo_valido = 1;

    if (equipo_valido == 0){
        string equipo = linea;
        equipo[largo - 1] = '\0';
        equipo[largo - 2] = '\0';
        get<0>(resultado) = equipo;
        get<1>(resultado) = linea[largo - 1];
    }
    else {
        get<0>(resultado) = "\0";
        get<1>(resultado) = '\0';
    }

    return resultado;
}
*/
