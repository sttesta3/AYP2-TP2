#include "Equipo.h"

Equipo::Equipo(){
    //ctor
}

Equipo::~Equipo()
{
    //dtor
}

// METODOS DE MOSTRAR
std::string Equipo::MostrarNombre(void){
    return this->nombre;
}

char Equipo::MostrarGrupo(void){
    return this->grupo;
}

int Equipo::ValidarEquipo(std::string linea){
    int equipo_valido = 0;
    int largo = int(linea.size());

    // SI TERMINA EN ' X', entonces itera pa00ra chequear que sea alfabetico
    if (is_alfa(linea[largo - 1]) && (int)linea[largo - 2] == 32){
        int i = 0;
        while (equipo_valido == 0 && i < largo - 2){
            if (!is_alfa(linea[i]))
                equipo_valido = 1;
            i += 1;
        }
    }
    else
        equipo_valido = 1;

    // ASIGNAR VALORES A EQUIPO
    if (equipo_valido == 0){
        this->nombre = linea;
        this->nombre[largo - 1] = '\0';
        this->nombre[largo - 2] = '\0';

        this->grupo = linea[largo - 1];
        this->original_de_archivo = true;
    }

    return equipo_valido;
}

// METODOS DE ASIGNAR
void Equipo::AsignarNombre(std::string nombre){
    this->nombre = nombre;
}

void Equipo::AsignarGrupo(char grupo){
    this->grupo = grupo;
}


void Equipo::AgregarPartido(Partido* partido, std::string fase){
    // SE TOMARON COMO BASE ALGUNO DE LOS EJEMPLOS DE MicrosoftLearn
    // https://learn.microsoft.com/es-es/cpp/standard-library/vector-class?view=msvc-170#insert 

    if (cmp_string("grupos",fase)){
        // SI ESTA VACIO, CREAR FASE
        if (this->fases.size() == 0){
            Fase* nuevo_grupos = new FaseGrupo;
            this->fases.push_back(nuevo_grupos);
            nuevo_grupos->AsignarFase("grupos");
        }
        this->fases[0]->AgregarPartido(partido);
    }
    else {
        // DEBUG std::cout << "Equipo: " << this->nombre << " NUEVA ELIM: " << fase << std::endl;

        Fase* nueva_eliminatoria = new FaseEliminatoria;
        nueva_eliminatoria->AgregarPartido(partido);
        nueva_eliminatoria->AsignarFase(fase);

        int fase_numerica = fase_a_numero(fase);
        if (int(this->fases.size()) < fase_numerica)
            this->fases.push_back(nueva_eliminatoria);
        else 
            this->fases.insert(this->fases.begin() + fase_numerica, nueva_eliminatoria);
    }
}

bool Equipo::EliminarPartido(Partido* partido, std::string fase){
    int i = 0;
    int POSICION_FASE = this->BuscarFase(fase);
    int CANT_PARTIDOS = int(this->fases[POSICION_FASE]->partidos.size());

    while (i < CANT_PARTIDOS && this->fases[POSICION_FASE]->partidos[i] != partido)
        i += 1;

    if (i != CANT_PARTIDOS)
        this->fases[POSICION_FASE]->partidos.erase(this->fases[POSICION_FASE]->partidos.begin() + i);

    return (i != CANT_PARTIDOS);
}

bool Equipo::ValidarMundialEquipo(bool verbose){
    //std::tuple <bool,bool,bool,bool,bool,bool> fases_existentes = this->MostrarFasesExistentes();
    
    //DEBUG 
    /*
    std::cout << "IN VALIDARMUNDIALEQUIPO" << std::endl;
    std::cout << "SECOND " << (this->BuscarFase("octavos") == -1) << std::endl;
    std::cout << "POSICION: " << this->BuscarFase("grupos") << std::endl;
    std::cout << "FIRST " << this->fases[this->BuscarFase("grupos")]->PasoFase(this) << std::endl;
    */
    // LLEGUE AL SEGUNDO, EL PROBLEMA ESTA EN LA PRIMER PARTE


    bool valido = true;
    if (this->fases[this->BuscarFase("grupos")]->PasoFase(this) && this->BuscarFase("octavos") == -1 ){
        if (verbose)
            std::cout << to_upper(this->nombre) << " PASO LA FASE DE GRUPOS PERO NO ESTA EN OCTAVOS" << std::endl;
        valido = false;
    }
    if (this->fases[this->BuscarFase("octavos")]->PasoFase(this) && this->BuscarFase("cuartos") == -1 ){
        if (verbose)
            std::cout << to_upper(this->nombre) << "GANO OCTAVOS PERO NO ESTA EN CUARTOS" << std::endl;
        valido = false;
    }
    if (this->fases[this->BuscarFase("cuartos")]->PasoFase(this) && this->BuscarFase("semifinales") == -1 ){
        if (verbose)
            std::cout << to_upper(this->nombre) << " GANO CUARTOS PERO NO ESTA EN SEMIFINALES" << std::endl;
        valido = false;
    }
    if (this->fases[this->BuscarFase("semifinales")]->PasoFase(this) && this->BuscarFase("final") == -1 ){
        if (verbose)
            std::cout << to_upper(this->nombre) << " GANO SEMIFINAL PERO NO ESTA EN FINAL" << std::endl;
        valido = false;
    }
    if (!this->fases[this->BuscarFase("semifinales")]->PasoFase(this) && this->BuscarFase("tercer puesto") == -1 ){
        if (verbose)
            std::cout << to_upper(this->nombre) << " PERDIO SEMIFINAL PERO NO ESTA EN TERCER PUESTO" << std::endl;
        valido = false;
    }
    
    return valido;
}

