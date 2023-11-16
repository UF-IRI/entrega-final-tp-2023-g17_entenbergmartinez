#ifndef ARCHIVOS_H
#define ARCHIVOS_H

#include <gym.h>

//Declaro errores
enum Archivos {ErrorApertura = -2, ErrorEscritura = -1, ExitoOperacion = 1};
typedef enum Archivos  eArchivos;

//Declaro Funciones
eArchivos leerArchivoClientes(ifstream &infileClientes, ClientesGYM *&Clientes, u_int &cantClientes);
eArchivos leerArchivoClases(ifstream &infileClases, ClasesGym *&Clases, u_int &cantClases);
eArchivos LeerArchivoBinario(ifstream &archivobinlee, Asistencia *asistencias);
eArchivos EscribirArchivoBinario(ofstream &archivobin, Asistencia *&AsistenciaClientes, u_int &cantAsistencias);

#endif // ARCHIVOS_H
