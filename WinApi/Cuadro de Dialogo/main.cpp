#include<windows.h>
#include "Menu.h"
#define ID_BOTON1 1
LRESULT CALLBACK WindowProcedure(HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam){
switch(msg){
	case WM_COMMAND:
		switch(LOWORD(wparam)){
			case ID_BOTON1:
				MessageBox(hwnd,"pulsaste el boton de abajo","button",MB_OK);
				PostQuitMessage(0);
				break;
			case SECOND_MENU:
			  MessageBox(hwnd,"Has pulsado el boton","Evento",MB_OK);
			  PostQuitMessage(0);
			  break;
		}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd,msg,wparam,lparam);
		}
return 0;
}
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpstr,int cmd){
MSG msg;
HWND hwnd;
WNDCLASS wnd = {};
wnd.lpfnWndProc = WindowProcedure;
wnd.lpszClassName = "INFO";
wnd.hbrBackground = (HBRUSH)(COLOR_WINDOW +1);
wnd.hCursor = LoadCursor(hInstance,IDC_ARROW);
wnd.hInstance = hInstance;
RegisterClass(&wnd);
hwnd = CreateWindow("INFO","INFO",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,488,222,NULL,NULL,hInstance,NULL);
make(hwnd);
 CreateWindow(
        "BUTTON",              // Clase del control
        "Haz clic",            // Texto del botón
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Estilos
        0,140,                // Posición (x, y)
        70,20,               // Tamaño (ancho, alto)
        hwnd,                 // Ventana padre
        (HMENU)ID_BOTON1,     // ID del botón
        hInstance,
        NULL
    );
ShowWindow(hwnd,cmd);
while(TRUE == GetMessage(&msg,0,0,0)){
	TranslateMessage(&msg);
	DispatchMessage(&msg);
}
}
