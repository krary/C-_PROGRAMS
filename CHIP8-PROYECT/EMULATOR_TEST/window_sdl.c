#include "library.h"

//============================================================================
void init_window(Window *window){

	window->w = SDL_CreateWindow("EMULATOR_TEST",
	                             SDL_WINDOWPOS_CENTERED,
	                             SCREEN_WIDTH *SCALE ,SCREEN_HIGH * SCALE,
	                             SDL_WINDOWPOS_CENTERED,
	                             SDL_WINDOW_SHOWN);
    window->r = SDL_CreateRenderer(window->w,-1,SDL_RENDERER_ACCELERATED);}
//==============================================================================




//===============================================================================   
void init_draw(Window *window){
	SDL_SetRenderDrawColor(window->r,0,0,0,255);
    SDL_RenderClear(window->r);
    for(int i = 0; i< (SCREEN_WIDTH*SCREEN_HIGH);i++){
    	window->pixels[i] = (window->ch->display[i] == 1)?0xFFFFFFFF:0X000000FF;}
    	SDL_UpdateTexture(window->t,NULL,window->pixels,SCREEN_WIDTH*sizeof(uint32_t));
    
    SDL_RenderPresent(window->r);}
//=================================================================================




//==================================================================================
void init_texture(Window *window){

    window->t = SDL_CreateTexture(
    			window->r,
    			SDL_PIXELFORMAT_RGB888,
    			SDL_TEXTUREACCESS_STREAMING,
    			SCREEN_WIDTH,
    			SCREEN_HIGH);}
//===================================================================================



//===================================================================================
void init_event(Window *window){
    
	init_window(window);
	init_texture(window);
	
	window->run = 1;
	SDL_Event event;
	while(window->run){
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT)window->run = 0;
			if(event.type == SDL_KEYDOWN){
				switch(event.key.keysym.sym){
					case SDLK_q:
						window->run = 0;
				}
			}
		}
        init_draw(window);
		SDL_Delay(16);
	}
	
}
//====================================================================================
