# AYP2-TP2
## TP2 AYP2 - El error de La'eeb, la venganza de La'eebb

### NOTAS IMPORTANTES
#### Se realizo polimorfismo de partidos, debido a que se interpreto que a eso se referian en la consigna (Una fase no guarda penales, lo guardan sus partidos). Y en si, los metodos son los mismos tanto para fase de grupos o de eliminatoria (Calcular puntaje y determinar si el equipo paso o no). Y creo que esos casos pueden resolverse con una sobrecarga de operadores ()

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
