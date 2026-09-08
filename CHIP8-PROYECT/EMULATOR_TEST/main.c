#include "library.h"
struct termios old,new;

int main(){
//========================================================================
Stdin_fileno *std_fileno = calloc(1,sizeof(Stdin_fileno));
std_fileno->get_old_config = get_old_config;
std_fileno->get_new_config = get_new_config;
std_fileno->take_back = take_back;
//========================================================================




//========================================================================
Chip8 *chip = malloc(sizeof(Chip8));
     making_sprites();  //CREA EL ARCHIVO DE LOS BYTES DE PIXELES
     init_chip(chip);   //INICIA UN PUNTERO DE CHIP CONFIGURANDO EL PUNTERO DE CHIP PC HACIA LA DIRECCION DE 0X200
     init_load_rom(chip,"square.ch8"); //CARGA LA ROM DENTRO DE EL BUFFER DE CHIP ES DECIR chip->rom
//=================================================================================================================



     get_old_config(&old);
     get_new_config(&new,&old);
    


//=========================================================================
    while (chip->pc < 4096) {
             writing_keypad(chip);
             init_chip8_cycle(chip);
             
             usleep(1200); // Pequeña pausa (~800Hz) para controlar la velocidad
         } 
//========================================================================================








//==========================================================================
    if(chip != NULL)free(chip);
    if(std_fileno != NULL)free(std_fileno);
    take_back(&old);
//=====================================================================================
	return 0;
}
