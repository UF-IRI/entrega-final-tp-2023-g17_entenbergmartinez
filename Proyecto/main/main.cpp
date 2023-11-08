#include <encabezados.h>
#include <gym.h>
#include <archivos.h>

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    Asistencia *Asistencias;
    u_int cantAsist, cantClases, cantClientes, reservas = 500, cantAsistencias;
    ClasesGym *Clases;
    ClientesGYM *Clientes;
    Asistencia *AsistenciaClientes;
    eCliente errCliente;
    eClase errClase;

    time_t t = time(0);
    tm* fecha_hora = localtime(&t);
    fecha_hora->tm_hour = 0;
    fecha_hora->tm_min = 0;
    fecha_hora->tm_sec = 0;

    char buffer[80];  // Suficiente para almacenar la fecha y hora formateada
    // Utiliza strftime para dar formato a la fecha y hora en el búfer
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", fecha_hora);
    // Convierte el búfer en una cadena de C++
    string aux(buffer);

    ifstream archivobinlee("../asistencias_1697673600000.dat", ios::binary);
    LeerArchivoBinario(archivobinlee, Asistencias, cantAsist);
    archivobinlee.close();
    if(LeerArchivoBinario(archivobinlee, Asistencias, cantAsist) == eArchivos :: ErrorApertura){
        cout<<"no se pudo abrir el archivo de asistencias";
        return eArchivos :: ErrorApertura;
    }

    ifstream infileClases("../iriClasesGYM.csv");
    leerArchivoClases(infileClases, Clases, cantClases);
    infileClases.close();
    if(leerArchivoClases(infileClases, Clases, cantClases) == eArchivos :: ErrorApertura){
        cout<<"no se pudo abrir el archivo de clases";
        return eArchivos :: ErrorApertura;
    }

    ifstream infileClientes("../iriClientesGYM.csv");
    leerArchivoClientes(infileClientes, Clientes, cantClientes);
    infileClientes.close();
    if(leerArchivoClientes(infileClientes, Clientes, cantClientes) == eArchivos :: ErrorApertura){
        cout<<"no se pudo abrir el archivo de clientes";
        return eArchivos :: ErrorApertura;
    }

    for(u_int i = 0; i < reservas; i++){
        u_int idCliente = rand() % cantClientes, idClase = rand() % cantClases;

        FiltroFecha();
        if(FiltroFecha() == eDia :: ErrDia){
            cout<<"Lo lamento su reserva no fue realizada, no se pueden reservar los dias sabados";
                return eDia :: ErrDia;
        }

        errCliente = FiltroDeCliente(Clientes, idCliente, cantClientes);
        if(errCliente == eCliente :: ErrNombre){
            cout<<"Lo lamento su reserva no fue realizada, el Nombre esta mal escrito";
            return eCliente::ErrNombre;
        }
        else if(errCliente == eCliente :: ErrApellido){
            cout<<"Lo lamento su reserva no fue realizada, el Apellido esta mal escrito";
            return eCliente :: ErrApellido;
        }
        else if(errCliente == eCliente :: ErrTelefono){
            cout<<"Lo lamento su reserva no fue realizada, el Telefono esta mal escrito";
            return eCliente :: ErrTelefono;
        }
        else if(errCliente == eCliente :: ErrEstado){
            cout<<"Lo lamento su reserva no fue realizada, la cuota no esta al dia";
            return eCliente::ErrNombre;
        }
        else if(errCliente == eCliente :: ErrMuyJoven){
            cout<<"Lo lamento su reserva no fue realizada, no llega a la edad permitida";
            return eCliente :: ErrMuyJoven;
        }
        else if(errCliente == eCliente :: ErrMuyViejo){
            cout<<"Lo lamento su reserva no fue realizada, exede la edad permitida";
            return eCliente :: ErrMuyViejo;
        }
        else if(errCliente == eCliente :: ErrIdClienteinx){
            cout<<"Lo lamento su reserva no fue realizada, su id no esta registrada";
            return eCliente :: ErrIdClienteinx;
        }

        errClase = FiltroDeClase(Clases, idCliente, idClase, AsistenciaClientes, cantClases, cantAsistencias);
        if(errClase == eClase :: ErrCupos){
            cout<<"Lo lamento su reserva no fue realizada, no hay cupos suficientes";
            return eClase :: ErrCupos;
        }
        else if(errClase == eClase :: ErrClaseRepetida){
            cout<<"Lo lamento su reserva no fue realizada, ya reservo esta clase";
            return eClase :: ErrClaseRepetida;
        }
        else if(errClase == eClase :: ErrSuperposicionDeHorarios){
            cout<<"Lo lamento su reserva no fue realizada, ya tiene otra clase en ese horario";
            return eClase :: ErrSuperposicionDeHorarios;
        }
        else if(errClase == eClase :: ErrEspacioCrearAsistencia){
            cout<<"Lo lamento su reserva no fue realizada, el espacio del programa fallo";
            return eClase :: ErrEspacioCrearAsistencia;
        }
        else if(errClase == eClase :: ErrIdClaseinx){
            cout<<"Lo lamento su reserva no fue realizada, la id de clase que eligio no existe";
            return eClase :: ErrIdClaseinx;
        }

    }

    ofstream archivobin("../asistencias_" + aux + ".dat", ios :: binary);
    EscribirArchivoBinario(archivobin, AsistenciaClientes, cantAsistencias);
    archivobin.close();
    if(EscribirArchivoBinario(archivobin, AsistenciaClientes, cantAsistencias) == eArchivos :: ErrorApertura){
        cout<<"no se pudo abrir el archivo de escritura de asistencias";
        return eArchivos :: ErrorApertura;
    }

    return 0;
}
