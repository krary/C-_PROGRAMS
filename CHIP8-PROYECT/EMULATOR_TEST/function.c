#include "library.h"
//THIS IS JUST A COMMENT

void init_chip(Chip8 *ch){
	*ch = (Chip8){0};
	 ch->pc = 0x200;

     memcpy(&ch->ram[FONT_SET_START_ADDRESS],chip8_fontset,sizeof(chip8_fontset));}

void init_load_rom(Chip8 *ch,const char *filename){
	FILE *f = fopen(filename,"rb");
	if(!f){printf("Cannot acces to the file");return;}

    fseek(f,0,SEEK_END);
    long size = ftell(f);
    fseek(f,0,SEEK_SET);
    if(size > (4096 - 0x200)){
    	printf("The file is bigger\n");
    	fclose(f);
    	return;}
size_t bytes_copies = fread(&ch->ram[0x200],1,size,f);
if(bytes_copies != (size_t)size){
	printf("THERE IS NOT COINCIDENT IN SIZES\n");
	fclose(f);}
printf("ROM LOADED SUCCESSFULLY\n");
if(f)fclose(f);}


void init_chip8_cycle(Chip8 *ch){
uint16_t opcode = (ch->ram[ch->pc] << 8) 
| ch->ram[ch->pc+1];
ch->pc +=2;
uint8_t x = (opcode & 0x0f00)>>8;
uint8_t y = (opcode & 0x00f0)>>4;
uint8_t n = (opcode & 0x000f);
uint8_t kk = (opcode & 0x00ff);
uint16_t nnn = (opcode & 0x0fff);

switch(opcode &0xf000){
    case 0xF000:{
    	switch(kk){
    		case 0x07:
    			ch->V[x]=ch->delay_timer;
    			break;
    		case 0x15:
    			ch->delay_timer = ch->V[x];
    			break;
    		case 0x18:
    			ch->delay_sound = ch->V[x];
    			break;
    		case 0x1E:
    			ch->I +=ch->V[x];
    			break;
    		case 0x29:
    			ch->I = FONT_SET_START_ADDRESS + (ch->V[x] * 5);
    			break;
    		case 0x33:
    			ch->ram[ch->I] = ch->V[x] / 100;
    			ch->ram[ch->I + 1] = (ch->V[x] / 10) %10;
    			ch->ram[ch->I +2] = ch->V[x] % 10;
    			break;
    		case 0x55:
    			for(int i = 0; i<= x; i++){
    				ch->ram[ch->I +i] = ch->V[i];}
    			break;
    		case 0x65:
    			for(int i = 0; i<= x; i++){
    				ch->V[i] = ch->ram[ch->I + i];}
    			break;
    		default:
    			printf("[0x%04X] UKNOWN INSTRUCTION\n",opcode);
    		
    	}
    	break;
    }
    case 0xD000:{
    	uint8_t x_pos = ch->V[x] % 64;
    	uint8_t y_pos = ch->V[y] % 32;
    	ch->V[0xF]=0;
    	for(uint8_t row = 0; row < n; row++){
    		uint8_t sprite_byte = ch->ram[ch->I + row];
    		for(uint8_t col = 0; col < 8;col++){
    		
    			uint8_t sprite_pixel = sprite_byte &(0x80 >> col);

    			if(sprite_pixel != 0){
    				uint16_t screen_x = (x_pos + col) % 64;
    				uint16_t screen_y = (y_pos + row) % 32;
    				uint16_t index = screen_y * 64 + screen_x;
    			    if(ch->display[index] == 1){ch->V[0XF]=1;}
    			    ch->display[index] ^= 1;	
    			}
    		}
    	}
    	break;
    }
	case 0x0000:
	if(opcode == 0x00E0){
memset(ch->display,0,sizeof(ch->display));}
    else if(opcode == 0x00EE){//CALL RETURN
    	ch->sp--;
    	ch->pc = ch->stack[ch->sp];}
    break;
    case 0x1000://SALTO INCONDICIONAL A NNN:
        ch->pc = nnn;
        break; 
     case 0x2000:
        ch->stack[ch->sp]= ch->pc;
        ch->sp++;
        ch->pc = nnn;
        break;
     case 0x3000:
        if(ch->V[x]==kk){ch->pc +=2;}
        break;
     case 0x4000:
        if(ch->V[x] != kk){ch->pc+=2;}
        break;
     case 0x5000: // 5XY0: SE Vx, Vy (Salto si Vx == Vy)
         if (ch->V[x] == ch->V[y]) {
             ch->pc += 2;}
         break;
     case 0x6000: //CREAR UN VALOR EN EL REGISTRO V[X]: kk
        ch->V[x]=kk;
        break;
     case 0x7000: //SUMAR UN VALOR EN EL REGISTRO V[x]: kk
        ch->V[x] += kk;
        break;
     case 0x8000:
         switch(n) {
             case 0x0: ch->V[x] = ch->V[y]; break;
             case 0x1: ch->V[x] |= ch->V[y]; break;
             case 0x2: ch->V[x] &= ch->V[y]; break;
             case 0x3: ch->V[x] ^= ch->V[y]; break;
             case 0x4: {
                 uint16_t sum = ch->V[x] + ch->V[y];
                 ch->V[0xF] = (sum > 255) ? 1 : 0;
                 ch->V[x] = sum & 0xFF;
                 break;
             }
             case 0x5: {
                 ch->V[0xF] = (ch->V[x] >= ch->V[y]) ? 1 : 0;
                 ch->V[x] -= ch->V[y];
                 break;
             }
             case 0x6: {
                 ch->V[0xF] = ch->V[x] & 0x1;
                 ch->V[x] >>= 1;
                 break;
             }
             case 0x7: { // Opcional: Si tu ROM usa este sub-opcode (Vy - Vx)
                 ch->V[0xF] = (ch->V[y] >= ch->V[x]) ? 1 : 0;
                 ch->V[x] = ch->V[y] - ch->V[x];
                 break;
             }
             case 0xE: {
                 ch->V[0xF] = (ch->V[x] & 0x80) >> 7;
                 ch->V[x] <<= 1;
                 break;
             }
             default:
                 printf("[0x%04X] UNKNOWN 0x8000 INSTRUCTION\n", opcode);
                 break;
         }
         break;
     case 0x9000: // 9XY0: Salta si V[x] != V[y]
         if (n == 0x0) {
             if (ch->V[x] != ch->V[y]) {
                 ch->pc += 2;}}
         break;
     case 0xA000:
        ch->I = nnn;
        break;
     default:
        printf("OPCODE UKNOWN : 0X%04X\n",opcode);
        break;
 	}
}