int Equipo::BuscarFase(std::string fase){
    int i = 0;
    int CANT_FASES = int(this->fases.size());
    while (i < CANT_FASES && (fase.compare(this->fases[i]->MostrarFase()) != 1))
        i++;
    
    if (i == CANT_FASES)
        return 0;
    else
        return i;
}

int Equipo::MostrarFaseFinal(){
    std::tuple <bool,bool,bool,bool,bool,bool> fases_existentes = this->MostrarFasesExistentes();

    int resultado = 0;
    if (std::get<0>(fases_existentes)){
        if (std::get<1>(fases_existentes))
            resultado += 1;
        if (std::get<2>(fases_existentes))
            resultado += 1;
        if (std::get<3>(fases_existentes))
            resultado += 1;
        if (std::get<4>(fases_existentes))
            resultado += 1;        
        if (std::get<5>(fases_existentes))
            resultado += 2;   
    }
    
    if (resultado < 0 || resultado > 5)
        resultado = 0;

    return resultado;
}

bool Equipo::TieneFase(std::string fase){
    bool resultado = false;
    std::tuple <bool,bool,bool,bool,bool,bool> fases_existentes = this->MostrarFasesExistentes();

    if (fase.compare("grupos") == 1 && std::get<0>(fases_existentes))
        resultado = true;
    else if (fase.compare("octavos") == 1 && std::get<1>(fases_existentes))
        resultado = true;
    else if (fase.compare("cuartos") == 1 && std::get<2>(fases_existentes))
        resultado = true;
    else if (fase.compare("semifinales") == 1 && std::get<3>(fases_existentes))
        resultado = true;
    else if (fase.compare("tercer puesto") == 1 && std::get<4>(fases_existentes))
        resultado = true;
    else if (fase.compare("final") == 1 && std::get<5>(fases_existentes))
        resultado = true;

    return resultado;
}

Partido* Equipo::BuscarPartido(std::string fase, Equipo* rival){
    int CANT_PARTIDOS = int(this->fases[this->BuscarFase(fase)]->partidos.size());
    int POSICION_FASE;
    int i = 0;

    Partido* encontrado = nullptr;
    while (i < CANT_PARTIDOS && !encontrado){
        POSICION_FASE = this->BuscarFase(fase);
        // Compara rival contra el equipo que no coincide con su nombre. Si encuentra coincidencia, es el partido buscado
        if ( this->MostrarNombre().compare(this->fases[POSICION_FASE]->partidos[i]->MostrarEquipos(true)->MostrarNombre()) == 1 ){
            if (rival->MostrarNombre().compare(this->fases[POSICION_FASE]->partidos[i]->MostrarEquipos(false)->MostrarNombre()) == 1)
                encontrado = this->fases[POSICION_FASE]->partidos[i];
        }
        else{
            if (rival->MostrarNombre().compare(this->fases[POSICION_FASE]->partidos[i]->MostrarEquipos(true)->MostrarNombre()) == 1)
                encontrado = this->fases[POSICION_FASE]->partidos[i];
        }

        if (!encontrado)
            i += 1;
    }

    return encontrado;
}

Fase* Equipo::MostrarFase(int posicion){
    if (posicion < 0)
        return nullptr;
    else if (posicion >= int(this->fases.size()))
        return nullptr;
    else
        return this->fases[posicion];
}

void Equipo::NoEsOriginal(){
    this->original_de_archivo = false;
}

int Equipo::CalcularPuntajeGrupos(){
    return this->fases[this->BuscarFase("grupos")]->CalcularPuntaje(this);
}

