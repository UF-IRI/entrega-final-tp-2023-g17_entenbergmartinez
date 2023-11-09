#include <gym.h>
Asistencia* resizeClientes(Asistencia *AsistenciaClientes, u_int CantAsistencias, u_int nuevoTam, eAsistencia &eAsist){

    Asistencia* aux = new Asistencia[nuevoTam];

    u_int longitud = (CantAsistencias <  nuevoTam) ? CantAsistencias : nuevoTam;

    if(aux != nullptr) {

        for(u_int i = 0; i < longitud; i++)
            aux[i] = AsistenciaClientes[i];


        eAsist = ExitoAsistencias;
        return aux;
    }

    eAsist = ErrEspacio;
    return nullptr;
}

Inscripcion* resizeInscripcion(Asistencia* AsistenciaClientes, u_int cantinscripciones, u_int nuevoTam, eAsistencia &eAsist2){

    Inscripcion* aux = new Inscripcion[nuevoTam];

    u_int longitud = (cantinscripciones <  nuevoTam) ? cantinscripciones : nuevoTam;

    if(aux != nullptr) {

        for(u_int i = 0; i < longitud; i++)
            aux[i] = AsistenciaClientes->CursosInscriptos[i];


        eAsist2 = ExitoAsistencias;
        return aux;
    }

    eAsist2 = ErrEspacio;
    return nullptr;
}

eCliente BuscarIdCliente(ClientesGYM *Clientes, u_int idCliente, u_int CantClientes, ClientesGYM &cliente)
{
    ClientesGYM *aux = Clientes, *ultimo = (Clientes) + CantClientes - 1;
    while(true) {
        if (aux->idCliente == idCliente ){
            cliente = *aux;
            return eCliente :: ExitoCliente;
        }
        if (aux == ultimo)
            break;
        aux++;
    }
    return eCliente :: ErrIdClienteinx;
}

eClase BuscarIdClase(ClasesGym *Clases, u_int idClase, u_int cantClases, ClasesGym &clase)
{
    ClasesGym *aux = Clases, *ultimo = (Clases) + cantClases - 1;
    while(true) {
        if (aux->idClase == idClase ){
            clase = *aux;
            return eClase :: ExitoClase;
        }
        if (aux == ultimo)
            break;
        aux++;
    }
    return eClase :: ErrIdClaseinx;
}

eClase BuscarIdClase(ClasesGym *Clases, u_int idClase, u_int cantClases)
{
    ClasesGym *aux = Clases, *ultimo = (Clases) + cantClases - 1;
    while(true) {
        if (aux->idClase == idClase ){
            aux->cuposActuales++;
            return eClase :: ExitoClase;
        }
        if (aux == ultimo)
            break;
        aux++;
    }
    return eClase :: ErrIdClaseinx;
}

eAsistencia BuscarAsistenicaCliente(u_int idClase, u_int idCliente,  Asistencia *&AsistenciaClientes, Asistencia &AsistenciaCliente, u_int &CantAsistencias)
{
    eAsistencia eAsist;
    eAsistencia eAsist2;
    if(CantAsistencias == 0){
        AsistenciaClientes = resizeClientes(AsistenciaClientes, CantAsistencias, CantAsistencias+1, eAsist);

        if(eAsist == ExitoAsistencias){
            AsistenciaClientes[CantAsistencias].idCliente = idCliente;
            AsistenciaClientes[CantAsistencias].cantInscriptos = 1;
            Asistencia *aux = AsistenciaClientes;
            AsistenciaClientes[CantAsistencias].CursosInscriptos = resizeInscripcion(aux, 0, 1, eAsist2);
            AsistenciaClientes[CantAsistencias].CursosInscriptos->idClase = idClase;
            AsistenciaClientes[CantAsistencias].CursosInscriptos->fechaInscripcion = time(0);
            AsistenciaCliente = AsistenciaClientes[CantAsistencias];
            CantAsistencias++;
            return eAsistencia :: ExitoCrearAsistencias;
        }
        else
            return eAsistencia :: ErrEspacio;
    }

    else{
        Asistencia *aux = AsistenciaClientes, *ultimo = (AsistenciaClientes) + CantAsistencias - 1;

        while(true) {

            if (aux->idCliente == idCliente ){
               AsistenciaCliente = *aux;
             return eAsistencia :: ExitoAsistencias;
            }

            if (aux == ultimo){
                AsistenciaClientes = resizeClientes(AsistenciaClientes, CantAsistencias, CantAsistencias+1, eAsist);

                if(eAsist == ExitoAsistencias){
                    AsistenciaClientes[CantAsistencias].idCliente = idCliente;
                    AsistenciaClientes[CantAsistencias].cantInscriptos = 1;
                    Asistencia *aux = AsistenciaClientes;
                    AsistenciaClientes[CantAsistencias].CursosInscriptos = resizeInscripcion(aux, 0, 1, eAsist2);
                    AsistenciaClientes[CantAsistencias].CursosInscriptos->idClase = idClase;
                    AsistenciaClientes[CantAsistencias].CursosInscriptos->fechaInscripcion = time(0);
                    AsistenciaCliente = AsistenciaClientes[CantAsistencias];
                    CantAsistencias++;
                    return eAsistencia :: ExitoCrearAsistencias;
                }

                else
                    return eAsistencia :: ErrEspacio;
            }

            aux++;
        }
    }

    return eAsistencia :: ExitoAsistencias ;
}

