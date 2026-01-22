#include<gtk/gtk.h>
#include<sys/stat.h>
#include<stdbool.h>
#include<stdlib.h>
#include "dir_usb.h"
#include "mbr.h"
#include "showing_data.h"
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
	


static void onParrafo(gpointer ptr){
	
	}
static void on_selected_string(GtkDropDown *dropdown,GParamSpec *prspec,gpointer user_data){
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
		   
		   printf("%s\n",full_path);
		    Info_base *i = mbr_h(full_path);
		    showing_data(i);
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
	//*****************************************************************************************S
	
	
	
	char **options = dir_usb();
	//CONFIGURACION DE EL DROPDOWN
	//****************************************************************************************
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
    "}");
   gtk_style_context_add_provider_for_display(gdk_display_get_default(),GTK_STYLE_PROVIDER(provider),
   GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
   g_object_unref(provider);
	for (int i = 0; options[i] != NULL; i++) free(options[i]);
    free(options);
	
	//*******************************************************************************************
	
	
	
		
    g_signal_connect(dropdown,"notify::selected",G_CALLBACK(on_selected_string),NULL);
    gtk_box_append(GTK_BOX(box),dropdown);
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
