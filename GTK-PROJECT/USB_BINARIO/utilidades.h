#include<stdio.h>
#include<stdlib.h>
#include<gtk/gtk.h> 
#include<inttypes.h>

#ifndef UTILIDADES_H
#define  UTILIDADES_H

GtkTextBuffer *getbuffer(GtkWidget *box){
	
	GtkWidget *child = gtk_widget_get_first_child(box);
	while(child != NULL){
		if(GTK_IS_TEXT_VIEW(child)){
			
			return gtk_text_view_get_buffer(GTK_TEXT_VIEW(child));
			}
			child = gtk_widget_get_next_sibling(child); 
		
		}
		return NULL;
	
	
	}



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

char **carpetas(Info_base *b){
	
	char **x_name = calloc(512,sizeof(char*));
	if(x_name == NULL)return NULL;
	for(int x =0; x < 512; x++){
		
		x_name = calloc(32,sizeof(char));
		if(x_name !=NULL){
			 memcpy(x_name,b->arr_global_folder+x,32);
			 x_name[x][32] = '\0';
			}
	
	
	return x_name;
	}
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
	
	GString *words_convert(uint8_t *ptr) {
    GString *w_ = g_string_new("");

    for (int x = 0; x < 16; x++) {
        uint8_t *entry = &ptr[x * 32];

        // Si la entrada está vacía, saltamos a la siguiente (no usamos break aún)
        if (entry[0] == 0x00) continue; 
        // Si está borrado, saltamos
        if (entry[0] == 0xE5) continue;

        // Copiamos los 8 bytes del nombre
        for (int j = 0; j < 8; j++) {
            // SOLO añadimos si no es nulo y no es un espacio molesto
            if (entry[j] != 0x00 && entry[j] != ' ') {
                g_string_append_c(w_, entry[j]);
            }
        }
        
        // Añadimos un separador para verlos todos
        g_string_append(w_, "\n");
    }

    return w_;
}

#endif 
