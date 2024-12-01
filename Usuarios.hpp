#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <list>

using  namespace std;

class Grafos 
{
    private:
    list<int>nodos;
    int amistades[100][6];

    public: 
    Grafos() {
        for (int i = 0; i < 100; i++) {
            for (int j = 0; j < 6; j++) {
                amistades[i][j] = 0; 
            }
        }
    }

    void agregarNodo(int nodo) {
        if(nodos.size()<100)
        {
            nodos.push_back(nodo);
        } else 
        {
            cout<<"Limite de perfiles alcanzado";
        }
    }

    void eliminarNodo(int nodo) {
        for (int i = 0; i < 6; i++) {
        int amigo = amistades[nodo][i];
        if (amigo != 0) {
            for (int j = 0; j < 6; j++) {
                if (amistades[amigo][j] == nodo) {
                    amistades[amigo][j] = 0;
                    break;
                }
            }
            amistades[nodo][i] = 0; 
        }
    }
        
        nodos.remove(nodo);  
        guardarAmistadesEnArchivo();
    }

    void cargarGrafo() {
    ifstream archivoNodos("nodos.txt");
    string linea;

    while (getline(archivoNodos, linea)) {
        int idNodo = stoi(linea);  
        agregarNodo(idNodo); 
    }

    archivoNodos.close();
}

    bool agregarAmistad(int nodo1, int nodo2)
    {
        bool nodo1Existe=false, nodo2Existe=false;
        if(nodo1==nodo2) return false;

        for(int nodo : nodos)
        {
            if(nodo==nodo1) nodo1Existe=true;
            if(nodo==nodo2) nodo2Existe=true;
        }

        if(!nodo1Existe || !nodo2Existe)
        {
            return false;
        }

        //ver si ya son amigos
        for (int i = 0; i < 6; i++)
        {
            if(amistades[nodo1][i]==nodo2)
            {
                return false;
            }
        }
        

        int numAmistades1 = contarAmistades(nodo1);
        int numAmistades2 = contarAmistades(nodo2);

        if (numAmistades1 >= 6 || numAmistades2 >= 6) {
            return false;
        }

        //supera todas las validaciones se agrega a la matriz
        for (int i = 0; i < 6; i++) {
            if (amistades[nodo1][i] == 0) {
                amistades[nodo1][i] = nodo2;
                break;
            }
        }
        for (int i = 0; i < 6; i++) {
            if (amistades[nodo2][i] == 0) {
                amistades[nodo2][i] = nodo1;
                break;
            }
        }
        
        guardarAmistadesEnArchivo();
        return true;
    }

    int contarAmistades(int nodo) {
        int count = 0;
        for (int i = 0; i < 6; i++) {
            if (amistades[nodo][i] != 0) {
                count++;
            }
        }
        return count;
    }

    void guardarAmistadesEnArchivo() {
        ofstream archivo("amistades.txt", ios::trunc);

        for (int i = 0; i < 100; i++) {
            for (int j = 0; j < 6; j++) {
                if (amistades[i][j] != 0) {
                    archivo << i << " " << amistades[i][j] << endl;
                }
            }
        }

        archivo.close();
    }

    void cargarAmistadesDesdeArchivo() {
        ifstream archivo("amistades.txt");
        string linea;

        while (getline(archivo, linea)) {
            int nodo1, nodo2;
            sscanf(linea.c_str(), "%d %d", &nodo1, &nodo2);
            agregarAmistad(nodo1, nodo2); 
        }

        archivo.close();
    }

    bool comprobarAmistad(int nodo1, int nodo2)
    {
        bool nodo1Existe=false, nodo2Existe=false;
        if(nodo1==nodo2) return false;

        for(int nodo : nodos)
        {
            if(nodo==nodo1) nodo1Existe=true;
            if(nodo==nodo2) nodo2Existe=true;
        }

        if(!nodo1Existe || !nodo2Existe)
        {
            return false;
        }

        //ver si ya son amigos
        for (int i = 0; i < 6; i++)
        {
            if(amistades[nodo1][i]==nodo2)
            {
                return true;
            }
        }
    }
    
