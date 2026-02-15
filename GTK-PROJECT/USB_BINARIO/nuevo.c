#include <gtk/gtk.h>
#include<glib.h>
#include "config_datos.h"
#include "mbr.h"
#include "dir_usb.h"
#include "showing_data.h"
#include "utilidades.h"
#include<inttypes.h>
Info_base *info_base;
bool state_sp;
uint64_t lba_p = 0;
uint64_t num_cluster = 0;
//char **m = mensaje();	

static void set_margin_all(GtkWidget *w, int m);
static GtkWidget *labels(const char *msg,uint64_t num);


static void update_buffer(GtkTextBuffer *widget,GString *s){
	
	
	
	gtk_text_buffer_set_text(widget,s->str,-1);
	}
static void update(GtkWidget *label,uint64_t num,const char *ms){
	//char **m = mensaje();
	char element_new[512];
	snprintf(element_new,sizeof(element_new),"%s %lu",ms,num);
	gtk_label_set_text(GTK_LABEL(label),element_new);
	
	
	}

static GtkWidget *labels(const char *msg,uint64_t num){
   	
	char buff[512];
	 

	snprintf(buff,sizeof(buff),"%s %lu ",msg,num);
	
	
	
	GtkWidget *l = gtk_label_new(buff);
	gtk_label_set_xalign(GTK_LABEL(l), 0.0);
    gtk_label_set_yalign(GTK_LABEL(l), 0.0);
    gtk_label_set_wrap(GTK_LABEL(l), TRUE);
    gtk_label_set_selectable(GTK_LABEL(l), TRUE);

    gtk_widget_set_hexpand(l, TRUE);
    gtk_widget_set_vexpand(l, FALSE);

    gtk_widget_add_css_class(l, "texto_config");
    set_margin_all(l, 1);
	return l;
	}

/* Helper para simular gtk_widget_set_margin_all en GTK4 */
static void set_margin_all(GtkWidget *w, int m)
{
    gtk_widget_set_margin_top(w, m);
    gtk_widget_set_margin_bottom(w, m);
    gtk_widget_set_margin_start(w, m);
    gtk_widget_set_margin_end(w, m);
}
static void onSettingText(GtkDropDown *dropdown,GParamSpec *spec,gpointer ptr){
	//GtkWidget *label = GTK_WIDGET(ptr);
	CallBack *c_back = (CallBack*)ptr;
	GtkWidget *label = c_back->box;
	GtkWidget *spinner = c_back->spinner;
	
	
	guint selected = gtk_drop_down_get_selected(dropdown);
	if(selected == 0 || selected == GTK_INVALID_LIST_POSITION)return;
	GListModel *model = gtk_drop_down_get_model(dropdown);
	GtkStringObject *object = g_list_model_get_item(model,selected);
	
	if(object!=NULL){
		const char *elemento = gtk_string_object_get_string(object);
		g_object_unref(object);
		char path[512];
		char ultimate_path[512];
		int x;
		for( x = 0; elemento[x] != '\0';x++){
			if(elemento[x] == ' ')break;
			path[x] = elemento[x];
			}
	    	
	    path[x] = '\0';
	    snprintf(ultimate_path,sizeof(ultimate_path),"%s",path);
	    info_base = mbr_h(ultimate_path);
if (info_base == NULL) {
    g_printerr("Error: No se pudo obtener la info del MBR\n");
    return;
}
printf("DEBUG: LBA leída directamente: %" PRIu64 "\n", info_base->lba_partition);
	    
	    
	    
	    
	    snprintf(info_base->full_path,sizeof(info_base->full_path),"%s",ultimate_path);
	    //CURRENT DATA.....
	    lba_p = info_base->lba_partition;  //AQUI CAMBIA EL VALOR DE lba_p PARA MOSTRAR EN PANTALLA
	    if(info_base->lba_partition > 0)state_sp = true;
	    
	    
	    
	    
	    char **m = mensaje();
	    char **n = nombres();
	    
	    printf("%lu\n",lba_p);
	    //showing_data(info_base);
	    jump_lba(info_base);
	    //showing_data(info_base);
	    update(label,info_base->lba_partition,m[0]);
	   for(int x = 0; n[x] != NULL;x++){
		   
		   GtkWidget *l = getWidget(label,n[x]);
		   if(x == 0) update(l,info_base->lba_partition,m[x]);
		    if(x == 1) update(l,info_base->bytes_por_sectors,m[x]); 
		    if(x == 2) update(l,info_base->sectors_saved,m[x]);
		    if(x == 3) update(l,info_base->sectors_por_cluster,m[x]);
		    if(x == 4) update(l,info_base->sectors_por_fat,m[x]);
		    if(x == 5) update(l,info_base->cluster_num,m[x]);
             if(x == 6) update(l,info_base->fat_num,m[x]);
             if(n[x] == NULL)break;
		   }
	    
	    
	    
	    
	    
	    //showing_data(info_base);
	    printf("Numero de cluster: %lu\n",info_base->cluster_num);
	    printf("Numero de fat .: %d\n",info_base->fat_num);
	    printf("Sectores reservados .: %lu\n",info_base->sectors_saved);
	    printf("Sectores por fats .: %lu\n",info_base->sectors_por_fat);
	    printf("Sectores por cluster .: %lu\n",info_base->sectors_por_cluster);
	    printf("Byte por sectores .: %lu\n",info_base->bytes_por_sectors);
	             
	    jump_regiondata(info_base);//AQUI YA LA FUNCION HACE EL SALTO A LOS SECTORES DE LOS CLUSTER DE INFO
	    showing_string(info_base);//AQUI SE LLENA LA FUNCION ARR_FOLDER;
	    
	    //provisional(info_base);
	        
	    //CHANGE...
	    GtkTextBuffer *buff = getbuffer(label);
	    GString *msg_buffer = words_convert(info_base->arr_global_folder);
	    
	    printf("THE FOLDER IS: %s\n",msg_buffer->str);
	    update_buffer(buff,msg_buffer); 
	    g_idle_add(ui_stop,spinner);
	    
	
	}

}



