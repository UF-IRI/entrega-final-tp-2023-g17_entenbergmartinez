#include <encabezados.h>
#include <gym.h>
#include <archivos.h>
#include <archivos.cpp>
#include <gym.cpp>


int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    //Asistencia *Asistencias;
    //u_int cantAsist;
    u_int cantclases = 0, cantClientes = 0, reservas = 1, cantAsistencias = 0;
    ClasesGym *Clases;
    ClientesGYM *Clientes;
    Asistencia *AsistenciaClientes;
    eCliente errCliente;
    eClase errClase;
    eArchivos errArchivoclase, errArchivocliente;

    time_t t = time(0);
    tm* fecha_hora = localtime(&t);
    fecha_hora->tm_hour = 0;
    fecha_hora->tm_min = 0;
    fecha_hora->tm_sec = 0;

    string aux;
    time_t timestamp = mktime(fecha_hora);
    aux = to_string(timestamp);

    /*ifstream archivobinlee("../asistencias_1697673600000.dat", ios::binary);
    LeerArchivoBinario(archivobinlee, Asistencias, cantAsist);
    archivobinlee.close();
    if(LeerArchivoBinario(archivobinlee, Asistencias, cantAsist) == eArchivos :: ErrorApertura){
        cout<<"no se pudo abrir el archivo de asistencias";
        cout<<endl;
        return eArchivos :: ErrorApertura;
    }*/

    ifstream infileprueba("iriClasesGYM.csv");
    infileprueba.close();
    ifstream infileClases("../iriClasesGYM.csv");
    errArchivoclase = leerArchivoClases(infileClases, Clases, cantclases);
    infileClases.close();
    if(errArchivoclase == eArchivos :: ErrorApertura){
        cout<<"no se pudo abrir el archivo de clases";
        cout<<endl;
        return eArchivos :: ErrorApertura;
    }

    ifstream infileClientes("../iriClientesGYM.csv");
    errArchivocliente = leerArchivoClientes(infileClientes, Clientes, cantClientes);
    infileClientes.close();
    if(errArchivocliente == eArchivos :: ErrorApertura){
        cout<<"no se pudo abrir el archivo de clientes";
        cout<<endl;
        delete [] Clases;
        return eArchivos :: ErrorApertura;
    }

    for(u_int i = 0; i < reservas; i++){
        u_int idCliente = rand() % cantClientes, idClase = rand() % cantclases;

        eDia errFecha = FiltroFecha();
        if(errFecha == eDia :: ErrDia){
            cout<<"Lo lamento su reserva no fue realizada, no se pueden reservar los dias sabados";
            cout<<endl;
            return eDia :: ErrDia;
        }

        errCliente = FiltroDeCliente(Clientes, idCliente, cantClientes);
        if(errCliente == eCliente :: ErrNombre){
            cout<<"Lo lamento su reserva no fue realizada, el Nombre esta mal escrito";
            cout<<endl;
            return eCliente::ErrNombre;
        }
        else if(errCliente == eCliente :: ErrApellido){
            cout<<"Lo lamento su reserva no fue realizada, el Apellido esta mal escrito";
            cout<<endl;
            return eCliente :: ErrApellido;
        }
        else if(errCliente == eCliente :: ErrTelefono){
            cout<<"Lo lamento su reserva no fue realizada, el Telefono esta mal escrito";
            cout<<endl;
            return eCliente :: ErrTelefono;
        }
        else if(errCliente == eCliente :: ErrEstado){
            cout<<"Lo lamento su reserva no fue realizada, la cuota no esta al dia";
            cout<<endl;
            return eCliente::ErrNombre;
        }
        else if(errCliente == eCliente :: ErrMuyJoven){
            cout<<"Lo lamento su reserva no fue realizada, no llega a la edad permitida";
            cout<<endl;
            return eCliente :: ErrMuyJoven;
        }
        else if(errCliente == eCliente :: ErrMuyViejo){
            cout<<"Lo lamento su reserva no fue realizada, exede la edad permitida";
            cout<<endl;
            return eCliente :: ErrMuyViejo;
        }
        else if(errCliente == eCliente :: ErrIdClienteinx){
            cout<<"Lo lamento su reserva no fue realizada, su id no esta registrada";
            cout<<endl;
            return eCliente :: ErrIdClienteinx;
        }

        errClase = FiltroDeClase(Clases, idCliente, idClase, AsistenciaClientes, cantclases, cantAsistencias);
        if(errClase == eClase :: ErrCupos){
            cout<<"Lo lamento su reserva no fue realizada, no hay cupos suficientes";
            cout<<endl;
            return eClase :: ErrCupos;
        }
        else if(errClase == eClase :: ErrClaseRepetida){
            cout<<"Lo lamento su reserva no fue realizada, ya reservo esta clase";
            cout<<endl;
            return eClase :: ErrClaseRepetida;
        }
        else if(errClase == eClase :: ErrSuperposicionDeHorarios){
            cout<<"Lo lamento su reserva no fue realizada, ya tiene otra clase en ese horario";
            cout<<endl;
            return eClase :: ErrSuperposicionDeHorarios;
        }
        else if(errClase == eClase :: ErrEspacioCrearAsistencia){
            cout<<"Lo lamento su reserva no fue realizada, el espacio del programa fallo";
            cout<<endl;
            return eClase :: ErrEspacioCrearAsistencia;
        }
        else if(errClase == eClase :: ErrIdClaseinx){
            cout<<"Lo lamento su reserva no fue realizada, la id de clase que eligio no existe";
            cout<<endl;
            return eClase :: ErrIdClaseinx;
        }

    }

    ofstream archivobin("../asistencias_" + aux + ".dat", ios :: binary);
    eArchivos errArchivoBinario = EscribirArchivoBinario(archivobin, AsistenciaClientes, cantAsistencias);
    archivobin.close();
    if(errArchivoBinario == eArchivos :: ErrorApertura){
        cout<<"no se pudo abrir el archivo de escritura de asistencias";
        cout<<endl;
        return eArchivos :: ErrorApertura;
    }

    delete [] Clases;
    delete [] Clientes;

    return 0;
}
