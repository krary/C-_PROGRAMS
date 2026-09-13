#include "library.h"

//============================================================================
void init_window(Window *window){
    // Corrección de los 6 parámetros en su orden correcto:
    window->w = SDL_CreateWindow("EMULATOR_TEST",
                                 SDL_WINDOWPOS_CENTERED, // x
                                 SDL_WINDOWPOS_CENTERED, // y
                                 SCREEN_WIDTH * SCALE,   // width (640)
                                 SCREEN_HIGH * SCALE,    // height (320)
                                 SDL_WINDOW_SHOWN);      // flags

    window->r = SDL_CreateRenderer(window->w, -1, SDL_RENDERER_ACCELERATED);
}
//==============================================================================

//===============================================================================   
void init_draw(Window *window){
    SDL_SetRenderDrawColor(window->r, 0, 0, 0, 255);
    SDL_RenderClear(window->r);

    for(int i = 0; i < (SCREEN_WIDTH * SCREEN_HIGH); i++){
        window->pixels[i] = (window->ch->display[i] == 1) ? 0xFFFFFFFF : 0x000000FF;
    }

    SDL_UpdateTexture(window->t, NULL, window->pixels, SCREEN_WIDTH * sizeof(uint32_t));
    SDL_RenderCopy(window->r, window->t, NULL, NULL);
    SDL_RenderPresent(window->r);
}
//=================================================================================

//==================================================================================
void init_texture(Window *window){
    window->t = SDL_CreateTexture(
                window->r,
                SDL_PIXELFORMAT_RGBA8888,
                SDL_TEXTUREACCESS_STREAMING,
                SCREEN_WIDTH,
                SCREEN_HIGH);
}
//===================================================================================

//===================================================================================
void init_event(Window *window){
    init_window(window);
    init_texture(window);
    
    window->run = 1;
    SDL_Event event;
    while(window->run){
        while(SDL_PollEvent(&event)){


         switch(event.type){
                case SDL_QUIT:
                	window->run = 0;
                	break;
         		case SDL_KEYDOWN:
         			int index_keypad = map_sdl_key_to_chip8(event.key.keysym.sym);
                    if(index_keypad !=-1){
         			window->ch->keypad[index_keypad] = 1;}
         			break;
         		case SDL_KEYUP:
         			index_keypad = map_sdl_key_to_chip8(event.key.keysym.sym);
         			if(index_keypad != -1){
         			window->ch->keypad[index_keypad] = 0;}
         			break;	
         }   
            }
        

        for (int i = 0; i < 10; i++) {
            if (window->ch->pc < 4096) {
                init_chip8_cycle(window->ch);
            }
        }
        
        if (window->ch->delay_timer > 0) window->ch->delay_timer--;
        if (window->ch->delay_sound > 0) window->ch->delay_sound--;

        init_draw(window);
        SDL_Delay(16);
    }
}
//====================================================================================


//===================================================================================
int map_sdl_key_to_chip8(SDL_Keycode key) {
    switch (key) {
        case SDLK_1: return 0x1;
        case SDLK_2: return 0x2;
        case SDLK_3: return 0x3;
        case SDLK_4: return 0xC;

        case SDLK_q: return 0x4;
        case SDLK_w: return 0x5;
        case SDLK_e: return 0x6;
        case SDLK_r: return 0xD;

        case SDLK_a: return 0x7;
        case SDLK_s: return 0x8;
        case SDLK_d: return 0x9;
        case SDLK_f: return 0xE;

        case SDLK_z: return 0xA;
        case SDLK_x: return 0x0;
        case SDLK_c: return 0xB;
        case SDLK_v: return 0xF;

        default: return -1; // Tecla no asignada
    }
}
//=======================================================================================
