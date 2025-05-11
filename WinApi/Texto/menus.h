#include<windows.h>
#define DINAMICA 100
#define CONTROL 101
#define MAX 102
#define MIN 103
#define CREAR 104
#define GUARDAR 105
#define DISENO 106
#define FORMATO 107




void menu(HWND hwnd){
  HMENU menu1,menu2,menu3,menu4;
  menu1 = CreateMenu();
  menu2 = CreateMenu();
  menu3 = CreateMenu();
  menu4 = CreateMenu();
  
  AppendMenu(menu2,MF_STRING,CREAR,"&Crear");  
  AppendMenu(menu2,MF_STRING,GUARDAR,"&Guardar");
  AppendMenu(menu3,MF_STRING,MAX,"&Maximizar..");
  AppendMenu(menu3,MF_STRING,MIN,"&Minimizar..");
  AppendMenu(menu4,MF_STRING,DISENO,"&Disigne");
  AppendMenu(menu4,MF_STRING,FORMATO,"&Formato");
  
  AppendMenu(menu1,MF_POPUP,(UINT_PTR)menu2,"&Archivos");
  AppendMenu(menu1,MF_POPUP,(UINT_PTR)menu3,"&Ventana");
  AppendMenu(menu1,MF_POPUP,(UINT_PTR)menu4,"&Herramientas");
  AppendMenu(menu1,MF_POPUP,NULL,"&Preferencias");
  
  SetMenu(hwnd,menu1);
  
}
