#include "Mundial.h"

//using namespace std;
Mundial::Mundial()
{
    // CONSTRUCTOR
    this->equipos = new Lista<Equipo>;
    this->partidos = new Lista<Partido*>;

    this->primero = nullptr;
    this->segundo = nullptr;
    this->tercero = nullptr;
}

Mundial::~Mundial()
{
    // DESTRUCTOR
    // COMO TODA LA MEMORIA DINAMICA DEL PROGRAMA DEPENDE DE ESTAS DOS LISTAS, ES SUFICIENTE BORRARLAS PARA QUE SE BORRE TUTI
    this->partidos->IniciarIterador();
    Partido* borrar;
    while (this->partidos->MostrarIterador() != nullptr){
        borrar = this->partidos->MostrarIterador()->MostrarContenido();
        this->partidos->AvanzarIterador(1);
        delete borrar;
    }
    delete this->partidos;
    delete this->equipos;
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
            this->equipos->AgregarElemento(nuevo_equipo); 
            //std::cout << this->BuscarEquipo(nuevo_equipo.MostrarNombre()) << std::endl;
            //this->AgregarGrupo(this->BuscarEquipo(nuevo_equipo.MostrarNombre()));
        }
    }
    entrada.close();

    Equipo* para_cargar_grupos;
    this->equipos->IniciarIterador();
    while (this->equipos->MostrarIterador() != nullptr){
        para_cargar_grupos = this->equipos->MostrarIterador()->MostrarDireccion();
        this->AgregarGrupo(para_cargar_grupos);
        this->equipos->AvanzarIterador(1);
    }
    // DEBUG     this->ListarEquipos();

    return 0;
}

void Mundial::AgregarGrupo(Equipo* equipo){
    int CANT_GRUPOS = this->MostrarCantidadGrupos();
    int i = 0;
    bool iterar = true;

    char grupo_del_equipo = equipo->MostrarGrupo();

    //DEBUG    std::cout << "POR ENTRAR AL WHILE" << std::endl;
    while (i < CANT_GRUPOS && iterar){
        if ((int)grupo_del_equipo < (int)this->grupos[i]->MostrarGrupo()){
            iterar = false;
            this->grupos.insert(this->grupos.begin() + i,equipo);
        }
        else if ((int)grupo_del_equipo == (int)this->grupos[i]->MostrarGrupo())
            iterar = false;
        else
            i++;
    }

    if (iterar){
        // debug std::cout << "PRIMER ELMENTO EN GRUPOS" << std::endl;
        this->grupos.push_back(equipo);
    }
}

int Mundial::MostrarCantidadEquipos(){
    return this->equipos->MostrarCantElementos();
}

int Mundial::MostrarCantidadGrupos(){
    return int(this->grupos.size());
}

int Mundial::CargarPartidos(std::string archivo2){
    std::ifstream entrada(archivo2);
    if (!entrada){
        std::cerr << "ERROR AL ABRIR ARCHIVO DE PARTIDOS" << std::endl;
        return 1;
    }

    std::string fase;
    std::string linea;
    int num_linea = 0;
    while (getline(entrada, linea)){
        linea = to_lower(linea);
        // std::cout << "LINEA PARTIDO: " << linea << std::endl;

        // DEBUG DictarLinea(linea);

        if (divisor_de_fase(linea)){
            fase = linea;
            // DEBUG std::cout << "ESTO ES UNA FASE" << std::endl;
        }
        else {
            // POLIMORFISMO !!!!!!
            // CREAR PARTIDO SEGUN FASE
            Partido* nuevo_partido;
            if (cmp_string(fase,"grupos"))
                nuevo_partido = new PartidoGrupo;
            else
                nuevo_partido = new PartidoEliminatoria;

            std::tuple <std::string,std::string> encontrado;
            Equipo *equipo1,*equipo2;
            encontrado = nuevo_partido->ValidarPartido(linea);
            if ( std::get<0>(nuevo_partido->MostrarPuntos() ) == -5){
                std::cerr << "LINEA PARTIDO INVALIDA: " << linea << std::endl;
                entrada.close(); 
                delete nuevo_partido;
                return 1;
            }
            else if ( !(equipo1 = this->BuscarEquipo(std::get<0>(encontrado)) ) ){
                std::cerr << "EQUIPO NO ENCONTRADO: " << std::get<0>(encontrado) << " Partido: " << linea << std::endl;
                entrada.close(); 
                delete nuevo_partido;
                return 1;
            }
            else if (!(equipo2 = this->BuscarEquipo(std::get<1>(encontrado)))){
                std::cerr << "EQUIPO NO ENCONTRADO: " << std::get<1>(encontrado) << " Partido: " << linea << std::endl;
                entrada.close(); 
                delete nuevo_partido;
                return 1;
            }

            // ASIGNAR EQUIPOS AL NUEVO PARTIDO -> AGREGAR PARTIDO A LISTA -> AGREGAR PARTIDO A FASE
            nuevo_partido->AsignarEquipo(equipo1,true); nuevo_partido->AsignarEquipo(equipo2,false); nuevo_partido->AsignarLinea(num_linea);
            this->partidos->AgregarElemento(nuevo_partido);
            equipo1->AgregarPartido(nuevo_partido,fase); equipo2->AgregarPartido(nuevo_partido,fase);
            
            // PODIO
            if (fase.compare("final") == 1){
                // DEBUG 
                // std::tuple <int,int> result = nuevo_partido->MostrarPuntos();
                // std::cout << "P1: " << std::get<0>(result) << " "<< nuevo_partido->MostrarEquipo(true)->MostrarNombre() << std::endl; 
                // std::cout << "P2: " << std::get<1>(result) << " "<< nuevo_partido->MostrarEquipo(false)->MostrarNombre() << std::endl; 

                this->primero = nuevo_partido->MostrarGanador();
                this->segundo = nuevo_partido->MostrarPerdedor();
            }
            else if (fase.compare("tercer puesto") == 1)
                this->tercero = nuevo_partido->MostrarGanador();
        }

        num_linea += 1;
    }

    entrada.close();
    return 0;
}