void Equipo::MostrarPuntosDelGrupo(){
    int POSICION_GRUPO = this->BuscarFase("grupos");
    int CANT_EQUIPOS = int(this->fases[POSICION_GRUPO]->partidos.size());
    std::cout << "CANT Equipos: " << CANT_EQUIPOS << std::endl;
    // Agregamos los equipos ordenados por puntos a un vector
    std::vector <Equipo*> Equipos_por_puntaje;
    Equipos_por_puntaje.push_back(this);

    Equipo* equipo_a_insertar;
    int ii; bool iterar;

    int puntos_equipo; int puntos_vector;
    for (int i=0; i < CANT_EQUIPOS; i++){
        ii = 0; iterar = true;
        while (iterar && ii < int(Equipos_por_puntaje.size())){
            // Compara rival contra el equipo que no coincide con su nombre. Si encuentra coincidencia, es el partido buscado
            if ( this->MostrarNombre().compare(this->fases[POSICION_GRUPO]->partidos[i]->MostrarEquipos(true)->MostrarNombre()) != 1 ){
                equipo_a_insertar = this->fases[POSICION_GRUPO]->partidos[i]->MostrarEquipos(true);
                puntos_equipo = equipo_a_insertar->CalcularPuntajeGrupos();
                puntos_vector = Equipos_por_puntaje[ii]->CalcularPuntajeGrupos();
                if (puntos_equipo > puntos_vector){
                    Equipos_por_puntaje.insert(Equipos_por_puntaje.begin() + ii,equipo_a_insertar);
                    iterar = false;
                }
                else
                    ii += 1;

            }
            else if ( this->MostrarNombre().compare(this->fases[POSICION_GRUPO]->partidos[i]->MostrarEquipos(false)->MostrarNombre()) != 1 ){ 
                equipo_a_insertar = this->fases[POSICION_GRUPO]->partidos[i]->MostrarEquipos(false);
                puntos_equipo = equipo_a_insertar->CalcularPuntajeGrupos();
                puntos_vector = Equipos_por_puntaje[ii]->CalcularPuntajeGrupos();
                if (puntos_equipo > puntos_vector){
                    Equipos_por_puntaje.insert(Equipos_por_puntaje.begin() + ii,equipo_a_insertar);
                    iterar = false;
                }
                else
                    ii += 1;
            }

        }

        if (iterar)
            Equipos_por_puntaje.push_back(equipo_a_insertar);
    }

    // Mostramos resultado
    for (int i = 0; i < int(Equipos_por_puntaje.size()); i++)
        std::cout << "Puntos: " << Equipos_por_puntaje[i]->CalcularPuntajeGrupos() << " Equipo: " <<  Equipos_por_puntaje[i]->MostrarNombre() << std::endl;
}

std::tuple <bool,bool,bool,bool,bool,bool> 
Equipo::MostrarFasesExistentes(){
    // INICIALIZAR TUPLA RESULTADO
    std::tuple <bool,bool,bool,bool,bool,bool> resultado;
    std::get<0>(resultado) = false;
    std::get<1>(resultado) = false;
    std::get<2>(resultado) = false;
    std::get<3>(resultado) = false;
    std::get<4>(resultado) = false;
    std::get<5>(resultado) = false;

    // EXISTE O NO EXISTE LA FASE
    int CANT_FASES = int(this->fases.size());
    for (int i=0; i < CANT_FASES; i++){
        if ((this->fases[i]->MostrarFase()).compare("grupos") == 1)
            std::get<0>(resultado) = true;
        else if ((this->fases[i]->MostrarFase()).compare("octavos") == 1)
            std::get<1>(resultado) = true;
        else if ((this->fases[i]->MostrarFase()).compare("cuartos") == 1)
            std::get<2>(resultado) = true;
        else if ((this->fases[i]->MostrarFase()).compare("semifinales") == 1)
            std::get<3>(resultado) = true;
        else if ((this->fases[i]->MostrarFase()).compare("tercer puesto") == 1)
            std::get<4>(resultado) = true;
        else if ((this->fases[i]->MostrarFase()).compare("final") == 1)
            std::get<5>(resultado) = true;
    }

    return resultado;
}


void Equipo::MostrarPartidosFase(std::string fase){
    if (cmp_string("grupos",fase)){
        int CANT_FASES = int(this->fases.size());
        int i = 0;

        Equipo* equipo1, *equipo2;
        Partido* partido;
        std::tuple <int,int> resultado;
        while (i < CANT_FASES && !cmp_string(this->fases[i]->MostrarFase(),fase) )
            i += 1;

        if (i < CANT_FASES){
            int CANT_PARTIDOS = int(this->fases[i]->partidos.size());

            for (int ii = 0; ii < CANT_PARTIDOS; ii++){
                partido = this->fases[i]->partidos[ii];
                equipo1 = partido->MostrarEquipos(true);
                equipo2 = partido->MostrarEquipos(false);
                resultado = partido->MostrarPuntos();
                
                std::cout << equipo1->MostrarNombre() << " vs. " << equipo2->MostrarNombre() << " " << partido->MostrarGoles(true) << " a " << partido->MostrarGoles(false) << std::endl;
            }
        }
    }
    else
        std::cout << "Entraste cualquier fruta" << std::endl;
}