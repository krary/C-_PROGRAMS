#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<stdbool.h>
#include<stdint.h>
#ifndef LIBRARY_H
#define LIBRARY_H

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


void init_chip(Chip8 *);



#endif
