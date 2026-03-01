#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<stdint.h>
#include "config_datos.h"
#ifndef SHOWING_DATA_H
#define SHOWING_DATA_H

void showing_data(Info_base *i){
	if(!i)return;
  for(int x = 0; x < 512;x++){
  
  printf("%02X ",i->arr_global[x]);
  if((x +1) % 16 == 0)printf("\n");
  }

}


void showing_string(Info_base *b){

  b->arr_global_folder = calloc(512,sizeof(uint8_t));
  memcpy(b->arr_global_folder,b->arr_global,512);
  for(int x = 0;x<16;x++ ){
  if((x+1) %32 == 0)printf("\n");

uint8_t *byte = &b->arr_global_folder[x*32];

  if(byte[0] == 0x00)break;
  if(byte[0] == 0xE5)continue;
  if(byte[11] == 0x0F)continue;
  for(int j = 0; j < 8; j++){
   if(byte[j] != ' ')printf("%c",byte[j]);}
  if(!(byte[11] & 0x10)){
     printf(".");
    for(int j = 8; j < 11;j++)printf("%c",byte[j]);


  }else{printf("/");}
    printf("\n");

}

 	

}
	
	void provisional(Info_base *i,const char *ele){
		
		
		for(int x = 0; x < 512;x++){
			int pos =0;
			uint8_t *byte = &i->arr_global_folder[x*32];
			if(byte[0] == 0x00)break;
			if(byte[0] == 0xE5)continue;
			if(byte[11] == 0x0F)continue;
			uint8_t *el_s = calloc(25,sizeof(uint8_t));
			for(int j = 0; j < 8; j++){
				if(byte[j] != ' '){
					el_s[pos++] = byte[j];
					printf("%02X ",el_s[j]);
					}
				}
				
				
				if(!(byte[11] & 0x10)){
				
					el_s[pos++] = '.';
						printf("%02X ",el_s[8]);
					
					for(int j = 8 ; j < 11; j++){
						
						el_s[pos++] = byte[j];
							printf("%02X ",el_s[j++]);
						}
					}
					else{el_s[pos++] = '/';	printf("%02X ",el_s[8]); }
					printf("[");
					for(int m = 0; ele[m] != '\0';m++){
							printf("%02X ",ele[m]);
						}
						printf("]");
						el_s[pos] = '\0';
                    if(strcmp(ele,el_s)==0){printf(" ***Match encontrado...***");}
                    
                    printf("\n");}
                    
                    
		
		}
	
	
	
	
#endif
