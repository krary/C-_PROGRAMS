#include <windows.h>
#include "Icon.h"
LRESULT CALLBACK WindowProcedures(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
            }
    return DefWindowProc(hwnd, message, wParam, lParam);
}


int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszCmdParam,int cmd){
	HWND hWnd;
	WNDCLASS WndClass = {};
	MSG Message;
	WndClass.style = CS_HREDRAW | CS_VREDRAW; //Redimensiona la vENTANA CON LAS BANDERAS HORIZ Y VERTICAL
	WndClass.lpfnWndProc = WindowProcedures;
	WndClass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH); 
    WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); 
    WndClass.hInstance = hInstance; 
    WndClass.lpszClassName = "NUESTRA_CLASE"; 
    WndClass.lpszMenuName = NULL; 
    RegisterClass(&WndClass); 
    hWnd = CreateWindow( 
      "NUESTRA_CLASE", 
      "CODIGO INFORMATICO", 
      WS_OVERLAPPEDWINDOW, 
      CW_USEDEFAULT, 
      CW_USEDEFAULT, 
      720, 
      300, 
      NULL, 
      NULL, 
      hInstance, 
      NULL 
      ); 
   InsertarMenu(hWnd);   
   ShowWindow(hWnd,cmd); 
   UpdateWindow(hWnd);
   while(TRUE == GetMessage(&Message, 0, 0, 0)) 
   { 
      TranslateMessage(&Message); 
      DispatchMessage(&Message); 
   } 
   return Message.wParam;
	
	
}

