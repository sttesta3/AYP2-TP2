#include <cmath>
#include <iostream>
#include <fstream>
#include <tuple>

#include "Mundial.h"

#include "lista.h"
#include "Equipo.h"
#include "defs.h"
#include "utils.h"

using namespace std;
Mundial::Mundial()
{
    // CONSTRUCTOR
    this->equipos = new Lista<Equipo>;
    this->partidos = new Lista<Partido>;

    this->primero = nullptr;
    this->segundo = nullptr;
    this->tercero = nullptr;
}

Mundial::~Mundial()
{
    // DESTRUCTOR
    delete this->equipos;
    delete this->partidos;
}

tuple <string, char> Mundial::ValidarEquipo(string linea){
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
        if (get<1>(equipo) == '\0' && cmp_string(get<0>(equipo),"\0")){
            cerr << "ERROR AL CARGAR EQUIPO, linea: " << linea << endl;
            entrada.close();
            return 1;
        }
        else
        {
            // cout << "POR CARGAR EQUIPO" << endl; 
            this->equipos->AgregarElemento(equipo); 
            // cout << "EQUIPO CARGADO" << endl;
        }
    }
    entrada.close();
    
    this->DefinirIteraciones();
    return 0;
}

void Mundial::DefinirIteraciones(){
    // Divido por Log(2) debido a que debemos calcular Log(equipos) en base 2
    this->MAXIMO_ITERACIONES = 2*log(this->MostrarCantidadEquipos())/log(2);
}

int Mundial::MostrarCantidadEquipos(){
    return this->equipos->MostrarCantElementos();
}
int Mundial::CargarPartidos(string archivo2){
    ifstream entrada(archivo2);
    if (!entrada){
        cerr << "ERROR AL ABRIR ARCHIVO DE PARTIDOS" << endl;
        return 1;
    }

    string fase;
    string linea;
    
    while (getline(entrada, linea)){
        linea = to_lower(linea);
        if (divisor_de_fase(linea))
            fase = linea;
        else {
            Partido* nuevo_partido;
            if (cmp_string(fase,"grupos"))
                nuevo_partido = new PartidoGrupo;
            else
                nuevo_partido = new PartidoEliminatoria;
            if (!nuevo_partido){
                cerr << "ERROR AL CREAR PARTIDO" << endl;
                return 1;
            }

            if (nuevo_partido->AsignarValor(linea);
        }
    }


    entrada.close();
    return 0;
}

// FUNCIONES DE MENU
void Mundial::MostrarMenu(void){
    bool mostrar_menu = true;

    while (mostrar_menu){
        cout << "Opciones (ingresar numero de opcion)" << endl;
        cout << "1. Listar equipos" << endl;
        cout << "2. Mostrar los equipos en primer segundo y tercer lugar" << endl;
        cout << "3. Buscar equipo por nombre" << endl;
        cout << "4. Mostrar por fase los paises ordenados por puntaje" << endl;
        cout << "5. Actualizar partido" << endl;
        cout << "6. Salir" << endl;

        char input; cin >> input;
        if (int(input) < 49 || int(input) > 57)
            input = '0';

        switch ((int)input%48 *((int)input < 58)){
        case 1:
            this->ListarEquipos(); break;
        case 2:
            this->Podio();break;
        case 3:
            { cout << "Ingrese nombre del equipo:" << endl; string busqueda; cin >> busqueda; this->MostrarBuscarEquipo(busqueda); break; }
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
}

void Mundial::ListarEquipos(void){
    cout << "EQUIPOS" << endl;

    this->equipos->IniciarIterador();
    while (this->equipos->MostrarIterador() != nullptr){
        cout << 
        "Grupo: "  << char(toupper(this->equipos->MostrarIterador()->MostrarContenido().MostrarGrupo()))  << " " <<
        "Equipo: " << to_upper(this->equipos->MostrarIterador()->MostrarContenido().MostrarNombre()) << endl;
        this->equipos->AvanzarIterador(1);
    }
}

void Mundial::Podio(void){
    cout << "PODIO" << endl;

    cout << "1ro: " << this->primero->MostrarContenido().MostrarNombre() << endl;
    cout << "2do: " << this->segundo->MostrarContenido().MostrarNombre() << endl;
    cout << "3ro: " << this->tercero->MostrarContenido().MostrarNombre() << endl;
}

Equipo* Mundial::BuscarEquipo(string busqueda){
    '''
    Se realiza busqueda lineal, no se me ocurrio un metodo mejor
    La mayor optimizacion que se me ocurrio (sin iterar la lista) es iterar desde el principio o el final segun primer letra 
    '''
    busqueda = to_lower(busqueda);
    bool busqueda_normal = true
    bool encontrado = false
    if (busqueda[0] > 110)
        busqueda_normal = false;    // Busqueda inversa

    if (busqueda_normal){
        this->equipos->IniciarIterador();

        while (!encontrado && this->equipos->MostrarIterador() != nullptr && comparar_alfabeticamente(equipo,this->equipos->MostrarIterador()->MostrarContenido().MostrarNombre()) != 0){
            this->equipos->AvanzarIterador(1);
    }
    }

}

void Mundial::MostrarBuscarEquipo(string busqueda){
    Equipo* equipo = this->BuscarEquipo(busqueda);
    if (equipo == nullptr)
        cout << "NO HAY COINCIDENCIAS" << endl;
    else{
        cout << "EQUIPO: " << to_upper(equipo->MostrarNombre());
        cout << "GRUPO: " << char(toupper(equipo->MostrarGrupo()));
        cout << "FASE HASTA LA QUE LLEGO" << endl;
    }
}
void Mundial::MenuPuntos(void){   

}

void Mundial::ActualizarPartidos(void){

}

