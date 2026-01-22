#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include "config_datos.h"

Info_base *mbr_h(char *dev){
	Info_base *info_base = malloc(sizeof(*info_base));
	if(!info_base){printf("Info_base no puedo reservar memoria\n");
		return NULL;}
	info_base->fd = open(dev,O_RDONLY);
	if(info_base->fd < 0){
		free(info_base);
		printf("Error en info_base->fd...\n");
		return NULL; }
	
	ssize_t r = read(info_base->fd,info_base->arr_global,512);
	if(r != 512){
		printf("El tamaño de los bytes [512] no coincide...\n");
		close(info_base->fd);
		free(info_base);
		return NULL;}
	memcpy(&info_base->lba_partition,info_base->arr_global + (446 + 8),4);
	
	return info_base;
}
