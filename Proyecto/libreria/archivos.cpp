#include <archivos.h>

//agregar longitud por derecha
eArchivos leerArchivoClientes(string archivo, ClientesGYM *&Clientes, int &cantClientes){

    int i = 0;

    ifstream infile(archivo);

    if (!infile.is_open()) {

        return eArchivos :: ErrorApertura;
    }

    string header;
    getline(infile, header);

    string line;
    char delimiter = ',';

    while(getline(infile, line))
        cantClientes++;

    infile.seekg(ios::beg);

    Clientes = new ClientesGYM[cantClientes];

    getline(infile, header);
    string auxidCliente, auxnombre, auxapellido, auxemail, auxtelefono, auxfechanacimiento, auxestado;
    stringstream ss;
    while(getline(infile, line)) {
        ss<<line;
        getline(ss,auxidCliente,delimiter);
        (Clientes[i]).idCliente = stoi(auxidCliente);

        getline(ss,auxnombre,delimiter);
        (Clientes[i]).nombre = auxnombre;

        getline(ss,auxapellido,delimiter);
        (Clientes[i]).apellido = auxapellido;

        getline(ss,auxemail,delimiter);
        (Clientes[i]).email = auxemail;

        getline(ss,auxtelefono,delimiter);
        (Clientes[i]).telefono = auxtelefono;

        getline(ss,auxfechanacimiento,delimiter);
        (Clientes[i]).fechanacimiento = auxfechanacimiento;

        getline(ss,auxestado,delimiter);
        (Clientes[i]).estado = stoi(auxestado);

        i++;
    }

    infile.close();
    return eArchivos :: ExitoOperacion;
}

eArchivos leerArchivoClases(string archivo, ClasesGym *&Clases, int &cantClases){

    int i = 0;

    ifstream infile(archivo);

    if (!infile.is_open()) {

        return eArchivos :: ErrorApertura;
    }

    string header;
    getline(infile, header);

    string line;
    char delimiter = ',';

    while(getline(infile, line))
        cantClases++;

    infile.seekg(ios::beg);

    Clases = new ClasesGym[cantClases];

    getline(infile, header);
    string auxidClase, auxnombre, auxhorario;
    stringstream ss;
    while(getline(infile, line)) {
        ss<<line;
        getline(ss,auxidClase,delimiter);
        (Clases[i]).idClase = stoi(auxidClase);

        getline(ss,auxnombre,delimiter);
        (Clases[i]).nombre = auxnombre;

        getline(ss,auxhorario,delimiter);
        (Clases[i]).horario = stof(auxhorario);

        if(stoi(auxidClase)>0 && stoi(auxidClase)<6)
            (Clases[i]).cuposMax=45;
        else if(stoi(auxidClase)>5 && stoi(auxidClase)<12)
            (Clases[i]).cuposMax=25;
        else if(stoi(auxidClase)>11 && stoi(auxidClase)<18)
            (Clases[i]).cuposMax=15;
        else if(stoi(auxidClase)>17 && stoi(auxidClase)<24)
            (Clases[i]).cuposMax=40;
        else if(stoi(auxidClase)>23 && stoi(auxidClase)<30)
            (Clases[i]).cuposMax=50;
        else if(stoi(auxidClase)>29 && stoi(auxidClase)<34)
            (Clases[i]).cuposMax=30;
        else if(stoi(auxidClase)>33 && stoi(auxidClase)<61)
            (Clases[i]).cuposMax=30;

        i++;
    }

    infile.close();

    return eArchivos::ExitoOperacion;
}
