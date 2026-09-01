#include "library.h"




int main(int argc,char **argv){

  if(argc != 2){
  	printf("Miss one argument..\n");
  	return 1;}

  Chip8 chip;
  init_chip(&chip);

  
  Window *window =  calloc(1,sizeof(Window));
  if(!window){printf("Cannot reserved enough memory for the struct..\n");return 1;}


init_event(window);

 if(window->window != NULL)SDL_DestroyWindow(window->window);
 if(window->render != NULL)SDL_DestroyRenderer(window->render);
 if(window->texture != NULL)SDL_DestroyTexture(window->texture);
 if(window != NULL)free(window);
 


	return 0;
}