// FUNCIONES DE MENU
void Mundial::MostrarMenu(void){
    // DEBUG    
    std::cout << "DEBUGs" << std::endl;
    this->ListarPartidos();
    std::cout << "════════════════════════════════════════════════════════════════════════════════════" << std::endl;
    /* DEBUG
    for (int i = 0; i < int(this->grupos.size()); i++)
        this->grupos[i]->MostrarPartidosFase("grupos");

    std::cout << "════════════════════════════════════════════════════════════════════════════════════" << std::endl;
    */
    this->FiguraAscii1();
    std::cout << "════════════════════════════════════════════════════════════════════════════════════" << std::endl;
    std::cout << "Bienvenido a la aplicacion no oficial del mundial de Qatar!" << std::endl;
    std::cout << "════════════════════════════════════════════════════════════════════════════════════" << std::endl;
    
    bool mostrar_menu = true;
    while (mostrar_menu){
        std::cout << "Opciones (ingresar numero de opcion)" << std::endl;
        std::cout << "1. Listar equipos" << std::endl;
        std::cout << "2. Mostrar los equipos en primer segundo y tercer lugar" << std::endl;
        std::cout << "3. Buscar equipo por nombre" << std::endl;
        std::cout << "4. Mostrar por fase los paises ordenados por puntaje" << std::endl;
        std::cout << "5. Actualizar partidos" << std::endl;
        std::cout << "6. Salir" << std::endl;

        bool mundial_valido = this->ValidarMundial(false);
        if (!mundial_valido){
            std::cout << "════════════════════════════════════════════════════════════════════════════════════" << std::endl;
            std::cout << "INCOHERENCIA(s) ENCONTRADA(s) EN EL MUNDIAL INGRESADO" << std::endl;
            std::cout << "7. Mostrar detalles de incoherencias en el mundial" << std::endl;
            std::cout << "════════════════════════════════════════════════════════════════════════════════════" << std::endl;
        }

        char input; std::cin >> input;
        if (int(input) < 48 || int(input) > 57)
            input = '/';           // UN NUMERO RANDOM INVALIDO (ascii 47)

        switch ( int(input) % 48 ){
            case 0: // DEBUG
                std::cout << "════════════════════════════════════════════════════════════════════════════════════" << std::endl; this->ListarPartidos(); break;
            case 1:
                std::cout << "════════════════════════════════════════════════════════════════════════════════════" << std::endl; this->ListarEquipos(); break;
            case 2:
                std::cout << "════════════════════════════════════════════════════════════════════════════════════" << std::endl; this->Podio();break;
            case 3:
                { std::cout << "════════════════════════════════════════════════════════════════════════════════════" << std::endl; std::cout << "Ingrese nombre del equipo:" << std::endl; std::string busqueda; std::cin >> busqueda; this->MostrarBuscarEquipo(busqueda); break; }
            case 4: 
                std::cout << "════════════════════════════════════════════════════════════════════════════════════" << std::endl; this->MenuPuntos(); break;
            case 5:
                std::cout << "════════════════════════════════════════════════════════════════════════════════════" << std::endl; this->MenuActualizarPartido(); break;
            case 6:
            {
                std::cout << "════════════════════════════════════════════════════════════════════════════════════" << std::endl;
                bool mostrar_menu_guardado = true;
                while (mostrar_menu_guardado){
                    if (!mundial_valido)
                        std::cout << "RECORDATORIO: Mundial Invalido" << std::endl;
                    std::cout << "¿DESEA GUARDAR LAS MODIFICACIONES REALIZADAS?" << std::endl;
                    std::cout << "0. No" << std::endl;
                    std::cout << "1. Si" << std::endl;

                    char input_guardado; std::cin >> input_guardado;
                    if (int(input_guardado) != 48 && int(input_guardado) != 49)
                        input_guardado = '/';           // UN NUMERO RANDOM INVALIDO

                    switch ( int(input_guardado) % 48 ){
                        case 0: 
                            mostrar_menu_guardado = false; break;
                        case 1:
                        {
                            
                            if (!this->Guardado())
                                std::cerr << "ERROR DE GUARDADO" << std::endl;
                        }; break;
                        default:
                            std::cout << "GUARDADO Opcion invalida, favor reingresar" << std::endl; break;
                    }

                }
                mostrar_menu = false;
            }; break;
            case 7:
            {
                if (!mundial_valido)
                    this->ValidarMundial(true);
                else
                    std::cout << "VALIDAR Opcion invalida, favor reingresar" << std::endl;
                break;
            }
            default:
                std::cout << "MENU Opcion invalida, favor reingresar" << std::endl; break;
        }
    }
}

