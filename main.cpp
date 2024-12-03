#include <iostream>
#include <graphics.h>
#include <list>
#include "Usuarios.hpp"
#include "validaciones.hpp"

using namespace std;

enum Menu {INICIO, MENSAJES, AMIGOS, BUSQUEDA,GESTION, CERRAR_SESION, VACIO}; //opciones menu

class Sistema 
{
    private:
    int windowWidth, windowHeight;
    int x, y;
    int correoIndex, passIndex,usuarioIndex, nombreIndex;
    char correo[35];
    char contrasena[19];
    char usuario[14];
    char nombre[35];
    int ID;
    bool oculto;
    Menu menu;
    bool enSubmenu;
    list<string> interesesSeleccionados;
    bool actualizarInteres;
    Usuarios UserPrincipal;
    Grafos grafo;

//LIMPIEZA
    void mostrarMensajeError(int x, int y, char* mensaje) {
    setcolor(RED);
    outtextxy(x, y, mensaje);
}
    void limpiarMensajeError(int x1, int y1, int x2, int y2) {
    setfillstyle(SOLID_FILL, COLOR(0xf3, 0xf3, 0xf3));
    bar(x1, y1, x2, y2);
}
    void limpiarChar(char* arr, int size) 
    {
    for (int i = 0; i < size; i++) {
        arr[i] = '\0';
    }
    } 
    void limpiarBufferTeclado() {
        while (kbhit()) {
            getch();
        }
    }
    void limpiarListaIntereses() {
    interesesSeleccionados.clear();
}

//FUNCIONES ESENCIALES
    bool clicEnRectangulo(int left, int top, int right, int bottom, int x, int y) {
        return (x >= left && x <= right && y >= top && y <= bottom);
    }
    void escribirEnCampo(int left, int top, int right, int bottom, char* texto, int maxLength, int &i, bool oculto) 
    {
        char letra;
        char pass = '*';
        char pass_text[100];
        int textLen = strlen(texto);

        if (!oculto) {
        outtextxy(left + 60, top + 20, texto);
    }   else {
        for (int j = 0; j < textLen; j++) {
            pass_text[j] = pass;
        }
        pass_text[textLen] = '\0';
        outtextxy(left + 60, top + 20, pass_text);
    }

        while (true) {
            if (kbhit()) {
                letra = getch();

                if (letra == '\r') {
                    texto[i] = '\0';
                    break;
                }

                if (letra == '\b' && texto[0] != '\0') {
                    texto[--i] = '\0';
                    bar(left + 60, top + 10, right - 10, bottom);
                    if (!oculto) {
                        outtextxy(left + 60, top + 20, texto);
                    } else {
                        char pass_text[19];
                        for (int j = 0; j < i; j++) {
                            pass_text[j] = pass;
                        }
                        pass_text[i] = '\0';
                        outtextxy(left + 60, top + 20, pass_text);
                    }
                }

                if (letra >= 32 && letra <= 126 && i < maxLength - 1) {
                    texto[i++] = letra;
                    texto[i] = '\0';
                    if (!oculto) {
                        outtextxy(left + 60, top + 20, texto);
                    } else {
                        char pass_text[19];
                        for (int j = 0; j < i; j++) {
                            pass_text[j] = pass;
                        }
                        pass_text[i] = '\0';
                        outtextxy(left + 60, top + 20, pass_text);
                    }
                }
                delay(5);
            } else if (ismouseclick(WM_LBUTTONDOWN)) {
                getmouseclick(WM_LBUTTONDOWN, x, y);

                if (!clicEnRectangulo(left, top, right, bottom, x, y)) {
                    break;
                }
            }
            delay(5);
        }
    }
    void manejarInteres(const char* interes) {
    bool encontrado = false;
    string interesStr(interes);

    for (auto i = interesesSeleccionados.begin(); i != interesesSeleccionados.end(); i++) {
        if (*i == interesStr) {
            interesesSeleccionados.erase(i);
            encontrado = true;
            break; 
        }
    }

    if (!encontrado && interesesSeleccionados.size() < 7) {
        interesesSeleccionados.push_back(interes);
    }

     actualizarInteres=true;
     x=0,y=0;
     return;
    }
    void imprimirIntereses() 
    {
        
        if (actualizarInteres) 
        {
            setfillstyle(SOLID_FILL,WHITE);
            setcolor(WHITE);
            bar(1031,104,1400,571);

            setbkcolor(WHITE);
            setcolor(BLACK);
            settextstyle(8, 0, 3);

            int yPos = 100;  
            for (auto interes : interesesSeleccionados) 
            {
                char interesChar[20];
                strcpy(interesChar, interes.c_str()); 
                setcolor(BLACK);
                outtextxy(1100, yPos, interesChar);
                yPos += 40; 
            }
            actualizarInteres = false;
        }
    }
    bool validarNumIntereses() {
        return (interesesSeleccionados.size() >= 3 && interesesSeleccionados.size() <= 7);
    }

//MANEJO DE INTERFACES
    void manejarClickRegister() 
     {
        setbkcolor(WHITE);
        setcolor(BLACK);
        setfillstyle(SOLID_FILL,WHITE);
        settextstyle(8, 0, 1);
        bool validaciones[4];
        for(int i=0;i<4;i++)
        {
            validaciones[i]=0;
        }    
        while (true) 
        {
            if (ismouseclick(WM_LBUTTONDOWN)) {
                getmouseclick(WM_LBUTTONDOWN, x, y);
                cout<<"X: "<<x<<" Y: "<<y<<endl;
                limpiarBufferTeclado();
            }

            // Campo Nombre
            if (clicEnRectangulo(931, 190, 1310, 235, x, y)) {
                oculto = false;
                setbkcolor(WHITE);
                setcolor(BLACK);
                setfillstyle(SOLID_FILL,WHITE);
                escribirEnCampo(870, 190, 1310, 235, nombre, 34, nombreIndex, oculto);
                validaciones[0]=validarNombre(nombre);
                if (!validaciones[0]) {
                mostrarMensajeError(709, 202, (char*)"invalido");
                } else {
                    limpiarMensajeError(685, 170, 805, 240);
                }
            }

            // Campo Correo
            if (clicEnRectangulo(930, 300, 1310, 345, x, y)) {
                oculto = false;
                setbkcolor(WHITE);
                setcolor(BLACK);
                setfillstyle(SOLID_FILL,WHITE);
                escribirEnCampo(870, 300, 1310, 345, correo, 34, correoIndex, oculto);
                validaciones[1]=validarCorreo(correo);
                if (!validaciones[1]) {
                mostrarMensajeError(709, 320, (char*)"invalido");
                } else {
                limpiarMensajeError(685, 300, 805, 362);
                }
            }

            //Campo Usuario
            if (clicEnRectangulo(925, 410, 1315, 455, x, y)) {
                oculto = false;
                setbkcolor(WHITE);
                setcolor(BLACK);
                setfillstyle(SOLID_FILL,WHITE);
                escribirEnCampo(870, 410, 1315, 455, usuario, 13, usuarioIndex, oculto);
                validaciones[2]=validarUsuario(usuario);
                if (!validaciones[2]) {
                mostrarMensajeError(709, 440, (char*)"invalido");
                } else {
                limpiarMensajeError(685, 413, 805,460);
                }
            }

            //Campo Contraseña
            if (clicEnRectangulo(930, 520, 1310, 565, x, y)) {
                oculto = true;
                setbkcolor(WHITE);
                setcolor(BLACK);
                setfillstyle(SOLID_FILL,WHITE);
                escribirEnCampo(870, 520, 1310, 565, contrasena, 18, passIndex, oculto);
                validaciones[3]=validarClave(contrasena);
                if (!validaciones[3]) {
                mostrarMensajeError(709, 550, (char*)"invalido");
                } else {
                limpiarMensajeError(685, 520, 805, 578);
                }
            }

            // Registrarse
            if (clicEnRectangulo(985, 623, 1260, 683, x, y)) {
                bool valido=true;
                for(int i=0;i<4;i++)
                {
                    if (!validaciones[i])
                    {
                        valido=false;
                    }
                }
                if(valido)
                {
                    InteresesInterfaz();
                    manejarClickIntereses();
                    return;
                } else 
                {
                    x=0,y=0;
                }
            }

            // Campo Iniciar Sesión
            if (clicEnRectangulo(158, 546, 436, 605, x, y)) 
            {
                limpiarChar(correo,35);
                limpiarChar(contrasena,19);
                limpiarChar(usuario,19);
                limpiarChar(nombre,19);
                correoIndex = 0; passIndex = 0, nombreIndex=0, usuarioIndex=0;
                LoginInterfaz();
                return;
            } 
            delay(10);
        }
            delay(10);
    }
    void manejarClickIntereses() 
     {
        setbkcolor(WHITE);
        setcolor(BLACK);
        settextstyle(8, 0, 1);

        const char* intereses[] = {
                "Futbol", "Cocina", "Leyes", "Arte", "Beisbol", "Gym",
                "Finanzas", "Musica", "Videojuegos", "Programacion", "Cine", "Fotografia"
            };

        while (true) 
        {
            
            if (ismouseclick(WM_LBUTTONDOWN)) {
                getmouseclick(WM_LBUTTONDOWN, x, y);
                cout<<"X: "<<x<<" Y: "<<y<<endl;
                limpiarBufferTeclado();
            }

            if(actualizarInteres)
            {
                imprimirIntereses();
            }

            //  Futbol
            if (clicEnRectangulo(77, 211, 212, 346, x, y)) {
                manejarInteres("Futbol");
            }

            // Cocina
            if (clicEnRectangulo(236, 211, 367, 346, x, y)) {
                manejarInteres("Cocina");
            }

            // Leyes
            if (clicEnRectangulo(391, 211, 523, 346, x, y)) {
                manejarInteres("Leyes");
            }

            // Arte
            if (clicEnRectangulo(548, 211, 680, 346, x, y)) {
                manejarInteres("Arte");
            }

            // Beisbol
            if (clicEnRectangulo(77, 363, 212, 495, x, y)) {
                manejarInteres("Beisbol");
            }

            // Gym
            if (clicEnRectangulo(236, 363, 367, 495, x, y)) {
                manejarInteres("Gym");
            }

            // Finanzas
            if (clicEnRectangulo(391, 363, 523, 495, x, y)) {
                manejarInteres("Finanzas");
            }

            // Musica
            if (clicEnRectangulo(548, 363, 680, 495, x, y)) {
                manejarInteres("Musica");
            }

            // Videojuegos
            if (clicEnRectangulo(77, 515, 212, 647, x, y)) {
                manejarInteres("Videojuegos");
            }

            // Programacion
            if (clicEnRectangulo(236, 515, 367, 647, x, y)) {
                manejarInteres("Programacion");
            }

            // Cine
            if (clicEnRectangulo(391, 515, 523, 647, x, y)) {
                manejarInteres("Cine");
            }

            // Fotografia
            if (clicEnRectangulo(548, 515, 680, 647, x, y)) {
                manejarInteres("Fotografia");
            }

             // Registrar
            if (clicEnRectangulo(1075, 620, 1355, 680, x, y)) {
                if(validarNumIntereses())
                {
                    Usuarios::guardarEnArchivo(nombre,correo,usuario,contrasena,interesesSeleccionados, grafo);
                    x=0,y=0;
                    limpiarChar(correo,19);
                    limpiarChar(contrasena,19);
                    limpiarChar(usuario,19);
                    limpiarChar(nombre,19);
                    limpiarListaIntereses();
                    nombreIndex=0;
                    usuarioIndex=0;
                    correoIndex=0;
                    passIndex=0;
                    LoginInterfaz();
                    return;
                }
            }

     
            delay(10);
        }
            delay(10);
    }
    void manejarClickLogin() 
     {
        setbkcolor(WHITE);
        setcolor(BLACK);
        settextstyle(8, 0, 1);
        while (true) 
        {
            if (ismouseclick(WM_LBUTTONDOWN)) {
                getmouseclick(WM_LBUTTONDOWN, x, y);
                cout<<"X: "<<x<<" Y: "<<y<<endl;
                limpiarBufferTeclado();
            }

            // Campo Correo
            if (clicEnRectangulo(165, 265, 555, 311, x, y)) {
                oculto = false;
                escribirEnCampo(100, 265, 555, 311, correo, 35, correoIndex, oculto);
            }

            // Campo Contraseña
            if (clicEnRectangulo(165, 375, 551, 430, x, y)) {
                oculto = true;
                escribirEnCampo(100, 375, 551, 430, contrasena, 18, passIndex, oculto);
            }

            // Registrarse
            if (clicEnRectangulo(1044, 530, 1320, 590, x, y)) {
                limpiarChar(correo,19);
                limpiarChar(contrasena,19);
                correoIndex=0;
                passIndex=0;
                x=0,y=0;
                RegisterInterfaz();
                manejarClickRegister();
            }

            // Campo Iniciar Sesión
            if (clicEnRectangulo(217, 480, 503, 542, x, y)) 
            {
                if(Usuarios::verificarLogin(correo,contrasena,ID))
                {
                    UserPrincipal = Usuarios::cargarUsuario(ID);
                    menu=INICIO;
                    return;
                } else
                {
                    x=0,y=0;
                }   
            }
            delay(10);
        }
            delay(10);
    }
    void manejarClickInicio()
    {
        setbkcolor(WHITE);
        setcolor(BLACK);
        settextstyle(8, 0, 1);
        char usuarioOne[14]="", usuarioTwo[14]="";
        int IndexOne=0, IndexTwo=0;
        int codigoOne=0, codigoTwo=0;
        while (true) 
        {
            if (ismouseclick(WM_LBUTTONDOWN)) 
            {
                getmouseclick(WM_LBUTTONDOWN, x, y);
                cout<<"X: "<<x<<" Y: "<<y<<endl;
                limpiarBufferTeclado();
            

                // Cuadro comprobar Amistades
                //user1
                if (clicEnRectangulo(634, 525, 900, 560, x, y)) {
                    codigoOne=0;
                    oculto = false;
                    setcolor(WHITE);
                    setbkcolor(COLOR(0x8b,0x8b,0x8b));
                    setfillstyle(SOLID_FILL,COLOR(0x8b,0x8b,0x8b));
                    escribirEnCampo(600, 525, 900, 560,usuarioOne, 13, IndexOne, oculto);
                    Usuarios::extraerCodigo(usuarioOne,codigoOne);
                }
                //user2
                if (clicEnRectangulo(634, 605, 900, 640, x, y)) {
                    codigoTwo=0;
                    oculto = false;
                    setcolor(WHITE);
                    setbkcolor(COLOR(0x8b,0x8b,0x8b));
                    setfillstyle(SOLID_FILL,COLOR(0x8b,0x8b,0x8b));
                    escribirEnCampo(600, 605, 900, 640,usuarioTwo, 13, IndexTwo, oculto);
                    Usuarios::extraerCodigo(usuarioTwo,codigoTwo);
                }
                
                //DETECTAR CONEXION
                if (clicEnRectangulo(663, 662, 867, 693, x, y)) {
                    if(grafo.comprobarAmistad(codigoOne,codigoTwo))
                    {
                        outtextxy(970,575, (char*)"SI");
                    }else
                    {
                        outtextxy(970,575, (char*)"NO");
                    }
                }


                if(clicEnRectangulo(0,0,155,750,x,y)){return;}

            }
            delay(10);
        }
    }
    void manejarClickAmigos()
    {
        setbkcolor(WHITE);
        setcolor(BLACK);
        settextstyle(8, 0, 1);
        char usuarioOperacion[14]="";
        int IndexOne=0;
        int codigoAgg;
        int Recomendaciones[4];
        int numRecomendaciones;
        int Intereses[4];
        int Amigos[6];
        bool tipo=0;
        setbkcolor(COLOR(0xf3,0xf3,0xf3));
        grafo.obtenerAmistades(ID,Amigos);
        Usuarios::mostrarAmigos(Amigos);
        grafo.recomendarAmistades(ID,Recomendaciones,numRecomendaciones);
        Usuarios::recomendarAmigosxIntereses(UserPrincipal,Intereses, grafo);
        Usuarios::mostrarRecomendaciones(Recomendaciones,1);
        Usuarios::mostrarRecomendaciones(Intereses,0);
        while (true) 
        {
            if (ismouseclick(WM_LBUTTONDOWN)) 
            {
                getmouseclick(WM_LBUTTONDOWN, x, y);
                cout<<"X: "<<x<<" Y: "<<y<<endl;
                limpiarBufferTeclado();
            

                // agregar o eliminar 
                //ususairo
                if (clicEnRectangulo(210, 645, 470, 680, x, y)) {
                    codigoAgg=0;
                    oculto = false;
                    setcolor(BLACK);
                    setbkcolor(COLOR(0xf3,0xf3,0xf3));
                    setfillstyle(SOLID_FILL,COLOR(0xf3,0xf3,0xf3));
                    escribirEnCampo(180, 638, 470, 680,usuarioOperacion, 13, IndexOne, oculto);
                    Usuarios::extraerCodigo(usuarioOperacion,codigoAgg);
                }
                
                //AGREGAR
                if (clicEnRectangulo(505, 630, 560, 680, x, y)) {
                    if(grafo.agregarAmistad(ID,codigoAgg))
                    {
                        codigoAgg=0;
                        menu=INICIO;
                        InicioInterfaz();
                        UserPrincipal.mostrarUsuario();
                        manejarClickInicio();
                        return;
                    } else 
                    {
                        cout<<"Invalido";
                    }
                }


                //ELIMINAR
                if (clicEnRectangulo(590, 630, 645, 680, x, y)) 
                {
                     if(grafo.eliminarAmistad(ID,codigoAgg))
                    {
                        codigoAgg=0;
                        menu=INICIO;
                        InicioInterfaz();
                        UserPrincipal.mostrarUsuario();
                        manejarClickInicio();
                        return;
                    } else 
                    {
                        cout<<"invalido";
                    }
                    
                }

                if(clicEnRectangulo(0,0,155,750,x,y)){return;}

            }
            delay(10);
        }
    }
    void manejarClickBusqueda()
    {
        Usuarios perfil;
        setbkcolor(WHITE);
        setcolor(BLACK);
        settextstyle(8, 0, 1);
        char usuarioOperacion[14]="";
        int IndexOne=0;
        int idPerfil=0;
        int cantAmistades=0;
        int amigos[6];
        int numAmigos;
        int distancia=0; 
        int camino[100];
        int numNodos=0;
        string usuariosCamino[100]={""};
        
        while (true) 
        {
            if (ismouseclick(WM_LBUTTONDOWN)) 
            {
                getmouseclick(WM_LBUTTONDOWN, x, y);
                cout<<"X: "<<x<<" Y: "<<y<<endl;
                limpiarBufferTeclado();
            

                // agregar o eliminar 
                //usuARIO
                if (clicEnRectangulo(225, 130, 677, 160, x, y)) {
                    setfillstyle(SOLID_FILL,COLOR(0xf3,0xf3,0xf3));
                    bar(185,182,700,707);
                    bar(800,95,1435,690);
                    idPerfil=0;
                    oculto = false;
                    setcolor(BLACK);
                    setbkcolor(COLOR(0xf3,0xf3,0xf3));
                    setfillstyle(SOLID_FILL,COLOR(0xf3,0xf3,0xf3));
                    escribirEnCampo(180, 118, 677, 160,usuarioOperacion, 13, IndexOne, oculto);
                    Usuarios::extraerCodigo(usuarioOperacion,idPerfil);
                    perfil = Usuarios::cargarUsuario(idPerfil);
                    cantAmistades = grafo.contarAmistades(idPerfil);
                    if(idPerfil!=0){ perfil.mostrarPerfil(cantAmistades);}
                    grafo.mostrarTodosAmigos(idPerfil,amigos, numAmigos);
                    if(grafo.caminoMasCorto(ID,idPerfil,distancia,camino,numNodos))
                    {
                        int x=1000 , y=100;
                        char strUsuario[100];
                        if(numNodos==1)
                        {
                            outtextxy(x,y,(char*) "Ya son amigos");

                        } else if(numNodos>1)
                        {
                            for (int i = 0; i < numNodos; i++)
                            {
                                Usuarios::extraerUsuario(usuariosCamino[i],camino[i]);
                                strcpy(strUsuario,usuariosCamino[i].c_str());
                                outtextxy(x,y,strUsuario);
                                y+=30;
                            }

                        }
                    }
                    
                }



                if(clicEnRectangulo(0,0,155,750,x,y)){return;}

            }
            delay(10);
        }
    }
    
