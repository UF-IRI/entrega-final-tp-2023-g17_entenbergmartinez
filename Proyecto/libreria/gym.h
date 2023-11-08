#ifndef GYM_H
#define GYM_H

#include "encabezados.h"

//Declaro Errores
enum Clientes  { ErrEstado = -7, ErrIdClienteinx = -6, ErrNombre = -5, ErrApellido = -4, ErrTelefono = -3, ErrMuyViejo = -2, ErrMuyJoven = -1, ExitoCliente = 1 };
enum Clases  { ErrEspacioCrearAsistencia = -5, ErrClaseRepetida = -4, ErrSuperposicionDeHorarios = -3, ErrCupos = -2, ErrIdClaseinx = -1, ExitoClase = 1 };
enum Asistencias  { ErrEspacio = -1, ExitoAsistencias = 1, ExitoCrearAsistencias = 2 };
enum Dia  { ErrDia = -1, ExitoDia = 1 };


typedef enum Clientes  eCliente;
typedef enum Clases  eClase;
typedef enum Asistencias   eAsistencia;
typedef enum Dia eDia;


//Declaro estructuras
typedef struct
{
    u_int idClase;
    time_t fechaInscripcion;

} Inscripcion;

typedef struct
{
    u_int idCliente, cantInscriptos;
    Inscripcion* CursosInscriptos;

} Asistencia;

typedef struct
{
    u_int idClase;
    string nombre;
    float horario;
    u_int cuposActuales;
    u_int cuposMax;

} ClasesGym;

typedef struct
{
    u_int idCliente;
    string nombre, apellido, email, telefono;
    string fechanacimiento;
    int estado;

} ClientesGYM;

//Buscar
eCliente BuscarIdCliente(ClientesGYM *Clientes, u_int idCliente, u_int cantClientes, ClientesGYM &cliente);
eClase BuscarIdClase(ClasesGym *Clases, u_int idClase, u_int cantClases, ClasesGym &clase);
eClase BuscarIdClase(ClasesGym *Clases, u_int idClase, u_int cantClases);
eAsistencia BuscarAsistenicaCliente(u_int idCliente, u_int idClase, Asistencia *&AsistenciaClientes, Asistencia &AsistenciaCliente, u_int &cantAsistencias);
eAsistencia BuscarAsistenicaCliente(u_int idClase, u_int idCliente,  Asistencia *&AsistenciaClientes);
eClase BuscarIdClaseEnInscripciones(Asistencia AsistenciaCliente, u_int idClase);

//Filtrar
eCliente FiltroDeCliente(ClientesGYM *Clientes, u_int idCliente, u_int cantClientes);
eClase FiltroDeClase(ClasesGym *Clases, u_int idCliente, u_int idClase, Asistencia *&AsistenciaClientes, u_int cantclases, u_int &CantAsistencias);
eDia FiltroFecha();

//resize
Asistencia* resizeClientes(Asistencia *AsistenciaClientes, u_int CantAsistencias, u_int nuevoTam, eAsistencia &eAsist);
Inscripcion* resizeInscripcion(Asistencia *AsistenciaClientes, u_int cantinscripciones, u_int nuevoTam, eAsistencia &eAsist2);

//comparar
eClase CompararClaseInscripciones(ClasesGym clase, Asistencia AsistenciaCliente, ClasesGym *Clases, u_int cantclases);

//Imprimir


#endif // GYM_H