void Mundial::MenuActualizarPartido(void){
    bool mostrar_menu_actualizar = true;

    while(mostrar_menu_actualizar){
        std::cout << "1. Agregar partido" << std::endl;
        std::cout << "2. Actualizar partido" << std::endl;
        std::cout << "3. Eliminar partido" << std::endl;
        std::cout << "4. Volver" << std::endl;
        
        char input_actualizar; std::cin >> input_actualizar;
        if (int(input_actualizar) < 48 || int(input_actualizar) > 57)
            input_actualizar = '/';           // UN NUMERO RANDOM INVALIDO (ascii 47)

        switch ( int(input_actualizar) % 48 ){
            case 1:
                std::cout << "════════════════════════════════════════════════════════════════════════════════════" << std::endl; this->AgregarPartido(); mostrar_menu_actualizar = false; break;
            case 2:
                std::cout << "════════════════════════════════════════════════════════════════════════════════════" << std::endl; this->ActualizarPartido(); mostrar_menu_actualizar = false; break;
            case 3:
                std::cout << "════════════════════════════════════════════════════════════════════════════════════" << std::endl; this->EliminarPartido(); mostrar_menu_actualizar = false; break;
            case 4:
                std::cout << "════════════════════════════════════════════════════════════════════════════════════" << std::endl; mostrar_menu_actualizar = false; break;
            default:
                std::cout << "MENU Opcion invalida, favor reingresar" << std::endl; break;
        }

        std::cout << "════════════════════════════════════════════════════════════════════════════════════" << std::endl;

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

    std::cout << "1ro: " << to_upper(this->primero->MostrarNombre()) << std::endl;
    std::cout << "2do: " << to_upper(this->segundo->MostrarNombre()) << std::endl;
    std::cout << "3ro: " << to_upper(this->tercero->MostrarNombre()) << std::endl;
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

        // DEBUG std::cout << "Normal, EQUIPO BUSCADO: " << busqueda << std::endl;
        while (this->equipos->MostrarIterador() != nullptr && comparar_alfabeticamente(busqueda,this->equipos->MostrarIterador()->MostrarContenido().MostrarNombre()) != -1){
            // DEBUG std::cout << "encontrado: " << this->equipos->MostrarIterador()->MostrarContenido().MostrarNombre() << std::endl;
            this->equipos->AvanzarIterador(1);
        }

        if (!this->equipos->MostrarIterador())
            return nullptr;
        else
            return this->equipos->MostrarIterador()->MostrarAnterior()->MostrarDireccion();
    }
    else{
        // DEBUG std::cout << "Inverso, EQUIPO BUSCADO: " << busqueda << std::endl;
        this->equipos->IniciarIteradorAlUltimo();

        while (this->equipos->MostrarIterador() != nullptr && comparar_alfabeticamente(busqueda,this->equipos->MostrarIterador()->MostrarContenido().MostrarNombre()) != 1){
            // DEBUG std::cout << "encontrado: " << this->equipos->MostrarIterador()->MostrarContenido().MostrarNombre() << std::endl;
            this->equipos->RetrocederIterador(1);
        }

        if (!this->equipos->MostrarIterador())
            return nullptr;
        else
            return this->equipos->MostrarIterador()->MostrarSiguiente()->MostrarDireccion();
    }
}

