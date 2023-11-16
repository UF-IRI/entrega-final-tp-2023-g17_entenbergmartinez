#include <catch2/catch.hpp>
#include <encabezados.h>
#include <archivos.cpp>
#include <gym.cpp>

TEST_CASE("leer archivos")
{
    SECTION("Archivo binario") {

        u_int cantAsist;
        Asistencia *asistencias;
        eArchivos errBinario;

        ifstream archivobinlee("../asistencias_1697673600000.dat", ios::binary);

        errBinario = LeerArchivoBinario(archivobinlee, asistencias, cantAsist);

        REQUIRE(errBinario == ExitoOperacion);
        REQUIRE(cantAsist == 29);

        archivobinlee.close();

        for(u_int i = 0; i < cantAsist; i++){
            delete[]asistencias[i].CursosInscriptos;
        }
        delete [] asistencias;
    }

    SECTION("Archivo Clientes") {

        u_int cantClientes;
        ClientesGYM *Clientes, ClientePrueba;
        eArchivos errArchivocliente;

        ClientePrueba.idCliente = 206;
        ClientePrueba.apellido = "Torres";
        ClientePrueba.email = "MateoTorres@bolandia.iri";
        ClientePrueba.estado = 0;
        ClientePrueba.fechanacimiento = "08-01-1995";
        ClientePrueba.nombre = "Mateo";
        ClientePrueba.telefono = "844-131-1318";

        ifstream infileClientes("../iriClientesGYM.csv");

        errArchivocliente = leerArchivoClientes(infileClientes, Clientes, cantClientes);

        REQUIRE(errArchivocliente == ExitoOperacion);
        REQUIRE(cantClientes == 250);
        REQUIRE(Clientes[205].apellido == ClientePrueba.apellido);
        REQUIRE(Clientes[205].idCliente == ClientePrueba.idCliente);
        REQUIRE(Clientes[205].email == ClientePrueba.email);
        REQUIRE(Clientes[205].estado == ClientePrueba.estado);
        REQUIRE(Clientes[205].fechanacimiento == ClientePrueba.fechanacimiento);
        REQUIRE(Clientes[205].nombre == ClientePrueba.nombre);
        REQUIRE(Clientes[205].telefono == ClientePrueba.telefono);

        infileClientes.close();

        delete []Clientes;
    }

    SECTION("Archivo Clases") {

        u_int cantclases;
        ClasesGym *Clases, ClasePrueba;
        eArchivos errArchivoclase;

        ClasePrueba.idClase = 9;
        ClasePrueba.nombre = "Yoga";
        ClasePrueba.horario = 15;
        ClasePrueba.cuposMax = 25;
        ClasePrueba.cuposActuales = 0;

        ifstream infileClases("../iriClasesGYM.csv");

        errArchivoclase = leerArchivoClases(infileClases, Clases, cantclases);

        REQUIRE(errArchivoclase == ExitoOperacion);
        REQUIRE(cantclases == 60);
        REQUIRE(Clases[8].idClase == ClasePrueba.idClase);
        REQUIRE(Clases[8].nombre == ClasePrueba.nombre);
        REQUIRE(Clases[8].horario == ClasePrueba.horario);
        REQUIRE(Clases[8].cuposMax == ClasePrueba.cuposMax);
        REQUIRE(Clases[8].cuposActuales == ClasePrueba.cuposActuales);

        infileClases.close();

        delete []Clases;
    }
}