static void activate(GtkApplication *app, gpointer user_data)
{   
	char **m = mensaje();
	char **n = nombres();
	int numero = sizeof(n);
	
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "BYTE TRAVELER // ROOT_ACCESS");
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 750);

    /* CONTENEDOR PRINCIPAL */
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_add_css_class(main_box, "main-container");	
    gtk_window_set_child(GTK_WINDOW(window), main_box);

    /* ================= HEADER ================= */
    GtkWidget *header_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 12);
    set_margin_all(header_box, 20);

    GtkWidget *lbl_info = gtk_label_new("› PLEASE SELECT A DEVICE ... ");
    gtk_widget_add_css_class(lbl_info, "neon-text");
   

    GtkWidget *spinner = gtk_spinner_new();
    set_margin_all(spinner,10);
    //gtk_widget_set_hexpand(spinner, TRUE);
    gtk_box_append(GTK_BOX(header_box),lbl_info);
    
    
    gtk_box_append(GTK_BOX(header_box), spinner);
    gtk_spinner_start(GTK_SPINNER(spinner));
    GtkWidget *spacer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    gtk_widget_set_hexpand(spacer,TRUE);
    gtk_box_append(GTK_BOX(header_box),spacer);

    char **devices = dir_usb();

    GtkWidget *device_dropdown = gtk_drop_down_new_from_strings((const char * const *)devices);
    gtk_widget_add_css_class(device_dropdown, "cyber-button");
    gtk_box_append(GTK_BOX(header_box), device_dropdown);

    gtk_box_append(GTK_BOX(main_box), header_box);

  
    /* ================= VISOR CENTRAL ================= */
    GtkWidget *scroll_view = gtk_scrolled_window_new();
    gtk_widget_set_vexpand(scroll_view, TRUE);
    gtk_widget_set_margin_start(scroll_view, 20);
    gtk_widget_set_margin_end(scroll_view, 20);
    gtk_widget_add_css_class(scroll_view, "neon-border");

    GtkWidget *text_view = gtk_text_view_new();
    gtk_text_view_set_monospace(GTK_TEXT_VIEW(text_view), TRUE);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    
    
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_text_buffer_set_text(buffer,"Software Engineering.. \n",-1);
   
        
    
    
    //==============  BUFFER ==========================================
   
    
   
   
   
   
   //=================================================================== 
    GtkWidget *box_labels = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    
    
    for(int x = 0; n[x] !=NULL;x++){
		GtkWidget *llb = labels(m[x],lba_p);
	    gtk_widget_set_name(llb,n[x]);
	
	    gtk_box_append(GTK_BOX(box_labels),llb);
      	
		}
    
    
    gtk_box_append(GTK_BOX(box_labels),text_view);
    
    GtkWidget *labb = getWidget(box_labels,"lb_partition");
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scroll_view),box_labels);
    gtk_box_append(GTK_BOX(main_box), scroll_view);
     
    
    
    
    
    /* ================= FOOTER ================= */
    GtkWidget *footer_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 15);
    set_margin_all(footer_box, 20);

    GtkWidget *btn_prev = gtk_button_new_with_label("« PREV_SECTOR");
    GtkWidget *btn_next = gtk_button_new_with_label("NEXT_SECTOR »");
    GtkWidget *entry_goto = gtk_entry_new();

    gtk_entry_set_placeholder_text(
        GTK_ENTRY(entry_goto),
        "GOTO_LBA..."
    );

    gtk_widget_add_css_class(btn_prev, "cyber-button");
    gtk_widget_add_css_class(btn_next, "cyber-button");
    gtk_widget_add_css_class(entry_goto, "cyber-entry");

    gtk_box_append(GTK_BOX(footer_box), btn_prev);
    gtk_box_append(GTK_BOX(footer_box), btn_next);
    gtk_box_append(GTK_BOX(footer_box), entry_goto);
	
    gtk_box_append(GTK_BOX(main_box), footer_box);

    /* ================= CSS CYBERPUNK ================= */
    GtkCssProvider *provider = gtk_css_provider_new();

    gtk_css_provider_load_from_string(provider,
        "window { background-color: #050505; }"

        ".main-container { "
        "  border: 2px solid #00ff41; "
        "  margin: 5px; "
        "  box-shadow: 0 0 10px #00ff41; "
        "}"

        ".neon-text { "
        "  color: #00ff41; "
        "  font-family: 'Monospace'; "
        "  font-weight: bold; "
        "  text-shadow: 0 0 5px #00ff41; "
        "}"
        ".texto_config { "
        "  color: #00ff41; "
        "  font-family: 'Monospace'; "
        "  font-weight: bold; "
        "  text-shadow: 0 0 15px #00ff41; "
        //"border: 5px solid #2731F5;"
        //"border-radius: 14px;" 
        "}"
       /* ".texto_config:hover{"
          "border: 1px solid #00ff41;"
           "margin: 1px;"
           "color: #00ff41;"
           "font-size:23px;"
        
        "}"*/
        
        ".data { "
        "  color: #00ff41; "
        "  font-family: 'Monospace'; "
        "  font-weight: bold; "
        "  text-shadow: 0 0 5px #00ff41; "
        "}"

        "textview { "
        "  background-color: #000000; "
        "  color: #A88E8D; "
        "  font-size: 14pt; "
        "}"
        

        ".neon-border { "
        "  border: 1px solid #00ff41; "
        "  box-shadow: inset 0 0 15px #003300; "
        "}"

        ".cyber-button { "
        "  background: #000000; "
        "  color: #00ff41; "
        "  border: 1px solid #00ff41; "
        "  border-radius: 0px; "
        "  font-family: 'Monospace'; "
        "  font-weight: bold; "
        "  padding: 5px 15px; "
        "}"

        ".cyber-button:hover { "
        "  background: #00ff41; "
        "  color: #000000; "
        "  box-shadow: 0 0 15px #00ff41; "
        "}"

        ".cyber-entry { "
        "  background: #000000; "
        "  color: #00ff41; "
        "  border: 1px solid #00ff41; "
        "  border-radius: 0px; "
        "  font-family: 'Monospace'; "
        "  caret-color: #00ff41; "
        "}"

        "scrollbar.vertical { "
        "  background: #000; "
        "  border-left: 1px solid #00ff41; "
        "}"

        "scrollbar slider { "
        "  background: #00ff41; "
        "  border-radius: 0px; "
        "  min-width: 8px; "
        "}"
    );

    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );

//================= ACTIONS ============================================================


CallBack *callback = g_malloc(sizeof(CallBack));
callback->box = box_labels;
callback->spinner = spinner;


if(labb){
g_signal_connect(device_dropdown,"notify::selected",G_CALLBACK(onSettingText),callback);


}


    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv)
{
    GtkApplication *app =
        gtk_application_new(
            "com.cyber.traveler",
            G_APPLICATION_DEFAULT_FLAGS
        );

    g_signal_connect(app, "activate",G_CALLBACK(activate), NULL);

    int status = g_application_run(
        G_APPLICATION(app), argc, argv
    );

    g_object_unref(app);
    return status;
}
