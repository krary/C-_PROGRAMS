#include<stdio.h>
#include<stdlib.h>
#include<gtk/gtk.h> 
#include<inttypes.h>

#ifndef UTILIDADES_H
#define  UTILIDADES_H

GtkWidget *getWidget(GtkWidget *box,const char *id){
	
	GtkWidget *child = gtk_widget_get_first_child(box);
	while(child){
		
		const char *name = gtk_widget_get_name(child);
		
		
		if(name && g_strcmp0(name,id) == 0){
		return child;}
	    child = gtk_widget_get_next_sibling(child);	
		
		}
		return NULL;
	
		
	}




char **mensaje(){
	static char *msg[] = {
		"PARTICION LABA : ",
		"BYTE POR SECTORES : ",
		"SECTORES RESERVADOS : ",
		"SECTORES POR CLUSTER : ",
		"SECTORES POR FAT : ",
		"NUMERO DE FAT : ",
		"NUMERO DE CLUSTER : ",
		NULL
		
		
		};
	
	return msg;
	}
char **nombres(){
	static char *n[]={
		"lb_partition",
        "byte_por_sectores",
        "sectores_reservados",
        "sectores_por_cluster",
        "sectores_por_fat",
        "numero_de_fat",
        "numero_de_cluster",
        NULL
    
		};
	
	return n;
	}


#endif 