void Mundial::MostrarBuscarEquipo(std::string busqueda){
    Equipo* equipo = this->BuscarEquipo(busqueda);
    if (equipo == nullptr)
        std::cout << "NO HAY COINCIDENCIAS" << std::endl;
    else{
        std::cout << "EQUIPO: " << to_upper(equipo->MostrarNombre()) << std::endl;
        std::cout << "GRUPO: " << char(toupper(equipo->MostrarGrupo())) << std::endl;

        if (equipo == this->primero)
            std::cout << "CAMPEON DEL MUNDO" << std::endl;
        else if (equipo == this->segundo)
            std::cout << "SUB-CAMPEON DEL MUNDO" << std::endl;
        else if (equipo == this->tercero)
            std::cout << "TERCERO" << std::endl;
        else {
            switch (equipo->MostrarFaseFinal()){
                case 0:
                    std::cout << "FASE HASTA LA QUE LLEGO: GRUPOS" << std::endl; break;
                case 1:
                    std::cout << "FASE HASTA LA QUE LLEGO: OCTAVOS" << std::endl; break;
                case 2:
                    std::cout << "FASE HASTA LA QUE LLEGO: CUARTOS" << std::endl; break;
                case 3:
                    std::cout << "FASE HASTA LA QUE LLEGO: SEMIFINAL" << std::endl; break;
                case 4:
                    std::cout << "FASE HASTA LA QUE LLEGO: TERCER PUESTO (Cuarto)" << std::endl; break;
            }
        }
    }
}
void Mundial::MenuPuntos(void){   
    int CANT_GRUPOS = this->MostrarCantidadGrupos();
    
    // DEBUG
    //for (int i = 0; i < CANT_GRUPOS; i++)
      //  this->grupos[i]->MostrarPartidosFase("grupos");
    


    std::cout << "PUNTOS POR GRUPO" << std::endl;
    for (int i = 0; i < CANT_GRUPOS; i++){
        std::cout << "GRUPO: " << char(toupper(this->grupos[i]->MostrarGrupo())) << std::endl;
        this->grupos[i]->MostrarPuntosDelGrupo();
    }
}

int Mundial::AgregarPartido(void){
    std::string input;
    
    // SOLICITAR FASE
    std::string fase;
    input = "Algo random para que itere";
    while (!divisor_de_fase(input)){
        std::cout << "Ingrese fase del partido a agregar: " << std::endl; std::cin >> input;
        if (!divisor_de_fase(input))
            std::cout << "Invalido, favor reingresar" << std::endl;
    }
    fase = input;

    // SOLICITAR EQUIPOS
    Equipo *equipo1 = this->SolicitarOCrearEquipo();
    if (!equipo1){
        std::cerr << "No se encontro/Creo equipo 1" << std::endl;
        return 1;
    }
    Equipo *equipo2 = this->SolicitarOCrearEquipo();
    if (!equipo1){
        std::cerr << "No se encontro/Creo equipo 1" << std::endl;
        return 1;
    }

    Partido* nuevo_partido;
    if (fase.compare("grupos") == 1)
        nuevo_partido = new PartidoGrupo;
    else
        nuevo_partido = new PartidoEliminatoria;

    if (!nuevo_partido){
        std::cerr << "No se pudo crear partido" << std::endl;
        return 1;
    }

    nuevo_partido->SolicitarValores(equipo1,equipo2,equipo1->MostrarNombre(),equipo2->MostrarNombre());
    nuevo_partido->NoEsOriginal();

    // AGREGAR PARTIDO
    this->partidos->AgregarElemento(nuevo_partido);
    equipo1->AgregarPartido(nuevo_partido,fase); equipo2->AgregarPartido(nuevo_partido,fase);

    return 0;
}

Equipo* Mundial::SolicitarOCrearEquipo(){
    bool equipo_encontrado = false;
    std::string input;

    Equipo auxiliar;
    Equipo* resultado;
    while (!equipo_encontrado){
        
        bool equipo_valido = false;
        while (!equipo_valido){
            std::cout << "Ingrese nombre del primer equipo: " << std::endl; std::cin >> input;
            equipo_valido = auxiliar.ValidarEquipo(input);
        } 

        resultado = this->BuscarEquipo(input);
        if (!resultado){
            std::cout << "El equipo " << input << " no existe" << std::endl;
            std::cout << "¿Desea crear un equipo nuevo para esto?" << std::endl;
            std::cout << "DISCLAIMER: Crear un nuevo equipo probablemente genere muchas inconsistencias" << std::endl;

            bool crear_nuevo_equipo = false;
            while (!crear_nuevo_equipo){
                std::cout << "0. No" << std::endl;
                std::cout << "1. Si" << std::endl;
                std::cin >> input;

                if (input.compare("0") == 1)
                    crear_nuevo_equipo = true;
                else if (input.compare("1") == 1){
                    crear_nuevo_equipo = true; 

                    char grupo;
                    bool grupo_valido = false;
                    while (!grupo_valido){
                        std::cout << "Ingrese grupo del equipo: " << std::endl; std::cin >> grupo;
                        grupo_valido = this->ValidarGrupo(grupo);
                    }
                    auxiliar.AsignarGrupo(grupo); auxiliar.NoEsOriginal();
                    this->equipos->AgregarElemento(auxiliar);
                    
                    resultado = this->BuscarEquipo(auxiliar.MostrarNombre());
                    this->AgregarGrupo(resultado);
                }
                else
                    std::cout << "Opcion Invalida, favor reingresar" << std::endl;
            }
        }
    }
    
    return resultado;
}

