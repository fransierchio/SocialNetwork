#include <iostream>
#include <string.h>
#include <ctime>

using namespace std;


bool validarNombre(char* nombre) {
    if (strlen(nombre) == 0) {
        cout << "El nombre no puede estar vacío." << endl;
        return false;
    }
    for (int i = 0; nombre[i] != '\0'; i++) {
        if (!isalpha(nombre[i]) && nombre[i] != ' ') {
            cout << "El nombre solo puede contener letras y espacios." << endl;
            return false;
        }
    }
    if (strlen(nombre) < 2) {
        cout << "El nombre debe tener al menos 2 caracteres." << endl;
        return false;
    }
    return true;
}

bool validarCorreo(char* correo) {
    if (strlen(correo) == 0) {
        cout << "El correo no puede estar vacío." << endl;
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
        cout << "El correo debe tener un formato válido (ejemplo@dominio.com)." << endl;
        return false;
    }
    if (!Usuarios::VerificarCorreo(correo)) {
        cout<<"Correo registrado"<<endl;
        return false;
    }
    return true;
}

bool validarClave(char* clave) {
    if (strlen(clave) == 0) {
        cout << "La clave no puede estar vacía." << endl;
        return false;
    }
    if (strlen(clave) < 6) {
        cout << "La clave debe tener al menos 6 caracteres." << endl;
        return false;
    }
    return true;
}

bool validarUsuario(char* usuario) {
    if (strlen(usuario) == 0) {
        cout << "El nombre de usuario no puede estar vacio." << endl;
        return false;
    }
    for (int i = 0; usuario[i] != '\0'; i++) {
        if (!isalnum(usuario[i])) {
            cout << "El nombre de usuario solo puede contener letras y numeros" << endl;
            return false;
        }
    }
    if (!Usuarios::VerificarUsuario(usuario)) {
        cout << "El nombre de usuario ya existe." << endl;
        return false;
    }
    return true;
}
