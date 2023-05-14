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
    int largo = len_string(linea);

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

    if (fase.compare("grupos") == 1){
        // SI ESTA VACIO, CREAR FASE
        if (this->fases.size() == 0){
            Fase* nuevo_grupos = new Fase;
            this->fases.push_back(nuevo_grupos);
            nuevo_grupos->AsignarFase(fase);
        }
        this->fases[0]->AgregarPartido(partido);
    }
    else {
        // DEBUG
        std::cout << "Equipo: " << this->nombre << " NUEVA ELIM: " << fase << std::endl;

        Fase* nueva_eliminatoria = new Fase;
        nueva_eliminatoria->AgregarPartido(partido);
        nueva_eliminatoria->AsignarFase(fase);

        int fase_numerica = fase_a_numero(fase);
        if (int(this->fases.size()) < fase_numerica)
            this->fases.push_back(nueva_eliminatoria);
        else 
            this->fases.insert(this->fases.begin() + fase_numerica, nueva_eliminatoria);
    }
}

bool Equipo::ValidarMundialEquipo(bool verbose){
    //std::tuple <bool,bool,bool,bool,bool,bool> fases_existentes = this->MostrarFasesExistentes();
    
    bool valido = true;
    /*
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
    */
    
    return valido;
}

int Equipo::BuscarFase(std::string fase){
    int i = 0;
    int CANT_FASES = int(this->fases.size());
    while (i < CANT_FASES && (fase.compare(this->fases[i]->MostrarFase()) != 1))
        i++;
    
    if (i == CANT_FASES)
        return -1;
    else
        return i;
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