bool Mundial::ValidarGrupo(char input){
    // SOLO SE PERMITIRAN GRUPOS EXISTENTES. LE ESTAMOS DANDO DEMASIADA FLEXIBILIDAD AL USUARIO Y NO SE LA MERECE
    bool iterar = true;
    
    this->equipos->IniciarIterador();
    while (iterar && this->equipos->MostrarIterador() != nullptr){
        if ( this->equipos->MostrarIterador()->MostrarContenido().MostrarGrupo() == input )
            iterar = false;
        else
            this->equipos->AvanzarIterador(1);
    }

    return !(iterar);
}
/*
int Mundial::CargarEquipo(Equipo equipo){

}
*/

int Mundial::ActualizarPartido(void){
    std::string fase;
    bool solicitar_valores = true;
    Equipo* equipo1;
    Equipo* equipo2;
    Partido* partido_a_actualizar;
    while (solicitar_valores){
        // Solicitar fase
        std::string input = "Evitando el error de capa 8, entre teclado y silla";
        while (!divisor_de_fase(input)){
            std::cout << "Ingrese fase del partido a modificar: " << std::endl; std::cin >> input;
            if (!divisor_de_fase(input))
                std::cout << "Invalido, favor reingresar" << std::endl;
        }
        fase = input;

        // Buscar equipo1 (si existe error, permite salir sin modificar)
        equipo1 = this->SolicitarEquipo(fase);
        solicitar_valores = (equipo1 != nullptr);
        if (!solicitar_valores)
            return 1;

        // Buscar equipo2 (si existe error, permite salir sin modificar)
        if (solicitar_valores)
            equipo2 = this->SolicitarEquipo(fase);
        solicitar_valores = (equipo2 != nullptr);
        
        if (!solicitar_valores)
            return 1;
        else {
            // Buscar Partido
            partido_a_actualizar = equipo1->BuscarPartido(fase, equipo2);
            if (!partido_a_actualizar){
                std::cout << "No se encontro el partido, volviendo al menu..." << std::endl;
                return 1;                
            }
            else{   // Punto de no retorno
                partido_a_actualizar->SolicitarValores(equipo1,equipo2,equipo1->MostrarNombre(),equipo2->MostrarNombre());
                solicitar_valores = false;
            }    
        }
    }
    return 0;
}

Equipo* Mundial::SolicitarEquipo(std::string fase){
    std::string input;
    Equipo* equipo = nullptr;
    bool salir = false;
    while (!equipo && !salir){
        std::cout << "Ingrese nombre del equipo: " << std::endl; std::cin >> input;
        equipo = this->BuscarEquipo(input);
        if (!equipo)
            std::cout << "Equipo no encontrado, favor reingresar" << std::endl;
        else if (!equipo->TieneFase(fase)){
            std::cout << equipo->MostrarNombre() << " no tiene la fase especificada." << std::endl;
            bool decision_irse_quedarse = false;
            while (!decision_irse_quedarse){
                std::cout << "1. Volver a ingresar equipo" << std::endl;
                std::cout << "2. Salir" << std::endl;

                if (input.compare("1") == 1){
                    decision_irse_quedarse = true; equipo = nullptr;
                }
                else if (input.compare("2") == 1){
                    decision_irse_quedarse = true; equipo = nullptr; salir = true;
                }
                else
                    std::cout << "Opcion invalida, favor reingresar" << std::endl;

            }
        }   
    }

    return equipo;
}
    

