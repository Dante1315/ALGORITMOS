#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuarios.h"
#include "horarios.h"

void menuAdministrador(Grupo grupos[], int numGrupos);
void menuAlumno(Grupo grupos[], int numGrupos);

const char* horasInicio[] = {"15:00", "16:30", "18:30", "20:00"};
const char* horasFin[] = {"16:30", "18:00", "20:00", "21:30"};

int seleccionarHorario(char* horaInicio, char* horaFin);

int main() {
    TablaUsuarios tablaUsuarios;
    inicializarTablaUsuarios(&tablaUsuarios);
    cargarUsuariosPredeterminados(&tablaUsuarios);

    Grupo grupos[MAX_GRUPOS];
    inicializarGrupos(grupos, MAX_GRUPOS);

    char nombreUsuario[MAX_NOMBRE];
    char contrasena[MAX_CONTRASENA];
    Usuario *usuarioLogueado;

    while (1) {
        printf("\n--- Sistema de Administración de Horarios ---\n");
        printf("Ingrese su nombre de usuario: ");
        scanf("%s", nombreUsuario);
        printf("Ingrese su contraseña: ");
        scanf("%s", contrasena);

        usuarioLogueado = buscarUsuario(&tablaUsuarios, nombreUsuario, contrasena);

        if (usuarioLogueado != NULL) {
            if (usuarioLogueado->tipoUsuario == 0) {
                menuAdministrador(grupos, MAX_GRUPOS);
            } else if (usuarioLogueado->tipoUsuario == 1) {
                menuAlumno(grupos, MAX_GRUPOS);
            }
        } else {
            printf("Usuario o contraseña incorrectos. Intente nuevamente.\n");
        }
    }

    return 0;
}

int seleccionarHorario(char* horaInicio, char* horaFin) {
    int opcion;
    printf("Seleccione el horario:\n");
    for (int i = 0; i < 4; i++) {
        printf("%d. %s - %s\n", i + 1, horasInicio[i], horasFin[i]);
    }
    printf("Opción: ");
    scanf("%d", &opcion);

    if (opcion >= 1 && opcion <= 4) {
        strcpy(horaInicio, horasInicio[opcion - 1]);
        strcpy(horaFin, horasFin[opcion - 1]);
        return 0;
    } else {
        printf("Opción inválida.\n");
        return -1;
    }
}

void menuAdministrador(Grupo grupos[], int numGrupos) {
    int opcion, idGrupo, indiceHorario;
    Horario nuevoHorario, horarioModificado;

    do {
        printf("\n--- Menu Administrador ---\n");
        printf("1. Agregar horario\n");
        printf("2. Modificar horario\n");
        printf("3. Eliminar horario\n");
        printf("4. Consultar horarios\n");
        printf("5. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Ingrese el ID del grupo (0-%d): ", numGrupos - 1);
                scanf("%d", &idGrupo);
                if (idGrupo >= 0 && idGrupo < numGrupos) {
                    printf("Ingrese el nombre de la clase: ");
                    scanf("%s", nuevoHorario.nombreClase);
                    if (seleccionarHorario(nuevoHorario.horaInicial, nuevoHorario.horaFinal) == 0) {
                        printf("Ingrese el nombre del profesor: ");
                        scanf("%s", nuevoHorario.profesor);

                        agregarHorario(&grupos[idGrupo], nuevoHorario);
                    }
                } else {
                    printf("ID de grupo inválido.\n");
                }
                break;

            case 2:
                printf("Ingrese el ID del grupo (0-%d): ", numGrupos - 1);
                scanf("%d", &idGrupo);
                if (idGrupo >= 0 && idGrupo < numGrupos) {
                    printf("Ingrese el índice del horario a modificar: ");
                    scanf("%d", &indiceHorario);
                    printf("Ingrese el nuevo nombre de la clase: ");
                    scanf("%s", horarioModificado.nombreClase);
                    if (seleccionarHorario(horarioModificado.horaInicial, horarioModificado.horaFinal) == 0) {
                        printf("Ingrese el nuevo nombre del profesor: ");
                        scanf("%s", horarioModificado.profesor);

                        modificarHorario(&grupos[idGrupo], indiceHorario, horarioModificado);
                    }
                } else {
                    printf("ID de grupo inválido.\n");
                }
                break;

            case 3:
                printf("Ingrese el ID del grupo (0-%d): ", numGrupos - 1);
                scanf("%d", &idGrupo);
                if (idGrupo >= 0 && idGrupo < numGrupos) {
                    printf("Ingrese el índice del horario a eliminar: ");
                    scanf("%d", &indiceHorario);
                    eliminarHorario(&grupos[idGrupo], indiceHorario);
                } else {
                    printf("ID de grupo inválido.\n");
                }
                break;

            case 4:
                printf("Ingrese el ID del grupo (0-%d): ", numGrupos - 1);
                scanf("%d", &idGrupo);
                if (idGrupo >= 0 && idGrupo < numGrupos) {
                    consultarHorarios(grupos[idGrupo]);
                } else {
                    printf("ID de grupo inválido.\n");
                }
                break;

            case 5:
                return;

            default:
                printf("Opción inválida. Intente nuevamente.\n");
                break;
        }
    } while (opcion != 5);
}

