#ifndef GYM_H
#define GYM_H

#include <encabezados.h>

//Declaro Errores
enum Clientes  { ErrIdClienteinx = -6, ErrNombre = -5, ErrApellido = -4, ErrTelefono = -3, ErrMuyViejo = -2, ErrMuyJoven = -1, ExitoCliente = 1 };
enum Clases  { ErrCupos = -2, ErrIdClaseinx = -1, ExitoClase = 1 };
enum Asistencias  { ErrClaseRepetida = -3, ErrSuperposicionDeHorarios = -2, ErrClienteinx = -1, ExitoAsistencias = 1 };
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
    u_int idCliente, cantInscripcion;
    Inscripcion* CursosInsciptos;

} Asistencia;

typedef struct
{
    u_int idClase;
    string nombre;
    time_t horario;
    u_int cuposActuales;
    u_int cuposMax;

} ClasesGym;

typedef struct
{
    u_int idCliente;
    string nombre, apellido, email, telefono;
    const char *fechanacimiento;
    int estado;

} ClientesGYM;

//Buscar
int BuscarIdCliente(ClientesGYM *Clientes, int IdCliente);
int BuscarIdClase(ClasesGym *Clases, int IdClase);
int BuscarAsistenicaCliente(ClasesGym *Clases, int IdClase);

//Filtrar
eCliente FiltroDeCliente(ClientesGYM *Clientes, int IdCliente);
eClase FiltroDeClase(ClasesGym *Clases, int IdCliente, int IdClase, Asistencia *AsistenciaCliente);
eAsistencia FiltroDeAsistencia(Asistencia *AsistenciaCliente, int IdCliente);
eDia FiltroDeDia(time_t fechaInscripcion);

//Imprimir
int


#endif // GYM_H
