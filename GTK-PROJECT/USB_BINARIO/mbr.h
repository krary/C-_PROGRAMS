#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include "config_datos.h"
#ifndef MBR_H
#define MBR_H

Info_base *mbr_h(char *dev){
	Info_base *info_base = calloc(1,sizeof(Info_base));
	if(!info_base){printf("Info_base no puedo reservar memoria\n");
		return NULL;}
	info_base->fd = open(dev,O_RDONLY);
	if(info_base->fd < 0){
		free(info_base);
		printf("Error en info_base->fd...\n");
		return NULL; }
	
	info_base->r = read(info_base->fd,info_base->arr_global,512);
	if(info_base->r != 512){
		printf("El tamaño de los bytes [512] no coincide...\n");
		close(info_base->fd);
		free(info_base);
		return NULL;}
	memcpy(&info_base->lba_partition,info_base->arr_global + (446 + 8),4);
	
	return info_base;
}
void jump_lba(Info_base *i){
	
	if(i->r == 512){
     lseek(i->fd,i->lba_partition * 512,SEEK_SET);
     read(i->fd,i->arr_global,512);	
     memcpy(&i->cluster_num,i->arr_global + 44,4);
     memcpy(&i->sectors_saved,i->arr_global + 14,2);
     memcpy(&i->fat_num,i->arr_global + 16,1);
     memcpy(&i->sectors_por_fat,i->arr_global + 36,4);
     memcpy(&i->sectors_por_cluster,i->arr_global + 10,1);
     memcpy(&i->bytes_por_sectors,i->arr_global + 11,2);	
		}
	
	
	}
	
	void jump_regiondata(Info_base *i){
		
		uint64_t r_ = i->sectors_saved +(i->fat_num * i->sectors_por_fat) + i->lba_partition;
		lseek(i->fd,r_ * 512,SEEK_SET);
		read(i->fd,i->arr_global,512);
		
		
		
		}
		
	
	






#endif
