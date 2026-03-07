#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
#include<fcntl.h>
#include<stdbool.h>
#ifndef CONFIG_DATOS_H
#define CONFIG_DATOS_H
typedef struct {GtkWidget *spinner;bool state_spinner;}THreadspinner;





//Hi this is just a test if the changes can hold it into this file 
typedef struct{
	 char *copia_texto_label;
	 int fd;   //lleno
	 ssize_t r; //lleno
	 char full_path[512]; //lleno
	 uint8_t arr_global[512]; //lleno
	 uint8_t *arr_global_folder;
	 uint64_t lba_partition; //lleno
	 uint64_t cluster_num; //lleno
	 uint8_t fat_num;  //lleno
     uint64_t bytes_por_sectors;
	 uint64_t sectors_por_fat; //lleno
	 uint64_t sectors_por_cluster; //lleno
	 uint64_t sectors_saved;    //lleno
	 uint16_t high_cluster;
	 uint16_t low_cluster;
	 uint64_t region_data;
	 GtkWidget *label_text_folder;
	 int tam_folder;
	 
	
	}__attribute__((packed))Info_base;


typedef struct{GtkWidget *box,*box_buffer,*box_item;Info_base *info_base;GtkWidget *spinner;}CallBack;





#endif
