#ifndef HORARIOS_H
#define HORARIOS_H

#define MAX_NOMBRE 50
#define MAX_GRUPOS 5

typedef struct Horario {
    char nombreClase[MAX_NOMBRE];
    char horaInicial[6];
    char horaFinal[6];
    char profesor[MAX_NOMBRE];
    struct Horario *anterior;
    struct Horario *siguiente;
} Horario;

typedef struct {
    int idGrupo;
    Horario *primero;
    Horario *ultimo;
} Grupo;

void inicializarGrupos(Grupo grupos[], int numGrupos);
int agregarHorario(Grupo *grupo, Horario nuevoHorario);
int modificarHorario(Grupo *grupo, int indiceHorario, Horario horarioModificado);
int eliminarHorario(Grupo *grupo, int indiceHorario);
void consultarHorarios(Grupo grupo);
int verificarTraslape(Grupo *grupo, Horario nuevoHorario);

#endif
    