#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <cmath>
#include <cstring>

bool divisor_de_fase(std::string input);
int fase_a_numero(std::string fase);
// FUNCIONES DE STRING
int len_string(std::string a);
std::string split_string(std::string a);
//bool cmp_string(std::string a, std::string b);
std::string to_lower(std::string a);
std::string to_upper(std::string a);
int comparar_alfabeticamente(std::string a, std::string b);
bool is_alfa(char a);
int string_a_int(std::string a);
bool cmp_string(std::string a, std::string b);
void DictarLinea(std::string linea);


// MANEJO DE MEMORIA
/*
int iniciar_equipo_vacio(Equipo* equipo);
int iniciar_fase_vacia(Fase* fase);
void iniciar_equipo(char grupo, string nombre, Equipo* equipo);

int estirar_vector(Mundial* mundial);
int estirar_vector_fases(Mundial* mundial);
int estirar_vector_grupo(Mundial* mundial, int num_fase);

int cargar_equipo_en_memoria(string linea, Mundial* mundial);
int cargar_partidos(Partido* partido, Mundial* mundial, string fase);
int formar_grupos(Mundial* mundial);

Mundial* iniciar_mundial(void);
int descargar_mundial(Mundial* mundial);


// ORDENAMIENTO
int recursion_swap(Mundial* mundial, int i);
int recursion_swap_pp(Mundial* mundial, int index_fase, int index_equipo, int fase_numerica);
void ordenar_equipos(Mundial* mundial);
void ordenar_fases(Mundial* mundial);
*/

/*
// FUNCIONES GENERALES
bool validar_equipo(string linea);
Partido* validar_partido(Mundial* mundial, string linea);
int iterar_fases(Mundial* mundial, char grupo);
Equipo* buscar_equipo(Mundial* mundial, string nombre);
int busqueda_binaria(Mundial* mundial, string nombre, int n, int cant_iteraciones);
*/

/*
int fase_a_numero(string fase);
int suma_puntos(Equipo* equipo);
int mod (float a);
*/

/*
// FUNCIONES DE PROGRAMA PRINCIPAL
bool menu(Mundial* mundial);
void menu_listar_equipos(Mundial* mundial);
void menu_podio(Mundial* mundial);
void menu_buscar_equipo(string busqueda, Mundial* mundial);
void menu_puntos(Mundial* mundial);
*/
/*
// FUNCIONES DE MEMORIA
int iniciar_equipo_vacio(Equipo* equipo);
int iniciar_fase_vacia(Fase* fase);

int estirar_vector(Mundial* mundial);
int estirar_vector_fases(Mundial* mundial);
int estirar_vector_grupo(Mundial* mundial, int num_fase);

void iniciar_equipo(char grupo, string nombre, Equipo* equipo);

int cargar_equipo_en_memoria(string linea, Mundial* mundial);
int formar_grupos(Mundial* mundial);

Mundial* iniciar_mundial(void);
int descargar_mundial(Mundial* mundial);

int recursion_swap(Mundial* mundial, int i);
int comparar_alfabeticamente(string a, string b);
void ordenar_equipos(Mundial* mundial);
void ordenar_fases(Mundial* mundial);

//void formar_grupos(Mundial* mundial);
int cargar_partidos(string linea, Mundial* mundial, string fase);
int fase_a_numero(string fase);

Equipo* buscar_equipo(Mundial* mundial, string nombre);
int busqueda_binaria(Mundial* mundial, string nombre, int n, int cant_iteraciones);
int iterar_fases(Mundial* mundial, char grupo);


bool divisor_de_fase(string input);
bool validar_equipo(string linea);
bool validar_partido(string linea);

// FUNCIONES DE STRING
string to_lower(string a);
string to_upper(string a);
string split_string(string a);
bool cmp_string(string a, string b);
string* separar_csv(string a);
int mod (float a);

bool menu(Mundial* mundial);
void menu_listar_equipos(Mundial* mundial);
void menu_podio(Mundial* mundial);
void menu_buscar_equipo(string busqueda, Mundial* mundial);
void menu_puntos(Mundial* mundial);
*/
#endif // UTILS_H
