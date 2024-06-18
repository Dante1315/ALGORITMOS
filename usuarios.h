#ifndef USUARIOS_H
#define USUARIOS_H

#define MAX_USUARIOS 100
#define MAX_NOMBRE 50
#define MAX_CONTRASENA 20

typedef struct Usuario {
    char nombreUsuario[MAX_NOMBRE];
    char contrasena[MAX_CONTRASENA];
    char nombreCompleto[MAX_NOMBRE];
    int tipoUsuario; 
    struct Usuario *siguiente;
    struct Usuario *anterior;
} Usuario;

typedef struct {
    Usuario *primero;
    Usuario *ultimo;
} TablaUsuarios;

void inicializarTablaUsuarios(TablaUsuarios *tabla);
int agregarUsuario(TablaUsuarios *tabla, Usuario nuevoUsuario);
Usuario* buscarUsuario(TablaUsuarios *tabla, char nombreUsuario[], char contrasena[]);
void cargarUsuariosPredeterminados(TablaUsuarios *tabla);

#endif
