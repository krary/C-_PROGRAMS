#include <windows.h>
#define CM_PRUEBA 100
#define CM_SALIR 101
#define CM_COPIAR 102
#define CM_CORTAR 103
#define CM_PEGAR 104
#define CM_ARCHIVO 105

void InsertarMenu(HWND hwnd) {
    HMENU menu1, menu2,menu3;
    
    // Crear los menús
    menu1 = CreateMenu();
    menu2 = CreateMenu();
    menu3 = CreateMenu();
    
    AppendMenu(menu3,MF_STRING,CM_COPIAR,"&copiar");
    AppendMenu(menu3,MF_SEPARATOR,0,NULL);
    
    AppendMenu(menu3,MF_STRING,CM_CORTAR,"&cortar");
    AppendMenu(menu3,MF_SEPARATOR,0,NULL);
    AppendMenu(menu3,MF_STRING,CM_PEGAR,"&pegar");
    AppendMenu(menu3,MF_SEPARATOR,0,NULL);
    AppendMenu(menu3,MF_STRING,CM_ARCHIVO,"&create file..");
    
    AppendMenu(menu2, MF_STRING, CM_PRUEBA, "&Prueba");
    AppendMenu(menu2, MF_SEPARATOR, 0, NULL);
    AppendMenu(menu2, MF_STRING, CM_SALIR, "&Salir");

    // Agregar el submenú 'menu2' al menú pri AppendMenu(menu1, MF_POPUP, (UINT_PTR)menu2, "&Principal");
    
    
    AppendMenu(menu1, MF_POPUP,(UINT_PTR)menu2, "&Folder");
    AppendMenu(menu1,MF_POPUP,(UINT_PTR)menu3,"&Herramientas");

    
    
    SetMenu(hwnd, menu1);
}

