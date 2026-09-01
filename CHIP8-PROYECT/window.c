#include "library.h"

uint8_t chip8_fontset[80] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};
void init_event(Window *w,Chip8 *ch){
	init_window(w);
	int run = 1;

    uint32_t pixels[SCREEN_WIDTH*SCREEN_HIGH];
    uint32_t last_time = SDL_GetTicks();
   
  
    
	SDL_Event event;
	while(run){
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT)run = 0;
			if(event.type == SDL_KEYDOWN){
				switch(event.key.keysym.sym){
					case SDLK_q:
						run = 0;}}

		}
	for(int i = 0; i<10;i++){init_chip8_cycle(ch);}
	uint32_t current_time = SDL_GetTicks();
	if(current_time - last_time >= 16){
		if(ch->delay_timer > 0)ch->delay_timer--;
		if(ch->delay_sound >0)ch->delay_sound--;
		last_time = current_time;}

		//CONVERSION DE PANTALLAR MONOCROMATICO A PIXELES DE COLORES
		for(int i = 0; i <(SCREEN_WIDTH*SCREEN_HIGH);i++){
			pixels[i] = (ch->display[i] == 1) ? 0xFFFFFFFF : 0x000000FF;}
		SDL_UpdateTexture(w->texture, NULL, pixels, SCREEN_WIDTH * sizeof(uint32_t));
        init_draw(w);
        SDL_Delay(16);
	}
}
void init_window(Window *w){
w->window = SDL_CreateWindow("CHIP8 Emulator",
		SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH*SCALE,SCREEN_HIGH*SCALE,SDL_WINDOW_SHOWN);
w->render = SDL_CreateRenderer(w->window,-1,SDL_RENDERER_ACCELERATED);

w->texture = SDL_CreateTexture(w->render,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH,
		SCREEN_HIGH	);
}


void init_draw(Window *w){
	SDL_SetRenderDrawColor(w->render,0,0,0,255);
    SDL_RenderClear(w->render);
    //AQUI SE DIBUJA


    SDL_RenderPresent(w->render);}
    
