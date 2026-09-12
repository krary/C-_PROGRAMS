#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<stdbool.h>
#include<stdint.h>
#include<termios.h>
#include<SDL2/SDL.h>
#ifndef LIBRARY_H
#define LIBRARY_H
#define SCREEN_WIDTH 64
#define SCREEN_HIGH 32
#define SCALE 10

#define FONT_SET_START_ADDRESS 0X50
typedef struct{
	uint8_t ram[4096];
//CARGA DE MEMORIA DE TODO EL BITCODE DE EL ARCHIVO A PARTIR DE 0X200
	uint8_t V[16];
	uint16_t I;
	uint16_t pc; 

//PC ES 16BITS PORQUE LAS INSTRUCCIOMES SON DE 16 BITS

	uint16_t stack[16];
	uint8_t sp;

	uint8_t delay_timer;
	uint8_t delay_sound;

	uint8_t display[64 * 32];
	uint8_t keypad[16];
}Chip8;
typedef struct{
	SDL_Window *w;
	SDL_Renderer *r;
	SDL_Texture *t;
	SDL_Surface *s;
	SDL_Rect re;
	int run;
	Chip8 *ch;
	uint32_t pixels[SCREEN_WIDTH*SCREEN_HIGH];
}Window;



typedef struct{
	void(*get_old_config)(struct termios *);
	void(*get_new_config)(struct termios *,struct termios *);
	void(*take_back)(struct termios *);
}Stdin_fileno;
extern uint8_t chip8_fontset[80];
void init_event(Window*);
void init_window(Window*);
void init_draw(Window*);
void init_texture(Window*);
void init_chip(Chip8 *);
void init_load_rom(Chip8*,const char *);
void init_chip8_cycle(Chip8 *);
void making_sprites();
void draw_terminal(Chip8*);
void get_old_config(struct termios*);
void get_new_config(struct termios*,struct termios*);
void take_back(struct termios *);
void writing_keypad(Chip8 *);
bool get_fd_set_config();
int getting_char(char);


#endif