int Mundial::EliminarPartido(void){
    // Quita el partido de los vectores de fases de ambos equipos. Modifica los goles a -5, con esto indicamos que el partido debe borrarse
    // Se distingue partido de grupo/eliminatoria por si tienen penales o no (tell dont ask)
    // Luego en el borrado se busca en el archivo fase, linea (entre el valor de la linea y linea - cant. elementos borrados)

    std::string fase;
    bool solicitar_valores = true;
    Equipo* equipo1;
    Equipo* equipo2;
    Partido* partido_a_eliminar;
    while (solicitar_valores){
        // Solicitar fase
        std::string input = "Evitando el error de capa 8, entre teclado y silla";
        while (!divisor_de_fase(input)){
            std::cout << "Ingrese fase del partido a eliminar: " << std::endl; std::cin >> input;
            if (!divisor_de_fase(input))
                std::cout << "Invalido, favor reingresar" << std::endl;
        }
        fase = input;

        // Buscar equipo1 (si existe error, permite salir sin modificar)
        equipo1 = this->SolicitarEquipo(fase);
        solicitar_valores = (equipo1 != nullptr);
        if (!solicitar_valores)
            return 1;

        // Buscar equipo2 (si existe error, permite salir sin modificar)
        if (solicitar_valores)
            equipo2 = this->SolicitarEquipo(fase);
        solicitar_valores = (equipo2 != nullptr);
        
        if (!solicitar_valores)
            return 1;
        else {
            // Buscar Partido
            partido_a_eliminar = equipo1->BuscarPartido(fase, equipo2);
            if (!partido_a_eliminar){
                std::cout << "No se encontro el partido, volviendo al menu..." << std::endl;
                return 1;                
            }
            else{   // Punto de no retorno
                partido_a_eliminar->AsignarGoles(-5,true); partido_a_eliminar->AsignarGoles(-5,false);
                if (!equipo1->EliminarPartido(partido_a_eliminar,fase) || !equipo2->EliminarPartido(partido_a_eliminar,fase)){
                    std::cerr << "ERROR DESCONOCIDO AL ELIMINAR PARTIDO" << std::endl;
                }
                solicitar_valores = false;
            }    
        }
    }

    return 0;
}