eAsistencia BuscarAsistenicaCliente(u_int idClase, u_int idCliente,  Asistencia *&AsistenciaClientes)
{
    Asistencia *aux = AsistenciaClientes;
    eAsistencia eAsist2;

    while(true) {

        if (aux->idCliente == idCliente){
            aux->CursosInscriptos = resizeInscripcion(aux, aux->cantInscriptos, aux->cantInscriptos+1, eAsist2);
            if(eAsist2 == eAsistencia :: ExitoAsistencias){
                aux->CursosInscriptos[(aux->cantInscriptos)-1].idClase = idClase;
                aux->CursosInscriptos[(aux->cantInscriptos)-1].fechaInscripcion = time(0);
                return eAsistencia :: ExitoAsistencias;
            }
            else
                return eAsistencia :: ErrEspacio;
        }

        aux++;
    }
}

eClase BuscarIdClaseEnInscripciones(Asistencia AsistenciaCliente, u_int idClase){

    u_int cont = 0;

    while(true) {
        if (AsistenciaCliente.CursosInscriptos->idClase == idClase ){
            return eClase :: ErrClaseRepetida;
        }
        if ( AsistenciaCliente.cantInscriptos == cont)
            break;
        cont++;
    }
    return eClase :: ExitoClase;
}

eClase CompararClaseInscripciones(ClasesGym clase, Asistencia AsistenciaCliente, ClasesGym *Clases, u_int cantclases){

    u_int i = 0;
    ClasesGym clase2;

    while(i<AsistenciaCliente.cantInscriptos) {
        if (AsistenciaCliente.CursosInscriptos[i].idClase == clase.idClase){
            return eClase :: ErrClaseRepetida;
        }
        i++;
    }

    while(i<AsistenciaCliente.cantInscriptos) {
        BuscarIdClase(Clases, AsistenciaCliente.CursosInscriptos[i].idClase, cantclases, clase2);
        if(((clase.horario-clase2.horario)<1 && (clase.horario-clase2.horario)>-1) || ((clase.nombre == "Musculacion" && clase2.nombre == "Musculacion") && ((clase.horario-clase2.horario) < 0.7 && (clase.horario-clase2.horario) > -0.7)))
            return eClase :: ErrSuperposicionDeHorarios;
        i++;
    }

    return eClase :: ExitoClase;
}

