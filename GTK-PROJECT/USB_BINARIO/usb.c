#include<gtk/gtk.h>
#include<sys/stat.h>
#include<stdbool.h>
#include<stdlib.h>
#include "dir_usb.h"
#include "mbr.h"
#include "showing_data.h"
#include<glib.h>
 Info_base *i;
typedef struct{
	
	GtkTextBuffer *buffer;
	int indice;
	}DatosEscritura;
typedef struct{
	double r,g,b;
	double grosor;
	int x , y ,end_x,end_y;
	bool operar_y;
	}ConfigLine;
	


static void show_string_gtk(uint8_t *arr_,int size,GtkTextBuffer *buffer){
	printf("DEBUG: El primer byte a mostrar es: %02X\n", arr_[0]);
	     GString *hex_display = g_string_new("");
         for(int x = 0; x < size;x++){
			 
			 g_string_append_printf(hex_display,"%02X",arr_[x]);
			 if((x+1) % 16 == 0){
				 g_string_append(hex_display,"\n");
				 }
			 
			 }	
	       gtk_text_buffer_set_text(buffer,hex_display->str,-1);
	       g_string_free(hex_display,TRUE);
	
	}
static void on_selected_string(GtkDropDown *dropdown,
GParamSpec *prspec,gpointer user_data){
	 GtkTextBuffer *buffer = GTK_TEXT_BUFFER(user_data);
	 
	 
	guint selected = gtk_drop_down_get_selected(dropdown);
	if(selected == GTK_INVALID_LIST_POSITION) return;
	GListModel *model = gtk_drop_down_get_model(dropdown);
	GtkStringObject *obj = g_list_model_get_item(model,selected);
	
	if(obj != NULL){
		const char *texto = gtk_string_object_get_string(obj);
		g_object_unref(obj);
		
		char path[512];
	    char full_path[512];
	    int x;
			printf("[");
        		
		for(x = 0; texto[x]!= '\0';x++){
			if(texto[x] == ' ')break;
			path[x] = texto[x];
		    printf("%c",path[x]);}
		    path[x] = '\0';
		
		
			printf("]\n");
		  snprintf(full_path,sizeof(full_path),"%s",path); 
		   
		   
		    i = mbr_h(full_path);//Inicializa i Info_base reservando memoria y dando el primer salto
		    snprintf(i->full_path,sizeof(i->full_path),"%s",full_path);
		    printf("%s\n",i->full_path);
		    show_string_gtk(i->arr_global,512,buffer);
		    //while (g_main_context_iteration(NULL, FALSE));

		    //showing_data(i);
		}
		
	
	}	

static void dibujo(GtkDrawingArea *lienzo,cairo_t *cr,int x,int y,gpointer ptr){
	
	ConfigLine *config = (ConfigLine*)ptr;
	
	cairo_set_source_rgb(cr,1.0,1.0,1.0);
	cairo_set_line_width(cr,1.0);

	cairo_move_to(cr,config->x,config->y);
	
	if(config->operar_y == 1){
	cairo_line_to(cr,config->x,y - config->end_y);}
	else{cairo_line_to(cr,x - config->end_x,config->y);}
	
	
	cairo_stroke(cr);
	
	
	}


static void activate(GtkApplication *app,gpointer ptr){
    
    
   
	GtkWidget *window = gtk_application_window_new(GTK_APPLICATION(app));
	gtk_window_set_title(GTK_WINDOW(window),"drawing");
	gtk_window_set_default_size(GTK_WINDOW(window),1000,700);
	
	
	//WIDGETS
	//*****************************************************************************************
	GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL,10);
	GtkCssProvider *provider = gtk_css_provider_new();
	GtkWidget *text_view = gtk_text_view_new();
	GtkWidget *scroll = gtk_scrolled_window_new();
	//******************************************************************************************
	
	
	//CONFIGURACION DE EL TEXT VIEW 
	//******************************************************************************************
	gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view),FALSE);
	gtk_text_view_set_monospace(GTK_TEXT_VIEW(text_view),TRUE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(text_view),FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view),GTK_WRAP_WORD);
    gtk_text_view_set_left_margin(GTK_TEXT_VIEW(text_view),20);
    gtk_text_view_set_right_margin(GTK_TEXT_VIEW(text_view),20);
    gtk_widget_set_vexpand(text_view,TRUE);
    gtk_widget_set_margin_top(text_view,20);
    gtk_widget_set_margin_start(text_view,30);
	GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
	gtk_text_buffer_set_text(buffer,"lisandro",-1);
	gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scroll),text_view);
	gtk_widget_add_css_class(text_view,"texto_view");
	//********************************************************************************************
	
	
	//CONFIGURACION DE EL DROPDOWN
	//****************************************************************************************
	char **options = dir_usb();
	GtkWidget *dropdown = gtk_drop_down_new_from_strings((const char * const *)options);
   	gtk_widget_add_css_class(dropdown,"droppdown");
   	gtk_widget_set_halign(dropdown,GTK_ALIGN_END);
   	gtk_widget_set_margin_end(dropdown,60);
   	gtk_widget_set_margin_top(dropdown,30);
	gtk_widget_set_valign(dropdown,GTK_ALIGN_START);
	gtk_widget_set_vexpand(dropdown,TRUE);
	
	gtk_css_provider_load_from_string(provider,
    ".droppdown{ "    
    "   color: yellow;"
    "   font-size: 18px;"
    "}"
    
    ".texto_view{ "
    "color:yellow;"
    "font-size:34dp;"
    
    "}"
    
    );
   gtk_style_context_add_provider_for_display(gdk_display_get_default(),GTK_STYLE_PROVIDER(provider),
   GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
   g_object_unref(provider);
	for (int i = 0; options[i] != NULL; i++) free(options[i]);
    free(options);
	
	//*******************************************************************************************
	
	
	
		
    g_signal_connect(dropdown,"notify::selected",G_CALLBACK(on_selected_string),buffer);
   
    gtk_box_append(GTK_BOX(box),dropdown);
    gtk_box_append(GTK_BOX(box),scroll);
    gtk_window_set_child(GTK_WINDOW(window),box);
	gtk_window_present(GTK_WINDOW(window));
	
	}





int main(int argc,char *argv[]){
	
	GtkApplication *app = gtk_application_new("example.app",G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect(app,"activate",G_CALLBACK(activate),NULL);
	int status = g_application_run(G_APPLICATION(app),argc,argv);
	
	g_object_unref(app);
	
	
	return 0;
	}
