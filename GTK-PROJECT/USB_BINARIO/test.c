	#include<gtk/gtk.h>
    #include<unistd.h>
    #include<stdint.h>
    #include<string.h>
    #include<fcntl.h>
    #include<stdio.h>
    #include<stdlib.h>
    #include<glib.h>
char **mensajes(){
  
  static char *palabras[] = {
     "PRUEBA 1",
     "PRUEBA 2",
     "PRUEBA 3",
     "PRUEBA 4",
  
  };
  
  return palabras;


}
static void margen(GtkWidget *w,int m){
	gtk_widget_set_margin_bottom(w,m);
	gtk_widget_set_margin_top(w,m);
	gtk_widget_set_margin_start(w,m);
	gtk_widget_set_margin_end(w,m);
	
	}

    
	
	static void activate(GtkApplication *app,gpointer ptr){
	GtkWidget *window = gtk_application_window_new(GTK_APPLICATION(app));
	gtk_window_set_title(GTK_WINDOW(window),"Testing...");
	gtk_window_set_default_size(GTK_WINDOW(window),1000,700);
     
    GtkCssProvider *provider = gtk_css_provider_new();

    
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL,20);
    gtk_widget_add_css_class(main_box,"m_box");
    margen(main_box,20); 

    GtkWidget *box_mensaje = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,20);
    gtk_widget_add_css_class(box_mensaje,"mensaje_box");
    margen(box_mensaje,10); 
    
    
    //LABEL
    char **k_m = mensajes();
    GtkWidget *label = gtk_label_new(k_m[0]);
    gtk_box_append(GTK_BOX(box_mensaje),label);
    gtk_box_append(GTK_BOX(main_box),box_mensaje);
    gtk_widget_add_css_class(label,"label1");
    
    
    
    GtkWidget *spacer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    gtk_widget_set_hexpand(spacer,TRUE);
    gtk_box_append(GTK_BOX(box_mensaje),spacer);
    
    GtkWidget *button = gtk_button_new_with_label("Press..");
    gtk_widget_add_css_class(button,"buttonlabel");
    margen(button,5);
    gtk_box_append(GTK_BOX(box_mensaje),button);
    


 
	
	gtk_css_provider_load_from_string(provider,
	".label1{"
	 "color:#2731F5;"
	 "font-family:Monospace;"
	 "font-size:14pt;"
	 "font-weight:bold;"
	 "text-shadow:0 0 10px #2731F5;"
	 "border: 2px solid #2731F5;"
	 "border-radius: 13px;"
	
	"}"
	".mensaje_box{"
	"border: 1px solid #00ff41;"
	"border-radius: 13px;"
	"}"
	".m_box{"
	"border: 1px solid #00ff42;"
	"border-radius: 8px;"
	"}"
	".mensaje_box:hover {"
	"background: #00ff41;"
	"color:#000000;"
	"box-shadow: 0 0 25px #00ff41;"
	"}"
	);
	gtk_style_context_add_provider_for_display(gdk_display_get_default(),GTK_STYLE_PROVIDER(provider),
    GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
	
	
	gtk_window_set_child(GTK_WINDOW(window),main_box);
	gtk_window_present(GTK_WINDOW(window));
	
	
	}
	
	int main(int argc,char *argv[]){
	
	GtkApplication *app = gtk_application_new("example.app",G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect(app,"activate",G_CALLBACK(activate),NULL);
	int status = g_application_run(G_APPLICATION(app),argc,argv);
	g_object_unref(app);
	
	
	return 0;}
