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
uint8_t rom_[512]={0};



void draw_terminal(Chip8 *ch){
    int x = 0;
    int y = 0;
	for( y = 0; y < 32;y++){
		for(x = 0; x < 64; x++ ){
			if(ch->display[y*64 + x]){
				//printf("██");
				printf("*");
				}
			else{
				printf(" ");
			}
		}
		printf("\n");
	}
	printf("VALUE: 0x%02X",ch->V[1]);
}
void making_sprites(){
   // Sprite comienza en rom[256] 8 BYTES
        rom_[0]=0x60;
        rom_[1]=0x03;  //INSTRUCCION LD V0
        
        rom_[2]	=0x61;
        rom_[3]	=0x05;  //INSTRUCCION LD V1
        
        rom_[4]	=0xA3;
        rom_[5]	=0x00; //INSTRUCCION LD I [INDICE DONDE SE ENCUENTRAN LOS BYTES QUE VAMOS A DIBUJAR]
        
        rom_[6]	=0xD0; //INSTRUCCION DXYN 

        rom_[7]	=0x11;

//************************************************
        rom_[8] =  0x70; //INSTRUCCION 7XKK SUMA AL REGISTRO VX EL ULTIMO BITE CAMBIANDO LAS COORDENADAS
        rom_[9] =  0x08;

        rom_[10] = 0xD0; 
        rom_[11] = 0x11;
//************************************************************************      
//===============SEGUNDA LINEA HORIZONTAL=====================================
        
        rom_[12] = 0xA3;
        rom_[13] = 0x00;

 		rom_[14] = 0x70;
 		rom_[15] = 0xF8;

 		rom_[16] = 0x61;
 		rom_[17] = 0xF0;

 		rom_[18] = 0xD0;
 		rom_[19] = 0x11;

 		rom_[20] = 0x70;
 		rom_[21] = 0x08;

 		rom_[22] = 0xD0;
 		rom_[23] = 0x11;
//*************************************************************************
//===============DIBUJANDO LAS LINEAS VERTICALES===============================
        rom_[24] = 0x60;
        rom_[25] = 0x03;

        rom_[26] = 0x61;
        rom_[27] = 0x06;

        rom_[28] = 0xA3;
        rom_[29] = 0x01;

        rom_[30] = 0xD0;
        rom_[31] = 0x14;

        rom_[32] = 0x61;
        rom_[33] = 0x0A;

        rom_[34] = 0xA3;
        rom_[35] = 0x01;
        rom_[36] = 0xD0; 
        rom_[37] = 0x16; 
//******************************************
        rom_[38] = 0x61;
        rom_[39] = 0x06;

        rom_[40] = 0x60;
        rom_[41] = 0x12;
        

        rom_[42] = 0xD0;
        rom_[43] = 0x14;

        rom_[44] = 0x61;
        rom_[45] = 0x0A;

        rom_[46] = 0xD0;
        rom_[47] = 0x16;
//==========================================
//******************************************

//=============DIBUJANDO EL PERSONAJE====================
       rom_[48] = 0xA3;
       rom_[49] = 0x54;

       rom_[50] = 0x61;
       rom_[51] = 0x0A;

       rom_[52] = 0x60;
       rom_[53] = 0x0A;

       rom_[54] = 0xD0;
       rom_[55] = 0x11;
       




//SPRITE DE EL MARCO:
   	    rom_[256] = 0xFF;
        rom_[257] = 0x80;
   	    rom_[258] = 0x80;
   	    rom_[259] = 0x80;
   	    rom_[260] = 0x80;
   	    rom_[261] = 0x80;
   	    rom_[262] = 0x80;    	    
   	    rom_[263] = 0x80;    	    
   	    rom_[264] = 0x80;    	    
   	    rom_[265] = 0x80;    
   	    rom_[266] = 0x80;    
   	    rom_[267] = 0x80;    
   	    	    
   	    
//SPRITE DE EL PERSONAJE:
        rom_[340] = 0x80;
        rom_[341] = 0xF0; 
        rom_[342] = 0xF0; 
        rom_[343] = 0xF0;
   	    
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
