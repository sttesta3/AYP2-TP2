#ifndef DEFS_INCLUDED
#define DEFS_INCLUDED

// ESTRUCTURAS DE DATOS
struct Equipo {
    string nombre;
    char grupo;

    int puntos[6];          // Vector dinamico de puntos[fase]
    int fase_final;
};

struct Fase {               // Struct para fases y grupos
    Equipo* equipos;
    string fase;
    int cant_equipos;
};

struct Mundial {
    int MAXIMO_ITERACIONES;
    //Vectores dinamicos de equipos (ordenados alfabeticamente)
    int cant_equipos;
    Equipo* equipos;

    // Vectores dinamicos de fases (ordenados por puntaje)
    Fase* fases;
    int cant_fases; // si hay 6 grupos, este int ser� 9 (6 grupos + 3 fases)
    /*
    fase[i] i:0 -> final
            i:1 -> tercer puesto
            i:2 -> semifinal
            i:3 -> cuartos
            i:4 -> octavos
            i:5 -> grupos

            EJ. arg C, croacia A -> i:3 grupo C, i:4 grupo A

            No se agrega final y tercer puesto, debido a que se tienen los punteros a primero, segundo, tercero y cuarto
    */

};

struct Partido {        // Estructura no guardada de forma dinamica, solo para facilitar codigo
    Equipo* equipo1;
    Equipo* equipo2;

    int goles1;
    int goles2;
    int penales1;
    int penales2;
};

#endif