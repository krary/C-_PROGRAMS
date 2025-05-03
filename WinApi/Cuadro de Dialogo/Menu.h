#include<windows.h>
#define SECOND_MENU 101
void make(HWND hwnd){
	HMENU menu1,menu2;
	menu1 = CreateMenu();
	menu2 = CreateMenu();
	AppendMenu(menu2,MF_STRING,SECOND_MENU,"&Mensaje...");
	AppendMenu(menu2,MF_SEPARATOR,0,NULL);
	AppendMenu(menu1,MF_POPUP,(UINT_PTR)menu2,"&Box..");
	SetMenu(hwnd,menu1);
	
}
