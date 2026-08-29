#include "library.h"


void init_chip(Chip8 *ch){
	*ch = (Chip8){0};
	 ch->pc = 0x200;}

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
uint8_t x = (opcode & 0x0f00)>>8;
uint8_t y = (opcode & 0x00f0)>>4;
uint8_t n = (opcode & 0x000f);
uint8_t kk = (opcode & 0x00ff);
uint8_t nnn = (opcode & 0x0fff);

switch(opcode &0xf000){
	case 0x0000:
	if(opcode == 0x0E00){
memset(ch->display,0,sizeof(ch->display));}
    else if(opcode == 0x00EE){//CALL RETURN
    	ch->sp--;
    	ch->pc = ch->stack[ch->sp];}
    break;
    case 0x1000:
        ch->pc = nnn;
        break; 
     case 0x6000:
        ch->V[x]=kk;
        break;
 	}
}
