#include <gym.h>

eCliente BuscarIdCliente(ClientesGYM *Clientes, u_int idCliente, int CantClientes, ClientesGYM &cliente)
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

eClase BuscarIdClase(ClasesGym *Clases, u_int idClase, int cantClases, ClasesGym &clase)
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


eCliente FiltroDeCliente(ClientesGYM* Clientes, int idCliente)
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

eClase FiltroDeClase(ClasesGym *Clases, int idCliente, int idClase, Asistencia *AsistenciaCliente, int cantClases)
{
    ClasesGym clase;
    int error;

    error = BuscarIdClase(Clases, idClase, cantClases, clase);




}
