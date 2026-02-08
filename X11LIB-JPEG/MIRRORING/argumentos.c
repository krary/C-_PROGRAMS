#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<X11/Xlib.h>
#include<X11/Xutil.h>
#include<jpeglib.h>

void maiking_JPG(XImage *image,const char* name){
  struct jpeg_compress_struct cinfo;
  struct jpeg_error_mgr err;

  cinfo.err = jpeg_std_error(&err);
  jpeg_create_compress(&cinfo);

  FILE *file = fopen(name,"wb");

  jpeg_stdio_dest(&cinfo,file);
   //CONFIGURANDO
   cinfo.image_width = image->width;
   cinfo.image_height = image->height;
   cinfo.input_components = 3; //RGB
   cinfo.in_color_space = JCS_RGB;

   jpeg_set_defaults(&cinfo);
   jpeg_set_quality(&cinfo,90,TRUE);
   jpeg_start_compress(&cinfo,TRUE);

   JSAMPROW row_poninter[1];
   int row_stride = image->width * 3;
   unsigned char *row = malloc(row_stride);
   if(!row)return;
   while(cinfo.next_scanline < cinfo.image_height){
    for(int x = 0; x< image->width;x++){
    unsigned long  pixel = XGetPixel(image,x,cinfo.next_scanline);
    row[x * 3 + 0] = (pixel & image->red_mask) >>16;
    row[x * 3 + 1] = (pixel & image->green_mask) >> 8;
    row[x * 3 + 2] = (pixel & image->blue_mask);
}
row_poninter[0] =row;
jpeg_write_scanlines(&cinfo,row_poninter,1);
   }
   free(row);
   jpeg_finish_compress(&cinfo);
   fclose(file);
   jpeg_destroy_compress(&cinfo);

}





void Lista_screen(const char *argu){
Window a_int = strtoul(argu,NULL,0);
Display *display = XOpenDisplay(NULL);


XWindowAttributes wa;
XGetWindowAttributes(display,a_int,&wa);
int width = wa.width;
int height = wa.height;


XImage *image = XGetImage(display,a_int,0,0,width,height,AllPlanes,ZPixmap);
maiking_JPG(image,"FOTO.jpg");
XDestroyImage(image);
XCloseDisplay(display);
}




void convertion(char *argv){



 char *word = argv;
  printf("El archivo que ejecutaste lleva el nombre de ...[%s]\n",word);
  char new_word[512];
  snprintf(new_word,sizeof(new_word),"%s ESTE ES EL TEXTO AÑADIDO...",word);
  printf("TEXTO AÑADIDO[%s]\n",new_word);

  char *numero = "123";
  int num = strtoul(numero,NULL,0);
  if(num){printf("El numero convertido es : [%d]\n",num);}
}

int main(int argc , char **argv){

Lista_screen(argv[1]);


return 0;
}
