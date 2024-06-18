#include "horarios.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void inicializarGrupos(Grupo grupos[], int numGrupos) {
    for (int i = 0; i < numGrupos; i++) {
        grupos[i].idGrupo = i;
        grupos[i].primero = NULL;
        grupos[i].ultimo = NULL;
    }
}

int verificarTraslape(Grupo *grupo, Horario nuevoHorario) {
    Horario *actual = grupo->primero;

    while (actual != NULL) {
        if (!(strcmp(nuevoHorario.horaFinal, actual->horaInicial) <= 0 || strcmp(nuevoHorario.horaInicial, actual->horaFinal) >= 0)) {
            return 1;
        }
        actual = actual->siguiente;
    }
    return 0;
}

int agregarHorario(Grupo *grupo, Horario nuevoHorario) {
    if (verificarTraslape(grupo, nuevoHorario)) {
        printf("Error: El horario se traslapa con otro existente.\n");
        return -1;
    }

    Horario *nuevo = (Horario *)malloc(sizeof(Horario));
    *nuevo = nuevoHorario;
    nuevo->anterior = NULL;
    nuevo->siguiente = NULL;

    if (grupo->ultimo == NULL) {
        grupo->primero = nuevo;
        grupo->ultimo = nuevo;
    } else {
        grupo->ultimo->siguiente = nuevo;
        nuevo->anterior = grupo->ultimo;
        grupo->ultimo = nuevo;
    }

    return 0;
}

int modificarHorario(Grupo *grupo, int indiceHorario, Horario horarioModificado) {
    Horario *actual = grupo->primero;
    int indice = 0;

    while (actual != NULL && indice < indiceHorario) {
        actual = actual->siguiente;
        indice++;
    }

    if (actual != NULL && indice == indiceHorario) {
        if (verificarTraslape(grupo, horarioModificado)) {
            printf("Error: El horario se traslapa con otro existente.\n");
            return -1;
        }
        strcpy(actual->nombreClase, horarioModificado.nombreClase);
        strcpy(actual->horaInicial, horarioModificado.horaInicial);
        strcpy(actual->horaFinal, horarioModificado.horaFinal);
        strcpy(actual->profesor, horarioModificado.profesor);
        return 0;
    }

    return -1;
}

int eliminarHorario(Grupo *grupo, int indiceHorario) {
    Horario *actual = grupo->primero;
    int indice = 0;

    while (actual != NULL && indice < indiceHorario) {
        actual = actual->siguiente;
        indice++;
    }

    if (actual != NULL && indice == indiceHorario) {
        if (actual->anterior != NULL) {
            actual->anterior->siguiente = actual->siguiente;
        } else {
            grupo->primero = actual->siguiente;
        }

        if (actual->siguiente != NULL) {
            actual->siguiente->anterior = actual->anterior;
        } else {
            grupo->ultimo = actual->anterior;
        }

        free(actual);
        return 0;
    }

    return -1;
}

void consultarHorarios(Grupo grupo) {
    Horario *actual = grupo.primero;
    int indice = 0;

    while (actual != NULL) {
        printf("%d. %s de %s a %s con %s\n", indice, actual->nombreClase, actual->horaInicial, actual->horaFinal, actual->profesor);
        actual = actual->siguiente;
        indice++;
    }
}
