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
uint8_t rom_[264]={0};



void draw_terminal(Chip8 *ch){
    int x = 0;
    int y = 0;
	for( y = 0; y < 32;y++){
		for(x = 0; x < 64; x++ ){
			if(ch->display[y*64 + x]){
				printf("██");}
			else{
				printf("  ");
			}
		}
		printf("\n");
	}
}
void making_sprites(){
   // Sprite comienza en rom[256] 8 BYTES
        rom_[0]=0x60;
        rom_[1]=0x03;  //INSTRUCCION LD V0
        
        rom_[2]	=0x61;
        rom_[3]	=0x05;  //INSTRUCCION LD V1
        
        rom_[4]	=0xA3;
        rom_[5]	=0x00; //INSTRUCCION LD I [INDICE DONDE SE ENCUETRAN LOS BYTES QUE VAMOS A DIBUJAR]
        
        rom_[6]	=0xD0; //INSTRUCCION DXYN 
        rom_[7]	=0x15;

        
  //************************************************************************      
   	    rom_[256] = 0xFF;
   	    rom_[257] = 0x80;
   	    rom_[258] = 0x80;
   	    rom_[259] = 0x80;
   	    
   	    rom_[260] = 0xFF;
  //************************************************************************
  FILE *f = fopen("square.ch8","wb");
  if(!f){
  	printf("The file couldnt create ..\n");
  	return;}
   fwrite(rom_,1,sizeof(rom_),f);
   printf("The file was created succesfully...\n");

   if(f != NULL)fclose(f);}



void bit_bit(size_t tam,uint8_t *arr){
	uint8_t elementos[tam* 8];
	for(int x = 0; x < (int)tam*8;x++) {
		
	}
}
