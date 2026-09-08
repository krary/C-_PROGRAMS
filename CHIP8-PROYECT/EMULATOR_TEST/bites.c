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

// ================= DIBUJO INICIAL DEL PERSONAJE =================
rom_[48] = 0xA3; rom_[49] = 0x54; // LD I, 0x0354 (Sprite del personaje)
rom_[50] = 0x60; rom_[51] = 0x0A; // LD V0, 10 (X inicial)
rom_[52] = 0x61; rom_[53] = 0x0A; // LD V1, 10 (Y inicial)
rom_[54] = 0xD0; rom_[55] = 0x14; // DRW V0, V1, 4 (Dibuja personaje inicial)

// ================= BUCLE PRINCIPAL (Dirección 0x0238 / Byte 56) =================
// 1. Cargar el puntero I y BORRAR el personaje en la posición actual (XOR)
rom_[56] = 0xA3; rom_[57] = 0x54; // LD I, 0x0354
rom_[58] = 0xD0; rom_[59] = 0x14; // DRW V0, V1, 4 (Borra sprite anterior)

// 2. TECLA IZQUIERDA (Tecla 4)
rom_[60] = 0x62; rom_[61] = 0x04; // LD V2, 4
rom_[62] = 0xE2; rom_[63] = 0xA1; // SKNP V2 (Si NO se pulsa 4, salta el ADD)
rom_[64] = 0x70; rom_[65] = 0xFF; // ADD V0, -1

// 3. TECLA DERECHA (Tecla 6)
rom_[66] = 0x62; rom_[67] = 0x06; // LD V2, 6
rom_[68] = 0xE2; rom_[69] = 0xA1; // SKNP V2
rom_[70] = 0x70; rom_[71] = 0x01; // ADD V0, 1

// 4. TECLA ARRIBA (Tecla 2)
rom_[72] = 0x62; rom_[73] = 0x02; // LD V2, 2
rom_[74] = 0xE2; rom_[75] = 0xA1; // SKNP V2
rom_[76] = 0x71; rom_[77] = 0xFF; // ADD V1, -1

// 5. TECLA ABAJO (Tecla 8)
rom_[78] = 0x62; rom_[79] = 0x08; // LD V2, 8
rom_[80] = 0xE2; rom_[81] = 0xA1; // SKNP V2
rom_[82] = 0x71; rom_[83] = 0x01; // ADD V1, 1

// 6. REDIBUJAR EN NUEVA POSICIÓN
rom_[84] = 0xD0; rom_[85] = 0x14; // DRW V0, V1, 4 (Pinta sprite en nuevas X,Y)

// 7. VOLVER AL INICIO DEL BUCLE (Byte 56 = 0x0238)
rom_[86] = 0x12; rom_[87] = 0x38; // JP 0x0238      
      
         
       




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



void get_old_config(struct termios *o){
		tcgetattr(STDIN_FILENO,o);	}
void get_new_config(struct termios *n ,struct termios *o){
	    *n = *o;
	    n->c_lflag &= ~(ICANON | ECHO);
	    tcsetattr(STDIN_FILENO,TCSANOW,n);}
void take_back(struct termios *o){
        tcsetattr(STDIN_FILENO,TCSANOW,o);}
bool get_fd_set_config(){
	fd_set fd;
	FD_ZERO(&fd);
    FD_SET(STDIN_FILENO,&fd);
	struct timeval tv = {0,0};
	int state = select(STDIN_FILENO + 1,&fd,NULL,NULL,&tv);
	return (state > 0);}

int getting_char(char c){
	switch(c){
				case '1': return 0x1; case '2': return 0x2; case '3': return 0x3; case '4': return 0xC;
				        case 'q': return 0x4; case 'w': return 0x5; case 'e': return 0x6; case 'r': return 0xD;
				        case 'a': return 0x7; case 's': return 0x8; case 'd': return 0x9; case 'f': return 0xE;
				        case 'z': return 0xA; case 'x': return 0x0; case 'c': return 0xB; case 'v': return 0xF;
				        default: return -1;}}

void writing_keypad(Chip8 *ch){
	for(int x = 0; x <16;++x) {
		ch->keypad[x] = 0;}

	while((get_fd_set_config())){
		char c = getchar();
		int indice = getting_char(c);
		if(indice != -1){
			ch->keypad[indice] = 1;
		}
	}
}