    bool eliminarAmistad(int nodo1, int nodo2) {
    bool nodo1Existe = false, nodo2Existe = false;

    for (int nodo : nodos) {
        if (nodo == nodo1) nodo1Existe = true;
        if (nodo == nodo2) nodo2Existe = true;
    }

    if (!nodo1Existe || !nodo2Existe) {
        return false;
    }

    bool amistadEliminada = false;

    // Eliminar la amistad en ambas direcciones
    for (int i = 0; i < 6; i++) {
        if (amistades[nodo1][i] == nodo2) {
            amistades[nodo1][i] = 0;
            amistadEliminada = true;
            break;
        }
    }

    for (int i = 0; i < 6; i++) {
        if (amistades[nodo2][i] == nodo1) {
            amistades[nodo2][i] = 0;
            break;
        }
    }

    if (amistadEliminada) {
        guardarAmistadesEnArchivo();
        return true;
    } else {
        return false;
    }
}

    void mostrarTodosAmigos(int nodo1, int amigos[],int &numAmigos)
    {
        numAmigos=0;
        bool nodoExiste = false;
        for (int nodo : nodos) {
        if (nodo == nodo1) {
            nodoExiste = true;
            break;
        }
        }

        if (!nodoExiste) {
            return;
        }

        // Guardar los amigos en el array
        for (int i = 0; i < 6; i++) {
        if (amistades[nodo1][i] != 0) {
            amigos[numAmigos++] = amistades[nodo1][i];
        }
        }

        if (numAmigos == 0) {
        } else {
        }
    }
};

class Usuarios 
{
    private: 
    int nodo;
    string nombre;
    string correo;
    string usuario;
    string clave;
    string icon;
    list<string> interesesSeleccionados;

    public:
    Usuarios(int nodo, const string &nombre, const string &correo, const string &usuario,
             const string &clave, const string &icon, const list<string> &interesesSeleccionados)
        : nodo(nodo), nombre(nombre), correo(correo), usuario(usuario), clave(clave),
          icon(icon), interesesSeleccionados(interesesSeleccionados) {}

    Usuarios() : nodo(0), nombre(""), correo(""), usuario(""), clave(""), icon(""), interesesSeleccionados() {}

    static int generarCodigoAleatorio() {
        srand(time(0));  
        return rand() % 100;  
    }

    static bool verificarCodigoExistente(int codigo) {
        ifstream archivo("usuarios.txt");
        string linea;
        bool existe = false;

        while (getline(archivo, linea)) {
            int pos1 = linea.find(';');
            int codigoEnArchivo = stoi(linea.substr(0, pos1)); 

            if (codigoEnArchivo == codigo) {
                existe = true;
                break;
            }
        }

        archivo.close();
        return existe;
    }

    static void guardarEnArchivo(const string &nombre, const string &correo, const string& usuario, const string &clave, const list<string> &intereses, Grafos &grafo) {
        
        ofstream archivo("usuarios.txt", ios::app);  
        
        int codigo;
        do {
            codigo = generarCodigoAleatorio();
        } while (verificarCodigoExistente(codigo));

        string icono = usuario + ".jpg";

        if (archivo.is_open()) {
            archivo << codigo << ";"
                    << nombre << ";"
                    << correo << ";"
                    << usuario << ";"
                    << clave << ";"
                    << icono <<";";

             string interesesStr;
        for (auto interes : intereses) {
            interesesStr += interes + ",";
        }

        if (!interesesStr.empty()) {
            interesesStr.pop_back(); // Eliminar la última coma
        }

            archivo << interesesStr << endl;

            archivo.close();

            ofstream archivoNodos("nodos.txt", ios::app);
            if (archivoNodos.is_open()) 
            {
                archivoNodos << codigo << endl;
                archivoNodos.close();
            }
            grafo.agregarNodo(codigo);
        }
    }

    static bool VerificarCorreo(string correo_escrito) {
    ifstream archivo("usuarios.txt");
    string linea;
    int codigo;
    string nombre, correo, usuario, clave;
    list<string> intereses;
    
    while (getline(archivo, linea)) {
        int pos1 = linea.find(';');
        int pos2 = linea.find(';', pos1 + 1);
        int pos3 = linea.find(';', pos2 + 1);
        int pos4 = linea.find(';', pos3 + 1);
        int pos5 = linea.find(';', pos4 + 1);
        
        correo = linea.substr(pos2 + 1, pos3 - pos2 - 1);  

        if (correo_escrito == correo) {
            return false;  
        }

    }

    return true;  
}

