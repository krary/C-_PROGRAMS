#include<windows.h>
#include "menus.h"
#include<cstring>
LRESULT CALLBACK WindowProcedure(HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam){
	const char* mensaje = "Hello World";
	switch(msg){
		case WM_PAINT:{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);
			SetTextColor(hdc,RGB(0,0,255));
			TextOut(hdc,50,10,mensaje,strlen(mensaje));
			EndPaint(hwnd,&ps);
			break;
		}
		case WM_COMMAND:
			switch(LOWORD(wparam)){
				case MIN:
					MessageBox(hwnd,"has pulsado el menu de minimizar...","mensaje",MB_OK);
				
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
	WNDCLASS wndclass = {};
	
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WindowProcedure;
	wndclass.lpszClassName = "Vectores";
	wndclass.hCursor = LoadCursor(hInstance,IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW +1);
	wndclass.hInstance = hInstance;
	RegisterClass(&wndclass);
	hwnd = CreateWindowEx(
	0,
	"Vectores",
	"Vectores",
	WS_OVERLAPPEDWINDOW,
	CW_USEDEFAULT,
	CW_USEDEFAULT,
	CW_USEDEFAULT,
	CW_USEDEFAULT,
	NULL,
	NULL,
	hInstance,
	NULL
	);
	menu(hwnd);
	ShowWindow(hwnd,cmd);
	while(GetMessage(&msg,0,NULL,NULL)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
