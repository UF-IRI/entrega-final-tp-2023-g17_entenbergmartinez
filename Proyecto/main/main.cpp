#include <encabezados.h>
#include <gym.h>
#include <archivos.h>
#include <archivos.cpp>
#include <gym.cpp>


int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    //Asistencia *Asistencias;
    //u_int cantAsist;
    u_int cantclases = 0, cantClientes = 0, reservas = 5000, cantAsistencias = 0, cantAsist = 0, cantasist = 154, j = 0;
    ClasesGym *Clases;
    ClientesGYM *Clientes;
    Asistencia *AsistenciaClientes, *asistencias;
    eCliente errCliente;
    eClase errClase;
    eArchivos errArchivoclase, errArchivocliente, errBinario;

    time_t t = time(0);
    tm* fecha_hora = localtime(&t);
    fecha_hora->tm_hour = 0;
    fecha_hora->tm_min = 0;
    fecha_hora->tm_sec = 0;

    string aux;
    time_t timestamp = mktime(fecha_hora);
    aux = to_string(timestamp);

    ifstream infileClases("../iriClasesGYM.csv");
    errArchivoclase = leerArchivoClases(infileClases, Clases, cantclases);
    infileClases.close();
    if(errArchivoclase == eArchivos :: ErrorApertura){
        cout<<"no se pudo abrir el archivo de clases";
        cout<<endl;
        return eArchivos :: ErrorApertura;
    }

    ifstream archivobinlee("../asistencias_1697673600000.dat", ios::binary);

    archivobinlee.seekg(0, std::ios::end);
    std::streampos fileSize = archivobinlee.tellg();
    archivobinlee.seekg(0, std::ios::beg);
    cantAsist = static_cast<u_int>(fileSize / ((sizeof(Asistencia)) + sizeof(Inscripcion)))-1;


    asistencias = new Asistencia[cantasist];

    errBinario = LeerArchivoBinario(archivobinlee, asistencias);
    archivobinlee.close();
    if(errBinario == eArchivos :: ErrorApertura){
        cout<<"no se pudo abrir el archivo de asistencias";
        cout<<endl;
        delete []Clases;
        return eArchivos :: ErrorApertura;
    }

    /*ordenarclasesinscriptas(asistencias, cantasist);
    eliminarclaserepetida(asistencias, cantasist);
    ordenarlasclaseseliminadasalfinal(asistencias, cantasist);
    ordenarclasesinscriptas(asistencias, cantasist);
    CompararClaseInscripciones(asistencias, Clases, cantclases, cantasist);
    ordenarlasclaseseliminadasalfinal(asistencias, cantasist);*/

    ifstream infileClientes("../iriClientesGYM.csv");
    errArchivocliente = leerArchivoClientes(infileClientes, Clientes, cantClientes);
    infileClientes.close();
    if(errArchivocliente == eArchivos :: ErrorApertura){
        cout<<"no se pudo abrir el archivo de clientes";
        cout<<endl;
        delete []Clases;
        delete []asistencias;
        return eArchivos :: ErrorApertura;
    }

    while(j < reservas){
        for(u_int i = 0; i != 1; i++){
            u_int idCliente = rand() % cantClientes, idClase = rand() % cantclases;

            eDia errFecha = FiltroFecha();
            if(errFecha == eDia :: ErrDia){
                cout<<"Lo lamento la reserva del Cliente id: "<<idCliente<<" para la Clase id: "<<idClase<<" no fue realizada, no se pueden reservar los dias sabados";
                cout<<endl;
                break;
            }

            errCliente = FiltroDeCliente(Clientes, idCliente, cantClientes);
            if(errCliente == eCliente :: ErrNombre){
                cout<<"Lo lamento la reserva del Cliente id: "<<idCliente<<" para la Clase id: "<<idClase<<" no fue realizada, el Nombre esta mal escrito";
                cout<<endl;
                break;
            }
            else if(errCliente == eCliente :: ErrApellido){
                cout<<"Lo lamento la reserva del Cliente id: "<<idCliente<<" para la Clase id: "<<idClase<<" no fue realizada, el Apellido esta mal escrito";
                cout<<endl;
                break;
            }
            else if(errCliente == eCliente :: ErrTelefono){
                cout<<"Lo lamento la reserva del Cliente id: "<<idCliente<<" para la Clase id: "<<idClase<<" no fue realizada, el Telefono esta mal escrito";
                cout<<endl;
                break;
            }
            else if(errCliente == eCliente :: ErrEstado){
                cout<<"Lo lamento la reserva del Cliente id: "<<idCliente<<" para la Clase id: "<<idClase<<" no fue realizada, la cuota no esta al dia";
                cout<<endl;
                break;
            }
            else if(errCliente == eCliente :: ErrMuyJoven){
                cout<<"Lo lamento la reserva del Cliente id: "<<idCliente<<" para la Clase id: "<<idClase<<" no fue realizada, no llega a la edad permitida";
                cout<<endl;
                break;
            }
            else if(errCliente == eCliente :: ErrMuyViejo){
                cout<<"Lo lamento la reserva del Cliente id: "<<idCliente<<" para la Clase id: "<<idClase<<" no fue realizada, exede la edad permitida";
                cout<<endl;
                break;
            }
            else if(errCliente == eCliente :: ErrIdClienteinx){
                cout<<"Lo lamento la reserva del Cliente id: "<<idCliente<<" para la Clase id: "<<idClase<<" no fue realizada, su id no esta registrada";
                cout<<endl;
                break;
            }

            errClase = FiltroDeClase(Clases, idCliente, idClase, AsistenciaClientes, cantclases, cantAsistencias);
            if(errClase == eClase :: ErrCupos){
                cout<<"Lo lamento la reserva del Cliente id: "<<idCliente<<" para la Clase id: "<<idClase<<" no fue realizada, no hay cupos suficientes";
                cout<<endl;
                break;
            }
            else if(errClase == eClase :: ErrClaseRepetida){
                cout<<"Lo lamento la reserva del Cliente id: "<<idCliente<<" para la Clase id: "<<idClase<<" no fue realizada, ya reservo esta clase";
                cout<<endl;
                break;
            }
            else if(errClase == eClase :: ErrSuperposicionDeHorarios){
                cout<<"Lo lamento la reserva del Cliente id: "<<idCliente<<" para la Clase id: "<<idClase<<" no fue realizada, ya tiene otra clase en ese horario";
                cout<<endl;
                break;
            }
            else if(errClase == eClase :: ErrEspacioCrearAsistencia){
                cout<<"Lo lamento la reserva del Cliente id: "<<idCliente<<" para la Clase id: "<<idClase<<" no fue realizada, el espacio del programa fallo";
                cout<<endl;
                break;
            }
            else if(errClase == eClase :: ErrIdClaseinx){
                cout<<"Lo lamento la reserva del Cliente id: "<<idCliente<<" para la Clase id: "<<idClase<<" no fue realizada, la id de clase que eligio no existe";
                cout<<endl;
                break;
            }

            cout<<"La reserva del Cliente id: "<<idCliente<<" para la Clase id: "<<idClase<<" fue realizada con exito";
            cout<<endl;
        }


        j++;
    }
    ofstream archivobin("../asistencias_" + aux + ".dat", ios :: binary);
    eArchivos errArchivoBinario = EscribirArchivoBinario(archivobin, AsistenciaClientes, cantAsistencias);
    archivobin.close();
    if(errArchivoBinario == eArchivos :: ErrorApertura){
        cout<<"no se pudo abrir el archivo de escritura de asistencias";
        cout<<endl;
        return eArchivos :: ErrorApertura;
    }

    for(u_int i = 0; i < cantasist; i++){
        delete[]asistencias[i].CursosInscriptos;
    }
    delete [] Clases;
    delete [] Clientes;
    delete [] asistencias;
    delete [] AsistenciaClientes;

    return 0;
}
