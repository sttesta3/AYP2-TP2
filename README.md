# AYP2-TP2
## TP2 AYP2 - El error de La'eeb, la venganza de La'eebb

### PENDIENTES
#### VALGRIND LEAKEA MEMORIA, sigo debuggeando
#### Equipos Por Puntos no funciona correctamente
#### No Guarda en archivo al cerrar programa (Pero esta implementado el andamiaje sobre el que se realizara la tarea)
#### Seguire trabajando en el tp post entrega para dejarlo funcionando (branch develop). Tomen como ultimo el pusheado en branch "entrega_final"

### LOGICA INTERNA
#### El programa contiene una lista de equipos y una lista de partidos
#### Los equipos tienen un vector de fases que contiene un vector de partidos con punteros a los partidos en la lista
#### Al usuario se le permite crear un mundial incoherente, pero se revisara la coherencia del mundial con cada corrida de programa y, en caso de ser incoherente, tendra la posibilidad de ver las incoherencias encontradas.
#### La validacion realizada es de coherencia de fases dentro de cada equipo (que haya pasado todas las etapas previas a su fase mas alta) y de coherencia general (que la cantidad de equipos en cada etapa sea correcta). 
#### Se asume que las eliminatorias son fijas (Octavos, Cuartos, Semifinal, Final y Tercer Puesto) y que puede haber cualquier cantidad de equipos en los ocho grupos (pero solamente pasan los dos mejores)

### Compilado con el comando  
##### g++ -Wall -Werror -Wconversion $(ls *.cpp) -o main.o

### VERSION 
##### stesta@DESKTOP-G9MH9QV:/mnt/c/Users/Santiago Testa/Programas/AYP2/AYP2-TP2$ g++ --version
##### g++ (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0
##### Copyright (C) 2021 Free Software Foundation, Inc.
##### This is free software; see the source for copying conditions.  There is NO
##### warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
