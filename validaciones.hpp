#include <iostream>
#include <string.h>
#include <ctime>

using namespace std;


bool validarNombre(char* nombre) {
    if (strlen(nombre) == 0) {
        return false;
    }
    for (int i = 0; nombre[i] != '\0'; i++) {
        if (!isalpha(nombre[i]) && nombre[i] != ' ') {
            return false;
        }
    }
    if (strlen(nombre) < 2) {
        return false;
    }
    return true;
}

bool validarCorreo(char* correo) {
    if (strlen(correo) == 0) {
        return false;
    }
    bool tieneArroba = false, tienePunto = false;
    for (int i = 0; correo[i] != '\0'; i++) {
        if (correo[i] == '@') {
            tieneArroba = true;
        } else if (correo[i] == '.'&&tieneArroba) {
            tienePunto = true;
        }
    }
    if (!tieneArroba || !tienePunto) {
        return false;
    }
    if (!Usuarios::VerificarCorreo(correo)) {
        return false;
    }
    return true;
}

bool validarClave(char* clave) {
    if (strlen(clave) == 0) {
        return false;
    }
    if (strlen(clave) < 6) {
        return false;
    }
    return true;
}

bool validarUsuario(char* usuario) {
    if (strlen(usuario) == 0) {
        return false;
    }
    for (int i = 0; usuario[i] != '\0'; i++) {
        if (!isalnum(usuario[i])) {
            return false;
        }
    }
    if (!Usuarios::VerificarUsuario(usuario)) {
        return false;
    }
    return true;
}
