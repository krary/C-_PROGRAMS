#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <ID_VENTANA>\n", argv[0]);
        return 1;
    }

    Window target_win = strtoul(argv[1], NULL, 0);
    Display *display = XOpenDisplay(NULL);
    if (!display) return 1;

    XWindowAttributes wa;
    if (XGetWindowAttributes(display, target_win, &wa) == 0) {
        fprintf(stderr, "Error: ID de ventana inválido.\n");
        XCloseDisplay(display);
        return 1;
    }

    Window root = DefaultRootWindow(display);

    // --- SOLUCIÓN AL BADMATCH ---
    // Definimos los atributos necesarios para que coincidan con el Visual del objetivo
    XSetWindowAttributes swa;
    swa.colormap = XCreateColormap(display, root, wa.visual, AllocNone);
    swa.border_pixel = 0;
    swa.background_pixel = 0;
    
    // Máscara que indica qué atributos estamos enviando
    unsigned long mask = CWColormap | CWBorderPixel | CWBackPixel;

    // Crear la ventana con XCreateWindow usando la máscara de atributos
    Window win = XCreateWindow(display, root, 0, 0, 
                               800, 600, 0, // Tamaño inicial
                               wa.depth, InputOutput, wa.visual, 
                               mask, &swa);

    XStoreName(display, win, "Espejo Estable");

    Atom wmDeleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(display, win, &wmDeleteMessage, 1);
    
    XSelectInput(display, win, ExposureMask | KeyPressMask);
    XMapWindow(display, win);
    GC gc = XCreateGC(display, win, 0, NULL);

    XEvent event;
    int running = 1;
    while (running) {
        while (XPending(display)) {
            XNextEvent(display, &event);
            if (event.type == ClientMessage && event.xclient.data.l[0] == wmDeleteMessage) running = 0;
            if (event.type == KeyPress && event.xkey.keycode == 9) running = 0;
        }

        // Capturar
        XImage *image = XGetImage(display, target_win, 0, 0, wa.width, wa.height, AllPlanes, ZPixmap);
        
        if (image) {
            // Ajustar el dibujo al tamaño de nuestra ventana si es necesario
            // Por ahora lo enviamos directo (XPutImage no escala)
            XPutImage(display, win, gc, image, 0, 0, 0, 0, wa.width, wa.height);
            XDestroyImage(image);
        }
        usleep(40000);
    }

    XFreeColormap(display, swa.colormap);
    XFreeGC(display, gc);
    XDestroyWindow(display, win);
    XCloseDisplay(display);
    return 0;
}
