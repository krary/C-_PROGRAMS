#include<stdio.h>
#include<stdlib.h>
#include<gtk/gtk.h> 
#include<inttypes.h>

#ifndef UTILIDADES_H
#define  UTILIDADES_H
char **mensaje(){
	static char *msg[] = {
		"PARTICION LABA : ",
		"BYTE POR SECTORES : ",
		"SECTORES RESERVADOS : ",
		"SECTORES POR CLUSTER : ",
		"SECTORES POR FAT : ",
		"NUMERO DE FAT : ",
		"NUMERO DE CLUSTER : ",
		
		
		};
	
	return msg;
	}


#endif 
