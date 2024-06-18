#include "usuarios.h"
#include <string.h>
#include <stdlib.h>

void inicializarTablaUsuarios(TablaUsuarios *tabla) {
    tabla->primero = NULL;
    tabla->ultimo = NULL;
}

int agregarUsuario(TablaUsuarios *tabla, Usuario nuevoUsuario) {
    Usuario *nuevo = (Usuario *)malloc(sizeof(Usuario));
    *nuevo = nuevoUsuario;
    nuevo->anterior = NULL;
    nuevo->siguiente = NULL;

    if (tabla->ultimo == NULL) {
        tabla->primero = nuevo;
        tabla->ultimo = nuevo;
    } else {
        tabla->ultimo->siguiente = nuevo;
        nuevo->anterior = tabla->ultimo;
        tabla->ultimo = nuevo;
    }

    return 0;
}

Usuario* buscarUsuario(TablaUsuarios *tabla, char nombreUsuario[], char contrasena[]) {
    Usuario *actual = tabla->primero;

    while (actual != NULL) {
        if (strcmp(actual->nombreUsuario, nombreUsuario) == 0 && strcmp(actual->contrasena, contrasena) == 0) {
            return actual;
        }
        actual = actual->siguiente;
    }

    return NULL;
}

void cargarUsuariosPredeterminados(TablaUsuarios *tabla) {
    Usuario admin = {"admin", "admin123", "Administrador", 0, NULL, NULL};
    Usuario alumno = {"alumno", "alumno123", "Alumno Ejemplo", 1, NULL, NULL};

    agregarUsuario(tabla, admin);
    agregarUsuario(tabla, alumno);
}
