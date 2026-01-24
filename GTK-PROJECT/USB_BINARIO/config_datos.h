#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
#include<fcntl.h>
#ifndef CONFIG_DATOS_H
#define CONFIG_DATOS_H

typedef struct{
	 int fd;
	 char full_path[512];
	 uint8_t arr_global[512];
	 uint64_t lba_partition;
	 uint8_t fat_num;
	 uint64_t fat_size;
	 uint64_t cluster_num;
	 uint64_t sectors_num;
	 uint64_t sectors_saved;
	 uint16_t high_cluster;
	 uint16_t low_cluster;
	 uint64_t region_data;
	 
	
	}__attribute__((packed))Info_base;

#endif
