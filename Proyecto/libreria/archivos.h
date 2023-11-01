#ifndef ARCHIVOS_H
#define ARCHIVOS_H

#include <encabezados.h>
#include <gym.h>

//Declaro Errores
enum Archivos { ErrorApertura=-2, ErrorEscritura=-1, ExitoOperacion=1 };
typedef enum Archivos eArchivos;

//Declaro Funciones
int Largo_Archivos(ifstream &archivo);
void LeerArchivoClases(ifstream &archivo, ClasesGym *Clases );
void LeerArchivoClientes(ifstream &archivo, ClientesGYM *Clientes);
void LeerArchivoBinario(ifstream &archivo, );

#endif // ARCHIVOS_H
