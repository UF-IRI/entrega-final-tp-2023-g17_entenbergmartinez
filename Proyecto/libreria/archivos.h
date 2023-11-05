#ifndef ARCHIVOS_H
#define ARCHIVOS_H

#include <gym.h>

//Declaro errores
enum Archivos {ErrorApertura = -2, ErrorEscritura = -1, ExitoOperacion = 1};
typedef enum Archivos  eArchivos;

//Declaro Funciones
eArchivos leerArchivoClientes(string archivo, ClientesGYM *&Clientes, int &cantClientes);
eArchivos leerArchivoClases(string archivo, ClasesGym *&Clases, int &cantClases);
//void LeerArchivoBinario(ifstream &archivo, );

#endif // ARCHIVOS_H