TEST_CASE("Escribir archivo")
{

    u_int cantAsistencias = 2, cantAsists;
    Asistencia *AsistenciaClientes, *AsistenciaClientesPrueba;
    eArchivos errArchivoBinario, errBinario;
    cantAsistencias = 2;

    AsistenciaClientes = new Asistencia[cantAsistencias];


    AsistenciaClientes[0].idCliente = 203;
    AsistenciaClientes[0].cantInscriptos = 3;
    AsistenciaClientes[0].CursosInscriptos = new Inscripcion[AsistenciaClientes[0].cantInscriptos];
    AsistenciaClientes[0].CursosInscriptos[0].idClase = 12;
    AsistenciaClientes[0].CursosInscriptos[0].fechaInscripcion = 1700103600;
    AsistenciaClientes[0].CursosInscriptos[1].idClase = 43;
    AsistenciaClientes[0].CursosInscriptos[1].fechaInscripcion = 1700203600;
    AsistenciaClientes[0].CursosInscriptos[2].idClase = 35;
    AsistenciaClientes[0].CursosInscriptos[2].fechaInscripcion = 1700303600;

    AsistenciaClientes[1].idCliente = 14;
    AsistenciaClientes[1].cantInscriptos = 3;
    AsistenciaClientes[1].CursosInscriptos = new Inscripcion[AsistenciaClientes[1].cantInscriptos];
    AsistenciaClientes[1].CursosInscriptos[0].idClase = 41;
    AsistenciaClientes[1].CursosInscriptos[0].fechaInscripcion = 1700103600;
    AsistenciaClientes[1].CursosInscriptos[1].idClase = 53;
    AsistenciaClientes[1].CursosInscriptos[1].fechaInscripcion = 1700203600;
    AsistenciaClientes[1].CursosInscriptos[2].idClase = 55;
    AsistenciaClientes[1].CursosInscriptos[2].fechaInscripcion = 1700303600;

    ofstream archivobin("../asistencias.dat", ios :: binary);

    errArchivoBinario = EscribirArchivoBinario(archivobin, AsistenciaClientes, cantAsistencias);

    REQUIRE(errArchivoBinario == ExitoOperacion);

    archivobin.close();

    ifstream archivobinlee("../asistencias.dat", ios::binary);

    errBinario = LeerArchivoBinario(archivobinlee, AsistenciaClientesPrueba, cantAsists);

    REQUIRE(errBinario == ExitoOperacion);
    REQUIRE(cantAsists == cantAsistencias);
    REQUIRE(AsistenciaClientesPrueba[0].idCliente == AsistenciaClientes[0].idCliente);
    REQUIRE(AsistenciaClientesPrueba[0].cantInscriptos  == AsistenciaClientes[0].cantInscriptos);
    REQUIRE(AsistenciaClientesPrueba[0].CursosInscriptos[0].idClase == AsistenciaClientes[0].CursosInscriptos[0].idClase);
    REQUIRE(AsistenciaClientesPrueba[0].CursosInscriptos[0].fechaInscripcion == AsistenciaClientes[0].CursosInscriptos[0].fechaInscripcion);
    REQUIRE(AsistenciaClientesPrueba[0].CursosInscriptos[1].idClase == AsistenciaClientes[0].CursosInscriptos[1].idClase);
    REQUIRE(AsistenciaClientesPrueba[0].CursosInscriptos[1].fechaInscripcion == AsistenciaClientes[0].CursosInscriptos[1].fechaInscripcion);
    REQUIRE(AsistenciaClientesPrueba[0].CursosInscriptos[2].idClase == AsistenciaClientes[0].CursosInscriptos[2].idClase);
    REQUIRE(AsistenciaClientesPrueba[0].CursosInscriptos[2].fechaInscripcion == AsistenciaClientes[0].CursosInscriptos[2].fechaInscripcion);

    REQUIRE(AsistenciaClientesPrueba[1].idCliente == AsistenciaClientes[1].idCliente);
    REQUIRE(AsistenciaClientesPrueba[1].cantInscriptos  == AsistenciaClientes[1].cantInscriptos);
    REQUIRE(AsistenciaClientesPrueba[1].CursosInscriptos[0].idClase == AsistenciaClientes[1].CursosInscriptos[0].idClase);
    REQUIRE(AsistenciaClientesPrueba[1].CursosInscriptos[0].fechaInscripcion == AsistenciaClientes[1].CursosInscriptos[0].fechaInscripcion);
    REQUIRE(AsistenciaClientesPrueba[1].CursosInscriptos[1].idClase == AsistenciaClientes[1].CursosInscriptos[1].idClase);
    REQUIRE(AsistenciaClientesPrueba[1].CursosInscriptos[1].fechaInscripcion == AsistenciaClientes[1].CursosInscriptos[1].fechaInscripcion);
    REQUIRE(AsistenciaClientesPrueba[1].CursosInscriptos[2].idClase == AsistenciaClientes[1].CursosInscriptos[2].idClase);
    REQUIRE(AsistenciaClientesPrueba[1].CursosInscriptos[2].fechaInscripcion == AsistenciaClientes[1].CursosInscriptos[2].fechaInscripcion);

    archivobinlee.close();

    delete []AsistenciaClientesPrueba;
}