eCliente FiltroDeCliente(ClientesGYM *Clientes, u_int idCliente, u_int cantClientes)
{
    ClientesGYM cliente;
    int error;


    error = BuscarIdCliente(Clientes, idCliente, cantClientes, cliente);
    if(error == 1){
        for(unsigned long long i = 0; i<cliente.nombre.length(); i++)
        {
            if(!(((cliente.nombre[i] >= 65 && cliente.nombre[i] <= 90) || (cliente.nombre[i] >= 97 && cliente.nombre[i] <= 127)))) //|| (cliente.nombre[i] >= 160 && cliente.nombre[i] <= 165) || (cliente.nombre[i] == 130)))
                return eCliente::ErrNombre; // cliente null pone todo en 0, borra todo
        }

        for(unsigned long long i = 0; i<cliente.apellido.length(); i++)
        {
            if(!(((cliente.apellido[i] >= 65 && cliente.apellido[i] <= 90) || (cliente.apellido[i] >= 97 && cliente.apellido[i] <= 127)))) //|| (cliente.nombre[i] >= 160 && cliente.nombre[i] <= 165) || (cliente.nombre[i] == 130)))
                return eCliente::ErrApellido;
        }

        for(unsigned long long i = 0; i<cliente.telefono.length(); i++)
        {
            if(!((cliente.telefono[i] >= 48 && cliente.telefono[i] <= 57) || (cliente.telefono[i] == 45)))
                return eCliente::ErrTelefono;
        }

        if(cliente.estado < 0)
            return eCliente::ErrEstado;

        int dia, mes, año, edad = 0;
        char delimiter = '-';
        string auxdia, auxmes, auxaño;
        stringstream ss;
        ss << cliente.fechanacimiento;
        getline(ss,auxdia,delimiter);
        dia = stoi(auxdia);
        getline(ss,auxmes,delimiter);
        mes = stoi(auxmes);
        getline(ss,auxaño,delimiter);
        año = stoi(auxaño);

        time_t rawtime;
        tm fechanacimiento;
        tm * timeinfo;

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        fechanacimiento.tm_mday = dia;
        fechanacimiento.tm_mon = (mes-1);
        fechanacimiento.tm_year = (año-1900);

        edad = timeinfo->tm_year - fechanacimiento.tm_year;

        if(fechanacimiento.tm_mon < timeinfo->tm_mon || (fechanacimiento.tm_mon == timeinfo->tm_mon && fechanacimiento.tm_mday < timeinfo->tm_mday))
            edad--;

        if(edad<18)
            return eCliente :: ErrMuyJoven;
        else if(edad>100)
            return eCliente :: ErrMuyViejo;

        return eCliente ::ExitoCliente;
    }
    else
        return eCliente :: ErrIdClienteinx;
}

eDia FiltroFecha() {

    time_t rawtime;
    tm * timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    if(timeinfo->tm_wday == 6)
        return eDia :: ErrDia;

    return eDia :: ExitoDia;
}

eClase FiltroDeClase(ClasesGym *Clases, u_int idCliente, u_int idClase, Asistencia *&AsistenciaClientes, u_int cantclases, u_int &CantAsistencias)
{
    ClasesGym clase;
    eClase error1, error3;
    eAsistencia error2, error4;
    Asistencia AsistenciaCliente;

    error1 = BuscarIdClase(Clases, idClase, cantclases, clase);

    if(error1 == eClase ::ExitoClase){

        if(clase.cuposActuales == clase.cuposMax)
            return eClase :: ErrCupos;

        error2 = BuscarAsistenicaCliente(idClase, idCliente, AsistenciaClientes, AsistenciaCliente, CantAsistencias);

        if(error2 == eAsistencia :: ExitoAsistencias)
        {

            if(BuscarIdClaseEnInscripciones(AsistenciaCliente, idClase) == eClase :: ErrClaseRepetida)
                return eClase :: ErrClaseRepetida;

            else {
                error3 = CompararClaseInscripciones(clase, AsistenciaCliente, Clases, cantclases);
                if(error3 == eClase :: ExitoClase){

                    BuscarIdClase( Clases, idClase, cantclases);

                    error4 = BuscarAsistenicaCliente(idClase, idCliente, AsistenciaClientes);

                    if(error4 == eAsistencia :: ExitoAsistencias)
                        return eClase :: ExitoClase;

                    else
                        return eClase :: ErrEspacioCrearAsistencia;
                }

                else
                    return error3;
            }
        }

        else if(error2 == eAsistencia :: ExitoCrearAsistencias){
            BuscarIdClase( Clases, idClase, cantclases);
            return eClase :: ExitoClase;
        }

        else
            return eClase :: ErrEspacioCrearAsistencia;
    }
    else
        return error1;
}