bool Mundial::ValidarMundial(bool verbose){
    // ACEPTAREMOS INPUT THE USUARIO, PERO CON CADA CORRIDA DEL MENU SE ANALIZARA COHERENCIA DEL MUNDIAL 
    // Y SE LE AVISARA EN CASO DE ENCONTRAR INCOHERENCIAS
    
    bool iterar = true;
    // VALIDACION A NIVEL EQUIPO
    int CANTIDAD_DE_EQUIPOS = this->MostrarCantidadEquipos();
    bool equipo_valido = true;
    this->equipos->IniciarIterador();

    if (verbose)
        std::cout << "INCOHERENCIAS DE EQUIPOS" << std::endl;
    
    // CANT DE GRUPOS
    if (this->MostrarCantidadGrupos() != 8){
        if (verbose)
            std::cout << "Hay " << this->MostrarCantidadGrupos() << " grupos. Deberian ser 8" << std::endl;
        else
            iterar = false;
    }

    // EQUIPOS POR GRUPO
    if (iterar){
        int CANT_GRUPOS = int(this->grupos.size());
        int POSICION_GRUPOS;
        int cant_partidos;

        int i = 0;
        while (iterar && i < CANT_GRUPOS){
            POSICION_GRUPOS = this->grupos[i]->BuscarFase("grupos");
            cant_partidos = int(this->grupos[i]->MostrarFase(POSICION_GRUPOS)->partidos.size());
            if (cant_partidos == 0){
                if (verbose)
                    std::cout << "Hay un unico equipo en el grupo " <<  this->grupos[i]->MostrarGrupo() << std::endl;
                else
                    iterar = false;
            }
            else if (cant_partidos == 1){
                if (verbose){
                    std::cout << "Hay solo dos equipos en el grupo " <<  this->grupos[i]->MostrarGrupo() << std::endl;
                    std::cout << "No es un error logico, pero los equipos pasan de fase indistintamente del resultado de su partido " << std::endl;
                }
            }

            i += 1;
        }
    }

    int i = 0;
    while (i < CANTIDAD_DE_EQUIPOS && iterar){
        // DEBUG        std::cout << "DENTRO DEL WHILE" << std::endl;
        equipo_valido = this->equipos->MostrarIterador()->MostrarContenido().ValidarMundialEquipo(verbose);
        // DEBUG        std::cout << "VALIDE EQUIPO" << std::endl;
        i += 1;
        if (!verbose && !equipo_valido)
            iterar = false;                 // DEJA DE ITERAR SI NO ES VERBOSE
        else if (i != CANTIDAD_DE_EQUIPOS)
            this->equipos->AvanzarIterador(1);
    }

    // DEBUG       std::cout << "SALI DEL WHILE" << std::endl;

    // VALIDACION A NIVEL MUNDIAL
    if (iterar){
        std::vector <int> Equipos_Por_Eliminatoria;
        int CANT_FASES = 6;
        for (int i = 0; i < CANT_FASES; i++)
            Equipos_Por_Eliminatoria.push_back(0);
        
        // SUMAR CANTIDAD DE EQUIPOS POR FASE
        this->equipos->IniciarIterador();
        std::tuple <bool,bool,bool,bool,bool,bool> fases_existentes;
        for (int i=0; i < CANTIDAD_DE_EQUIPOS; i++){
            fases_existentes = this->equipos->MostrarIterador()->MostrarContenido().MostrarFasesExistentes();
            
            // SE HACE SUMATORIA MANUAL POR TUPLA (SOLO SE PUEDE ACCEDER CON INDICE CONSTANTE)
            if (std::get<0>(fases_existentes))
                Equipos_Por_Eliminatoria[0] += 1;
            if (std::get<1>(fases_existentes))
                Equipos_Por_Eliminatoria[1] += 1;
            if (std::get<2>(fases_existentes))
                Equipos_Por_Eliminatoria[2] += 1;
            if (std::get<3>(fases_existentes))
                Equipos_Por_Eliminatoria[3] += 1;
            if (std::get<4>(fases_existentes))
                Equipos_Por_Eliminatoria[4] += 1;
            if (std::get<5>(fases_existentes))
                Equipos_Por_Eliminatoria[5] += 1;

            this->equipos->AvanzarIterador(1);
        }

        if (!verbose){
            // BUSCAR HASTA ENCONTRAR UNA INCOHERENCIA
            iterar = (Equipos_Por_Eliminatoria[5] == 2);
            for (int i=1; i < 5 && iterar; i++)
                iterar = (Equipos_Por_Eliminatoria[i] == int(pow(2, 5 - i)));  
        }
        else {
            // MOSTRAR INCOHERENCIAS (si existen)
            if (Equipos_Por_Eliminatoria[5] != 2 || Equipos_Por_Eliminatoria[4] != 2 || Equipos_Por_Eliminatoria[3] != 4 || Equipos_Por_Eliminatoria[2] != 8 || Equipos_Por_Eliminatoria[1] != 16)
                std::cout << "INCOHERENCIAS GENERALES DEL MUNDIAL:" << std::endl;
            if (Equipos_Por_Eliminatoria[5] != 2)
                std::cout << "Hay " << Equipos_Por_Eliminatoria[5] << " EQUIPOS EN LA FINAL" << std::endl;
            if (Equipos_Por_Eliminatoria[4] != 2)
                std::cout << "Hay " << Equipos_Por_Eliminatoria[4] << " EQUIPOS EN TERCER PUESTO" << std::endl;                
            if (Equipos_Por_Eliminatoria[3] != 4)
                std::cout << "Hay " << Equipos_Por_Eliminatoria[3] << " EQUIPOS EN SEMIFINAL" << std::endl;                                
            if (Equipos_Por_Eliminatoria[2] != 8)
                std::cout << "Hay " << Equipos_Por_Eliminatoria[2] << " EQUIPOS EN CUARTOS" << std::endl;                                                
            if (Equipos_Por_Eliminatoria[1] != 16)
                std::cout << "Hay " << Equipos_Por_Eliminatoria[1] << " EQUIPOS EN OCTAVOS" << std::endl;                                                
        }
    }

    if (verbose){
        std::cout << "════════════════════════════════════════════════════════════════════════════════════" << std::endl;
        std::cout << "PARA QUE EL MUNDIAL SEA VALIDO, SE DEBEN CUMPLIR LAS SIGUIENTES CONDICIONES" << std::endl;
        std::cout << "1. Los equipos deben pasar todas las fases anteriores a la ultima fase que alcanzaron" << std::endl;
        std::cout << "2. Deben haber la cantidad correcta de equipos en cada fase eliminatoria" << std::endl;
        std::cout << "3. Deben haber por lo menos dos equipos por grupo" << std::endl;    
        std::cout << "════════════════════════════════════════════════════════════════════════════════════" << std::endl;
    }

    return iterar;
}

bool Mundial::Guardado(){
    // Lee Equipos Buscando bool not original_de_archivo. Si no es original, entonces lo guarda en el archivo
    // Lee Partidos Buscando bool not original_de_archivo o bool editado. 
    // Si es partido nuevo lo agrega en fase correspondiente, si es una edicion va a linea, borra y agrega linea del partido

    return true;
}

