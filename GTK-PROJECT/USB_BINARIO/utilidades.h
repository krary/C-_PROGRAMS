#include<stdio.h>
#include<stdlib.h>
#include<gtk/gtk.h> 
#include<inttypes.h>

#ifndef UTILIDADES_H
#define  UTILIDADES_H

static gboolean ui_stop(gpointer pointer){
	
	GtkWidget *spinner = GTK_WIDGET(pointer);
	gtk_spinner_stop(GTK_SPINNER(spinner));
	
	return FALSE;
	
}


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

        if (entry[0] == 0x00) continue; 
        if (entry[0] == 0xE5) continue;
        if (entry[11] == 0x0F) continue; // Ignorar nombres largos

        // 1. Copiar NOMBRE (8 bytes)
        for (int j = 0; j < 8; j++) {
            if (entry[j] != 0x00 && entry[j] != ' ') {
                g_string_append_c(w_, entry[j]);
            }
        }

        // 2. Manejar EXTENSIÓN o DIRECTORIO
        if (!(entry[11] & 0x10)) { // Es un ARCHIVO
            g_string_append(w_, ".");
            for (int j = 8; j < 11; j++) {
                // FILTRO CRUCIAL: No copiar espacios ni nulos de la extensión
                if (entry[j] != 0x00 && entry[j] != ' ') {
                    g_string_append_c(w_, entry[j]);
                }
            }
        } else { // Es un DIRECTORIO
            g_string_append(w_, "/");
        }

        g_string_append(w_, "\n");
    }
    return w_;
}	
#endif 
