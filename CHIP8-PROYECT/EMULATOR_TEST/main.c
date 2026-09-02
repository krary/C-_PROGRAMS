#include "library.h"

int main(){
Chip8 *chip = malloc(sizeof(Chip8));
     making_sprites();  //CREA EL ARCHIVO DE LOS BYTES DE PIXELES
     init_chip(chip);   //INICIA UN PUNTERO DE CHIP CONFIGURANDO EL PUNTERO DE CHIP PC HACIA LA DIRECCION DE 0X200
     init_load_rom(chip,"square.ch8"); //CARGA LA ROM DENTRO DE EL BUFFER DE CHIP ES DECIR chip->rom


    while (chip->pc < 4096) {
             init_chip8_cycle(chip);
             usleep(1200); // Pequeña pausa (~800Hz) para controlar la velocidad
         } 





    if(chip != NULL)free(chip);
	return 0;
}
