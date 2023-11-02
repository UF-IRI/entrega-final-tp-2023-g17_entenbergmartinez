#include <gym.h>

eCliente BuscarIdCliente(ClientesGYM *Clientes, u_int idCliente, int CantClientes, ClientesGYM cliente)
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

eClase BuscarIdClase(ClasesGym *Clases, int idClase, int cantClases, ClasesGym clase);
{
    ClasesGym *aux = Clases, *ultimo = (Clases) + CantClases - 1;
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

    BuscarIdCliente(*Clientes, idCliente, CantClientes, cliente);

    for(int i = 0; i<30; i++)
    {
        if(!((cliente.nombre[i] >= 65 && cliente.nombre[i] <= 90) || (cliente.nombre[i] >= 97 && cliente.nombre[i] <= 127) || (cliente.nombre[i] >= 160 && cliente.nombre[i] <= 165) || (cliente.nombre[i] == 130)))
            return eCliente::ErrNombre; // cliente null pone todo en 0, borra todo
    }

    for(int i = 0; i<30; i++)
    {
        if(!((cliente.apellido[i] >= 65 && cliente.apellido[i] <= 90) || (cliente.apellido[i] >= 97 && cliente.apellido[i] <= 127) || (cliente.nombre[i] >= 160 && cliente.nombre[i] <= 165) || (cliente.nombre[i] == 130)))
            return eCliente::ErrApellido;
    }

    for(int i = 0; i<13; i++)
    {
        if(!(cliente.telefono[i] >= 48 && cliente.telefono[i] <= 57) || (cliente.telefono[i] == 45))
            return eCliente::ErrTelefono;
    }

    if(cliente.estado < 0)
        return eCliente::ErrEstado;


    //revisar
    string str = cliente.fechanacimiento;
    const char *c = str.c_str();
    time_t ts = 0;
    struct tm a_date;

    strptime(c, "%d-%m-%Y", &a_date);
    ts = mktime(&a_date);



}


eClase FiltroDeClase(ClasesGym *Clases, int idCliente, int idClase, Asistencia *AsistenciaCliente)
{
    ClasesGym clase;

    BuscarIdClase(*Clases, idClase, cantClases, clase);


}
