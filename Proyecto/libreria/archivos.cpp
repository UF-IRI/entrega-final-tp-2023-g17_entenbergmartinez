#include <archivos.h>

eArchivos leerArchivoClientes(ifstream *archivo, ClientesGYM *Clientes){
    u_int auxidCliente;
    string auxNombre, auxApellido, auxEmail, auxTelefono;
    string auxFechanacimiento;
    int auxEstado;
    char coma;
    int i=0;

    if(!archivo->is_open())
        return eArchivos::ErrorApertura;

    while(*archivo>>auxidCliente>>coma>>auxNombre>>coma>>auxApellido>>coma>>auxEmail>>coma>>auxTelefono>>auxFechanacimiento>>coma>>auxEstado){
        (Clientes+i)->idCliente=auxidCliente;
        (Clientes+i)->nombre=auxNombre;
        (Clientes+i)->apellido=auxApellido;
        (Clientes+i)->email=auxEmail;
        (Clientes+i)->telefono=auxTelefono;
        (Clientes+i)->fechanacimiento=auxFechanacimiento;
        (Clientes+i)->estado=auxEstado;


        i++;
    }

    return eArchivos::ExitoOperacion;
}

eArchivos leerArchivoClases(ifstream *archivo, ClasesGym *Clases){
    u_int auxidClase;
    string auxNombre;
    int auxHorario;
    char coma;
    int i=0;

    if(!archivo->is_open())
        return eArchivos::ErrorApertura;

    while(*archivo>>auxidClase>>coma>>auxNombre>>coma>>auxHorario){
        (Clases+i)->idClase=auxidClase;
        (Clases+i)->nombre=auxNombre;
        (Clases+i)->horario=auxHorario;
        (Clases+i)->cuposActuales= 0;

        if(auxidClase>0 && auxidClase<6)
        (Clases+i)->cuposMax=45;
        else if(auxidClase>5 && auxidClase<12)
        (Clases+i)->cuposMax=25;
        else if(auxidClase>11 && auxidClase<18)
        (Clases+i)->cuposMax=15;
        else if(auxidClase>17 && auxidClase<24)
        (Clases+i)->cuposMax=40;
        else if(auxidClase>23 && auxidClase<30)
        (Clases+i)->cuposMax=50;
        else if(auxidClase>29 && auxidClase<34)
        (Clases+i)->cuposMax=30;
        else if(auxidClase>33 && auxidClase<61)
        (Clases+i)->cuposMax=30;
        i++;
    }

    return eArchivos::ExitoOperacion;
}