void menuAlumno(Grupo grupos[], int numGrupos) {
    int opcion, idGrupo, indiceHorario;
    Horario *horarioAlumno[MAX_GRUPOS * 4];
    int numHorarios = 0;
    int traslape;

    do {
        printf("\n--- Menu Alumno ---\n");
        printf("1. Armar horario de clases\n");
        printf("2. Eliminar horario\n");
        printf("3. Consultar horario\n");
        printf("4. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                do {
                    printf("Ingrese el ID del grupo (0-%d): ", numGrupos - 1);
                    scanf("%d", &idGrupo);
                    if (idGrupo >= 0 && idGrupo < numGrupos) {
                        consultarHorarios(grupos[idGrupo]);
                        printf("Ingrese el índice del horario a agregar: ");
                        scanf("%d", &indiceHorario);

                        Horario *actual = grupos[idGrupo].primero;
                        int indice = 0;
                        while (actual != NULL && indice < indiceHorario) {
                            actual = actual->siguiente;
                            indice++;
                        }

                        if (actual != NULL && indice == indiceHorario) {
                            traslape = 0;
                            for (int i = 0; i < numHorarios; i++) {
                                if (!(strcmp(actual->horaFinal, horarioAlumno[i]->horaInicial) <= 0 || strcmp(actual->horaInicial, horarioAlumno[i]->horaFinal) >= 0)) {
                                    traslape = 1;
                                    break;
                                }
                            }

                            if (!traslape) {
                                horarioAlumno[numHorarios] = (Horario *)malloc(sizeof(Horario));
                                *(horarioAlumno[numHorarios]) = *actual;
                                numHorarios++;
                                printf("Horario agregado correctamente.\n");
                            } else {
                                printf("Error: El horario se traslapa con uno ya añadido.\n");
                            }
                        } else {
                            printf("Índice de horario inválido.\n");
                        }
                    } else {
                        printf("ID de grupo inválido.\n");
                    }

                    printf("¿Desea agregar otro horario? (1: Sí, 0: No): ");
                    scanf("%d", &opcion);
                } while (opcion == 1);
                break;

            case 2:
                printf("Ingrese el índice del horario a eliminar: ");
                scanf("%d", &indiceHorario);
                if (indiceHorario >= 0 && indiceHorario < numHorarios) {
                    free(horarioAlumno[indiceHorario]);
                    for (int i = indiceHorario; i < numHorarios - 1; i++) {
                        horarioAlumno[i] = horarioAlumno[i + 1];
                    }
                    numHorarios--;
                    printf("Horario eliminado correctamente.\n");
                } else {
                    printf("Índice de horario inválido.\n");
                }
                break;

            case 3:
                printf("Horarios del alumno:\n");
                for (int i = 0; i < numHorarios; i++) {
                    printf("%d. %s de %s a %s con %s\n", i, horarioAlumno[i]->nombreClase, horarioAlumno[i]->horaInicial, horarioAlumno[i]->horaFinal, horarioAlumno[i]->profesor);
                }
                break;

            case 4:
                for (int i = 0; i < numHorarios; i++) {
                    free(horarioAlumno[i]);
                }
                return;

            default:
                printf("Opción inválida. Intente nuevamente.\n");
                break;
        }
    } while (opcion != 4);
}