void Mundial::FiguraAscii1(void){
    std::cout << "⠀⠀⠀⠀⠀⠀⠀⢀⣀⠤⣤⣶⣶⣶⣶⣶⣶⣦⣤⢀⡀⠀⠀⠀⠀⠀⠀⠀⠀   " << std::endl;
    std::cout << "⠀⠀⠀⠀⢀⣤⠚⠁⢀⡤⠛⠛⠛⠛⠛⢿⠛⠉⠀⠉⠛⢶⣤⡀⠀⠀⠀⠀⠀" << std::endl;
    std::cout << "⠀⠀⠀⡰⠉⠀⣠⠖⠁⠀⠀⠀⠀⠀⠀⠈⡆⠀⠀⠀⠀⠀⠈⠻⣦⡀⠀⠀⠀" << std::endl;
    std::cout << "⠀⢀⡎⣀⣤⣶⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⢱⡀⠀⠀⠀⠀⠀⠀ ⠸⣷⡄⠀⠀" << std::endl;
    std::cout << "⢀⡎⣿⣿⣿⣿⣿⡀⠀⠀⠀⠀⠀⠀⢀⣴⣿⣿⣷⣦⣀⠀⠀⢀⣀ ⣿⣿⡄⠀" << std::endl;
    std::cout << "⡸⢸⣿⣿⣿⣿⣿⠗⠒⠒⠤⠤⠤⣴⣿⣿⣿⣿⣿⣿⣿⣿⠉⠁⠀ ⠈⢻⣷⠀" << std::endl;
    std::cout << "⡇⣸⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠘⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀ ⠀⢻⡆" << std::endl;
    std::cout << "⢠⠋⠙⠻⢿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠹⣿⣿⣿⣿⣿⣿⠁⠀⠀⠀⠀⠀ ⢸⡇" << std::endl;
    std::cout << "⣾⠀⠀⠀⠈⣆⠀⠀⠀⠀⠀⠀⠀⠀⢠⠋⠉⠉⠉⠉⠙⢆⠀⠀⠀⠀⠀ ⡆⡇" << std::endl;
    std::cout << "⢻⠀⠀⠀⠀⠘⣆⠀⠀⠀⠀⠀⠀⡰⠃⠀⠀⠀⠀⠀⠀⠈⢧⠀⠀⣀⡸⢰⠁" << std::endl;
    std::cout << "⠈⣆⠀⠀⠀⠀⢸⣶⣦⣤⣤⣤⡼⠁⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣇⠎⠀" << std::endl;
    std::cout << "⠀⠘⢆⡀⠀⠀⣼⣿⣿⣿⣿⣿⣿⣄⠀⠀⠀⠀⠀⠀⠀⣠⣿⣿⣿⣿⠏⠀⠀" << std::endl;
    std::cout << "⠀⠀⠈⠫⡉⠒⢿⣿⣿⣿⣿⣿⣿⣿⣆⣀⣀⣀⡠⠤⢴⣿⣿⣿⡿⠁⠀⠀⠀" << std::endl;
    std::cout << "⠀⠀⠀⠀⠈⠳⢄⡈⠛⠿⣿⣿⠿⠋⠁⠀⠀⠀⠀⢀⠈⣻⠿⠋⠀⠀⠀⠀⠀" << std::endl;
    std::cout << "⠀⠀⠀⠀⠀⠀⠀⠈⠑⠢⠤⣳⣀⣀⣀⣒⠤⠤⠔⠚⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
}


void Mundial::ListarPartidos(void){
    // DEBUG 
    //std::cout << "PG" << std::endl;

    this->partidos->IniciarIterador();
    std::tuple <int,int> resultado;
    while (this->partidos->MostrarIterador() != nullptr){
        /*
        std::cout <<  
        "Eq1: " << this->partidos->MostrarIterador()->MostrarContenido()->MostrarEquipos(true)->MostrarNombre() <<
        "Eq2: " << this->partidos->MostrarIterador()->MostrarContenido()->MostrarEquipos(false)->MostrarNombre() <<
        std::endl;

        if ( this->partidos->MostrarIterador()->MostrarContenido()->MostrarGanador() == nullptr)
            std::cout << "EMPATE" << std::endl;
        else
            std::cout << "GANO: " << this->partidos->MostrarIterador()->MostrarContenido()->MostrarGanador()->MostrarNombre() << std::endl;
        this->partidos->AvanzarIterador(1);
        */
        std::cout << this->partidos->MostrarIterador()->MostrarContenido()->MostrarEquipos(true)->MostrarNombre() << " vs " << 
        this->partidos->MostrarIterador()->MostrarContenido()->MostrarEquipos(false)->MostrarNombre() << " " << 
        this->partidos->MostrarIterador()->MostrarContenido()->MostrarGoles(true) << " a " << 
        this->partidos->MostrarIterador()->MostrarContenido()->MostrarGoles(false) << std::endl;
        this->partidos->AvanzarIterador(1);
    }
}

/*
void Mundial::ListarCantFasesPorEquipo(void){
    // DEBUG 
    //std::cout << "PG" << std::endl;

    this->equipos->IniciarIterador();
    while (this->equipos->MostrarIterador() != nullptr){
        std::cout << "FASE FINAL: " << this->equipos->MostrarIterador()->MostrarContenido().MostrarFaseFinal() <<
        " EQUIPO: " << this->equipos->MostrarIterador()->MostrarContenido().MostrarNombre() << std::endl;

        this->equipos->AvanzarIterador(1);
    }
}
*/




/*
tuple <string, char> Mundial::ValidarEquipo(string linea){
    int equipo_valido = 0;
    int largo = int(linea.size());
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