    static bool verificarLogin(const string &correoIngresado, const string &claveIngresada, int &ID) {
    ifstream archivo("usuarios.txt");
    string linea;
    string correo, clave;
    int codigo;

    while (getline(archivo, linea)) {
        int pos1 = linea.find(';');
        int pos2 = linea.find(';', pos1 + 1);
        int pos3 = linea.find(';', pos2 + 1);
        int pos4 = linea.find(';', pos3 + 1);
        int pos5 = linea.find(';', pos4 + 1);

        codigo = stoi(linea.substr(0, pos1));                      
        correo = linea.substr(pos2 + 1, pos3 - pos2 - 1);           
        clave = linea.substr(pos4 + 1, pos5 - pos4 - 1);            

        if (correoIngresado == correo && claveIngresada == clave) {
            ID=codigo;
            archivo.close();
            return true;
        }
    }
    setcolor(BLACK);
    outtextxy(170,600,(char*)"Credenciales invalidas");
    archivo.close();
    return false;
}

    static bool VerificarUsuario(const string& usuario_escrito) {
    ifstream archivo("usuarios.txt");
    string linea;
    string usuario;


    while (getline(archivo, linea)) {
        int pos1 = linea.find(';');
        int pos2 = linea.find(';', pos1 + 1);
        int pos3 = linea.find(';', pos2 + 1);
        int pos4 = linea.find(';', pos3 + 1);
        
        usuario = linea.substr(pos3 + 1, pos4 - pos3 - 1);

        if (usuario_escrito == usuario) {
            archivo.close();  
            return false;  
        }
    }

    archivo.close();  
    return true;  
}

    void mostrarUsuario() {
        setbkcolor(COLOR(0x33, 0x33, 0x33));  
        setcolor(WHITE);
        settextstyle(8, 0, 1);

        char strNombre[100];
        char strUsuario[100];
        char strIcon[100];
        
        strcpy(strNombre, nombre.c_str());
        strcpy(strUsuario, usuario.c_str());
        strcpy(strIcon, icon.c_str());

        readimagefile(strIcon, 1215, 110, 1400, 245);

        outtextxy(1170, 300, strNombre);

        outtextxy(1170, 325, (char*)"Usuario:");
        outtextxy(1270, 325, strUsuario);

        int xInteres = 1170, yInteres = 350;  
        outtextxy(1170, yInteres, (char*)"Intereses:");
        yInteres += 25;
        for (auto interes : interesesSeleccionados) {
            char strInteres[100];
            strcpy(strInteres, interes.c_str());
            outtextxy(1170, yInteres, strInteres);
            yInteres += 22;
        }
        return;
    }

    static Usuarios cargarUsuario(int codigoUsuario) {
    ifstream archivo("usuarios.txt");

    string linea;
    while (getline(archivo, linea)) {
        int pos1 = linea.find(';');
        int pos2 = linea.find(';', pos1 + 1);
        int pos3 = linea.find(';', pos2 + 1);
        int pos4 = linea.find(';', pos3 + 1);
        int pos5 = linea.find(';', pos4 + 1);
        int pos6 = linea.find(';', pos5 + 1);

        // Extraer campos
        int nodo = stoi(linea.substr(0, pos1)); 
        string nombre = linea.substr(pos1 + 1, pos2 - pos1 - 1); 
        string correo = linea.substr(pos2 + 1, pos3 - pos2 - 1); 
        string usuario = linea.substr(pos3 + 1, pos4 - pos3 - 1); 
        string clave = linea.substr(pos4 + 1, pos5 - pos4 - 1); 
        string icon = linea.substr(pos5 + 1, pos6 - pos5 - 1); 
        string interesesStr = linea.substr(pos6 + 1);
        cout<<nodo<<" : "<<nombre<<" : "<<correo<<" : "<<usuario<<" : "<<clave<<" : "<<icon;

        // Convertir intereses a una lista
        list<string> interesesSeleccionados;
        string interes = "";
        for (char c : interesesStr) 
        {
            if (c == ',') {
                cout<<interes<<endl;
                interesesSeleccionados.push_back(interes);
                interes = ""; 
            } else {
                interes += c;
            }
        }

        if (!interes.empty()) 
        {
            cout<<interes<<endl;
            interesesSeleccionados.push_back(interes);
        }

        if (nodo == codigoUsuario) 
        {
            archivo.close();
            return Usuarios(nodo, nombre, correo, usuario, clave, icon, interesesSeleccionados);
        }
    }

    archivo.close();
    return Usuarios(); 
}