    void manejarClickGestion()
    {
        setbkcolor(WHITE);
        setcolor(BLACK);
        settextstyle(8, 0, 1);
        while (true) 
        {
            if (ismouseclick(WM_LBUTTONDOWN)) 
            {
                getmouseclick(WM_LBUTTONDOWN, x, y);
                cout<<"X: "<<x<<" Y: "<<y<<endl;
                limpiarBufferTeclado();
            

                //BORRAR USUARIO
                if (clicEnRectangulo(325, 310, 530, 345, x, y)) {
                    Usuarios::eliminarUsuario_Nodo(ID,grafo);\
                    menu=CERRAR_SESION;
                    return;
                }

                if(clicEnRectangulo(0,0,155,750,x,y)){return;}

            }
            delay(10);
        }
    }
    void manejarClickMensajes()
    {
        setbkcolor(WHITE);
        setcolor(BLACK);
        settextstyle(8, 0, 1);
        while (true) 
        {
            if (ismouseclick(WM_LBUTTONDOWN)) 
            {
                getmouseclick(WM_LBUTTONDOWN, x, y);
                cout<<"X: "<<x<<" Y: "<<y<<endl;
                limpiarBufferTeclado();
            

                //Escribir Mensaje
                if (clicEnRectangulo(750, 640, 1365, 700, x, y)) {

                }

                //enviar Mensaje
                if (clicEnRectangulo(1385, 640, 1440, 700, x, y)) {

                }

                if(clicEnRectangulo(0,0,155,750,x,y)){return;}

            }
            delay(10);
        }
    }

//Interfaces
    void LoginInterfaz() {
        readimagefile("Login.jpg", 0, 0, windowWidth, windowHeight);
    }
    void RegisterInterfaz()
    {
        readimagefile("Register.jpg", 0, 0, windowWidth, windowHeight);
    }
    void InteresesInterfaz()
    {
        readimagefile("Intereses.jpg", 0, 0, windowWidth, windowHeight);
    }
    void InicioInterfaz()
    {
        readimagefile("Inicio.jpg", 0, 0, windowWidth, windowHeight);
    }
    void MensajeInterfaz()
    {
        readimagefile("Mensajes.jpg", 0, 0, windowWidth, windowHeight);
    }
    void AmigosInterfaz()
    {
        readimagefile("Amigos.jpg", 0, 0, windowWidth, windowHeight);
    }
    void BusquedaInterfaz()
    {
        readimagefile("Busqueda.jpg", 0, 0, windowWidth, windowHeight);
    }
    void GestionInterfaz()
    {
        readimagefile("Gestion.jpg", 0, 0, windowWidth, windowHeight);
    }

//MANEJO DE MENU
    void manejarMenu()
    {
            //Opcion Inicio
            if (clicEnRectangulo(49, 44, 120, 120, x, y)) {menu= INICIO;}

           // Opción Mensajes
            if (clicEnRectangulo(49, 135, 120, 200, x, y)) {menu = MENSAJES;}

            // Opción Amigos
            if (clicEnRectangulo(49, 225, 120, 286, x, y)) {menu = AMIGOS;}

            // Opción Busqueda
            if (clicEnRectangulo(49, 312, 120, 384, x, y)) {menu = BUSQUEDA;}

            //OPCIOON GESTION
            if (clicEnRectangulo(49, 557, 120, 610, x, y)) {menu = GESTION;}

            //OPCIOON cERRAR SESION
            if (clicEnRectangulo(54, 644, 120, 693, x, y)) {menu = CERRAR_SESION;}

            if (ismouseclick(WM_LBUTTONDOWN)) 
            {
                getmouseclick(WM_LBUTTONDOWN, x, y);
                cout<<"X="<<x<<" Y="<<y;
            }
    }
    void dibujarMenu(Menu &estado)
    {
        if (estado!=menu) 
        {    
            switch (menu) 
            {
                case INICIO:
                    InicioInterfaz();
                    UserPrincipal.mostrarUsuario();
                    manejarClickInicio();
                    break;
                case MENSAJES: 
                    MensajeInterfaz();
                    
                    break;
                case AMIGOS: 
                    AmigosInterfaz();
                    manejarClickAmigos();
                    break;
                case BUSQUEDA:
                    BusquedaInterfaz();
                    manejarClickBusqueda();
                    break; 
                case GESTION:
                    GestionInterfaz();
                    manejarClickGestion();
                    break;
                case CERRAR_SESION:
                    break;  
            }
            estado = menu;
        }
    }

