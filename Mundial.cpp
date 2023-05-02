#include <iostream>
#include <fstream>
#include <tuple>

#include "Mundial.h"
#include "Equipo.h"
#include "defs.h"
#include "utils.h"

Mundial::Mundial()
{
    this->equipos = new Lista<Equipo>;
    this->partidos = new Lista<Partido>;

    this->primero = nullptr;
    this->segundo = nullptr;
    this->tercero = nullptr;
}

Mundial::~Mundial()
{
    //dtor
    delete this->equipos;
    delete this->partidos;
}

int Mundial::CargarEquipos(string archivo1){
    ifstream entrada(archivo1);
    if (!entrada){
        cerr << "ERROR AL ABRIR ARCHIVO DE EQUIPOS" << endl;
        return 1;
    }

    string linea;
    tuple <string, char> equipo;
    while (getline(entrada, linea)){
        linea = to_lower(linea);
        equipo = this->ValidarEquipo(linea);
        if (get<1>(equipo) == '\0' && !cmp_string(get<0>(equipo),"\0")){
            cerr << "ERROR AL CARGAR EQUIPO, linea: " << linea << endl;
            return 1;
        }
        else
            this->equipos->AgregarElemento(equipo);
    }

    return 0;
}

tuple <string, char> ValidarEquipo(string linea){
    int equipo_valido = 0;
    int largo = len_string(linea);
    tuple <string, char> resultado;

    if (is_alfa(linea[largo - 1]) && (int)linea[largo - 2] == 32){
        int i = 0;
        while (equipo_valido == 0 && i < largo - 2){
            if (is_alfa(linea[i]) == false)
                equipo_valido = 1;
            i += 1;
        }
    }
    else
        equipo_valido = 1;

    if (!equipo_valido){
        string equipo = linea;
        equipo[largo - 1] = '\0';
        equipo[largo - 2] = '\0';
        get<0>(resultado) = equipo;
        get<1>(resultado) = linea[largo - 1];
        // salida->fases = nullptr;
    }
    else {
        get<0>(resultado) = "\0";
        get<1>(resultado) = '\0';
    }

    return resultado;
}

// FUNCIONES DE MENU
void Mundial::MostrarMenu(void){
    bool mostrar_menu = true;

    while (mostrar_menu){
        cout << "Opciones (ingresar numero de opcion)" << endl;
        cout << "1. Listar equipos" << endl;
        cout << "2. Mostrar los equipos en primer segundo y tercer lugar" << endl;
        cout << "3. Buscar equipo por nombre" << endl;
        cout << "4. Mostrar por fase los pa�ses ordenados por puntaje" << endl;
        cout << "5. Salir" << endl;

        char input; cin >> input;
        if (int(input) < 49 || int(input) > 57)
            input = '0';

        switch ((int)input%48 *((int)input < 58)){
        case 1:
            this->ListarEquipos(); break;
        case 2:
            this->Podio();break;
        case 3:
            {cout << "Ingrese nombre del equipo:" << endl; string busqueda; cin >> busqueda; this->BuscarEquipo(busqueda); break;}
        case 4:
            this->MenuPuntos(); break;
        case 5:
            this->ActualizarPartidos(); break;
        case 6:
            mostrar_menu = false; break;
        default:
            cout << "Opcion invalida, favor reingresar" << endl; break;
        }
    }

    this->Salir();
}

void Mundial::ListarEquipos(void){
    cout << "EQUIPOS" << endl;

    Nodo <Equipo> *iterador = this->equipos->MostrarPrimerElemento();
    while (iterador != nullptr){
        cout << "Equipo: " << iterador->contenido.MostrarNombre() << endl;
        iterador = iterador->siguiente;
    }
}

void Mundial::Podio(void){
    cout << "PODIO" << endl;

    cout << "1ro: " << this->primero->contenido.MostrarNombre() << endl;
    cout << "2do: " << this->segundo->contenido.MostrarNombre() << endl;
    cout << "3ro: " << this->tercero->contenido.MostrarNombre() << endl;
}