    static bool eliminarUsuario_Nodo(int id, Grafos &grafo) {

        //eliminar de usuario.txt
        ifstream archivo("usuarios.txt");
        ofstream archivoTemp("usuarios_temp.txt");
        string linea;
        bool encontrado = false;

        while (getline(archivo, linea)) {
            int pos1 = linea.find(';');
            int codigo = stoi(linea.substr(0, pos1));

            if (codigo == id) {
                encontrado = true; 
            } else {
                archivoTemp << linea << endl; 
            }
        }

        archivo.close();
        archivoTemp.close();

        if (!encontrado) {
            cout << "Usuario no encontrado." << endl;
            remove("usuarios_temp.txt");
            return false;
        }

        remove("usuarios.txt");
        rename("usuarios_temp.txt", "usuarios.txt");


        // Eliminar nodo de nodos.txt
        ifstream archivoNodos("nodos.txt");
        ofstream archivoNodosTemp("nodos_temp.txt");
        bool nodoEliminado = false;

        while (getline(archivoNodos, linea)) {
            int nodo = stoi(linea);
            if (nodo == id) {
                nodoEliminado = true;  
            } else {
                archivoNodosTemp << linea << endl; 
            }
        }

        archivoNodos.close();
        archivoNodosTemp.close();

        if (!nodoEliminado) {
            remove("nodos_temp.txt");
            return false;
        }
        remove("nodos.txt");
        rename("nodos_temp.txt", "nodos.txt");

        grafo.eliminarNodo(id);


        return true;
    }

    static void extraerCodigo(const string &usuarioBuscado, int &codigoAgg)
    {
        ifstream archivo("usuarios.txt");
        string linea;
        while (getline(archivo, linea)) {
            int pos1 = linea.find(';');
            int pos2 = linea.find(';', pos1 + 1);
            int pos3 = linea.find(';', pos2 + 1);
            int pos4 = linea.find(';', pos3 + 1);

            int codigo = stoi(linea.substr(0, pos1)); 
            string usuarios = linea.substr(pos3 + 1, pos4 - pos3 - 1); 

            if (usuarios == usuarioBuscado) {
                archivo.close();
                codigoAgg=codigo;
                return;
            }
        }

        archivo.close();
        return; 
    }

    static void extraerUsuario(string &usuarioBuscado, int &ID)
    {
        ifstream archivo("usuarios.txt");

        string linea;
        while (getline(archivo, linea)) {
            int pos1 = linea.find(';');
            int pos2 = linea.find(';', pos1 + 1);
            int pos3 = linea.find(';', pos2 + 1);
            int pos4 = linea.find(';', pos3 + 1);

            int codigo = stoi(linea.substr(0, pos1)); 
            string usuarios = linea.substr(pos3 + 1, pos4 - pos3 - 1); 

            if (ID == codigo) {
                archivo.close();
                usuarioBuscado=usuarios;
                return;
            }
    }

    archivo.close();
    return; 
    }

    void mostrarPerfil(int cantAmistades)
    {
        settextstyle(8, 0, 1);


        char strNombre[100];
        char strUsuario[100];
        char strIcon[100];
        char strCantAmigos[50];
        
        strcpy(strNombre, nombre.c_str());
        strcpy(strUsuario, usuario.c_str());
        strcpy(strIcon, icon.c_str());


        readimagefile(strIcon, 377, 200, 495, 312);

        outtextxy(300, 350, strNombre);

        outtextxy(300, 325, (char*)"Usuario:");
        outtextxy(410, 325, strUsuario);

        int xInteres = 300, yInteres = 375;  
        outtextxy(300, yInteres, (char*)"Intereses:");
        yInteres += 25;
        for (auto interes : interesesSeleccionados) {
            char strInteres[100];
            strcpy(strInteres, interes.c_str());
            outtextxy(300, yInteres, strInteres);
            yInteres += 22;
        }
        sprintf(strCantAmigos, "%d", cantAmistades);
        outtextxy(520,610,(char*)"Amigos: ");
        outtextxy(600,610,strCantAmigos);

        return;
    }

};