    public:
    Sistema(int width, int height) : windowWidth(width), windowHeight(height) {
        x = 0; y = 0;
        correoIndex = 0; passIndex = 0, nombreIndex=0, usuarioIndex=0;
        oculto = false;
        correo[0] = '\0';
        contrasena[0] = '\0';
        usuario[0]='\0';
        nombre[0]='\0';
    }


    void iniciarSistema() {
        int gd = DETECT, gm;
        initgraph(&gd, &gm, (char*)"");
        initwindow(windowWidth, windowHeight, "UGMA FRIENDS", 100, 100);
        int codigo;
        bool primera=false;
        grafo.cargarGrafo(); //cargar datos de grafo ID
        grafo.cargarAmistadesDesdeArchivo(); //Cargar aristas 

    while(true)
    {
        LoginInterfaz();
        manejarClickLogin();
        Menu estado=VACIO;
        primera=false;
        while(menu!=CERRAR_SESION)
        { 
            if(!primera)
            {
                primera=true;
            } else 
            {
                estado = menu;
            }
            manejarMenu();
            dibujarMenu(estado);
            delay(5);
        }

        cleardevice();
        limpiarChar(correo,19);
        limpiarChar(contrasena,19);
        correoIndex=0;
        passIndex=0;

    }
        closegraph();
    }
};


int main()
{

    Sistema ugmaFriends(1500, 750);  
    ugmaFriends.iniciarSistema();   

    return 0;
} 