#include <gym.h>
Asistencia* resizeClientes(Asistencia *AsistenciaClientes, u_int CantAsistencias, u_int nuevoTam, eAsistencia &eAsist){

    Asistencia* aux = new Asistencia[nuevoTam];

    u_int longitud = (CantAsistencias <  nuevoTam) ? CantAsistencias : nuevoTam;

    if(aux != nullptr) {

        for(u_int i = 0; i < longitud; i++)
            aux[i] = AsistenciaClientes[i];

        delete[] AsistenciaClientes;
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
            aux[i] = AsistenciaClientes->CursosInsciptos[i];

        delete[] AsistenciaClientes->CursosInsciptos;
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
    if(CantAsistencias == 0){

        AsistenciaClientes = resizeClientes(AsistenciaClientes, CantAsistencias, CantAsistencias+1, eAsist);

        if(eAsist == ExitoAsistencias){
            AsistenciaClientes[CantAsistencias].idCliente = idCliente;
            AsistenciaClientes[CantAsistencias].cantInscripcion = 1;
            AsistenciaClientes[CantAsistencias].CursosInsciptos->idClase = idClase;
            AsistenciaClientes[CantAsistencias].CursosInsciptos->fechaInscripcion = time(0);
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
                    AsistenciaClientes[CantAsistencias].cantInscripcion = 1;
                    AsistenciaClientes[CantAsistencias].CursosInsciptos->idClase = idClase;
                    AsistenciaClientes[CantAsistencias].CursosInsciptos->fechaInscripcion = time(0);
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
            aux->CursosInsciptos = resizeInscripcion(aux, aux->cantInscripcion, aux->cantInscripcion+1, eAsist2);
            if(eAsist2 == eAsistencia :: ExitoAsistencias){
                aux->CursosInsciptos[(aux->cantInscripcion)-1].idClase = idClase;
                aux->CursosInsciptos[(aux->cantInscripcion)-1].fechaInscripcion = time(0);
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
        if (AsistenciaCliente.CursosInsciptos->idClase == idClase ){
            return eClase :: ErrClaseRepetida;
        }
        if ( AsistenciaCliente.cantInscripcion == cont)
            break;
        cont++;
    }
    return eClase :: ExitoClase;
}

eClase CompararClaseInscripciones(ClasesGym clase, Asistencia AsistenciaCliente, ClasesGym *Clases, u_int cantclases){

    u_int i = 0;
    ClasesGym clase2;

    while(i<AsistenciaCliente.cantInscripcion) {
        if (AsistenciaCliente.CursosInsciptos[i].idClase == clase.idClase){
            return eClase :: ErrClaseRepetida;
        }
        i++;
    }

    while(i<AsistenciaCliente.cantInscripcion) {
        BuscarIdClase(Clases, AsistenciaCliente.CursosInsciptos[i].idClase, cantclases, clase2);
        if((clase.horario-clase2.horario)<1 && (clase.horario-clase2.horario)>-1)
            return eClase :: ErrSuperposicionDeHorarios;
        i++;
    }

    return eClase :: ExitoClase;
}


eCliente FiltroDeCliente(ClientesGYM* Clientes, u_int idCliente)
{
    ClientesGYM cliente;
    int CantClientes = 0, error;


    error = BuscarIdCliente(Clientes, idCliente, CantClientes, cliente);
    if(error == 1){
        for(int i = 0; i<30; i++)
        {
            if(!((cliente.nombre[i] >= 65 && cliente.nombre[i] <= 90) || (cliente.nombre[i] >= 97 && cliente.nombre[i] <= 127))) //|| (cliente.nombre[i] >= 160 && cliente.nombre[i] <= 165) || (cliente.nombre[i] == 130)))
                return eCliente::ErrNombre; // cliente null pone todo en 0, borra todo
        }

        for(int i = 0; i<30; i++)
        {
            if(!((cliente.apellido[i] >= 65 && cliente.apellido[i] <= 90) || (cliente.apellido[i] >= 97 && cliente.apellido[i] <= 127))) //|| (cliente.nombre[i] >= 160 && cliente.nombre[i] <= 165) || (cliente.nombre[i] == 130)))
                return eCliente::ErrApellido;
        }

        for(int i = 0; i<13; i++)
        {
            if(!(cliente.telefono[i] >= 48 && cliente.telefono[i] <= 57) || (cliente.telefono[i] == 45))
                return eCliente::ErrTelefono;
        }

        if(cliente.estado < 0)
            return eCliente::ErrEstado;

        int dia, mes, año, edad;
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

        edad = fechanacimiento.tm_year - timeinfo->tm_year;

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

