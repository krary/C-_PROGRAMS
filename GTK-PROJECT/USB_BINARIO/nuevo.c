#include <gtk/gtk.h>
#include <glib.h>
#include "config_datos.h"
#include "mbr.h"
#include "dir_usb.h"
#include "showing_data.h"
#include "utilidades.h"
#include <inttypes.h>

Info_base *info_base;
bool state_sp;
uint64_t lba_p = 0;
uint64_t num_cluster = 0;

static void set_margin_all(GtkWidget *w, int m);
static GtkWidget *labels(const char *msg,uint64_t num);

static void update_buffer(GtkTextBuffer *widget,GString *s){
    gtk_text_buffer_set_text(widget,s->str,-1);
}

static void update(GtkWidget *label,uint64_t num,const char *ms){
    char element_new[512];
    snprintf(element_new,sizeof(element_new),"%s %lu",ms,num);
    gtk_label_set_text(GTK_LABEL(label),element_new);
}

static GtkWidget *labels(const char *msg,uint64_t num){
    char buff[512];
    snprintf(buff,sizeof(buff),"%s %lu ",msg,num);

    GtkWidget *l = gtk_label_new(buff);
    gtk_label_set_xalign(GTK_LABEL(l), 0.0);
    gtk_label_set_wrap(GTK_LABEL(l), TRUE);
    gtk_label_set_selectable(GTK_LABEL(l), TRUE);

    gtk_widget_set_hexpand(l, TRUE);
    gtk_widget_add_css_class(l, "texto_config");

    set_margin_all(l, 4);
    return l;
}

static void set_margin_all(GtkWidget *w, int m){
    gtk_widget_set_margin_top(w, m);
    gtk_widget_set_margin_bottom(w, m);
    gtk_widget_set_margin_start(w, m);
    gtk_widget_set_margin_end(w, m);
}

static void onSettingText(GtkDropDown *dropdown,GParamSpec *spec,gpointer ptr){

    CallBack *c_back = (CallBack*)ptr;
    GtkWidget *label = c_back->box;
    GtkWidget *bx_buffer = c_back->box_buffer;
    GtkWidget *spinner = c_back->spinner;

    guint selected = gtk_drop_down_get_selected(dropdown);
    if(selected == 0 || selected == GTK_INVALID_LIST_POSITION) return;

    GListModel *model = gtk_drop_down_get_model(dropdown);
    GtkStringObject *object = g_list_model_get_item(model,selected);

    if(object!=NULL){

        gtk_spinner_start(GTK_SPINNER(spinner));

        const char *elemento = gtk_string_object_get_string(object);
        g_object_unref(object);

        char path[512];
        char ultimate_path[512];
        int x;

        for(x = 0; elemento[x] != '\0'; x++){
            if(elemento[x] == ' ') break;
            path[x] = elemento[x];
        }

        path[x] = '\0';
        snprintf(ultimate_path,sizeof(ultimate_path),"%s",path);

        info_base = mbr_h(ultimate_path);
        if (info_base == NULL) {
            g_printerr("Error: No se pudo obtener la info del MBR\n");
            return;
        }

        snprintf(info_base->full_path,sizeof(info_base->full_path),"%s",ultimate_path);

        lba_p = info_base->lba_partition;
        if(info_base->lba_partition > 0) state_sp = true;

        char **m = mensaje();
        char **n = nombres();

        jump_lba(info_base);

        for(int i = 0; n[i] != NULL; i++){
            GtkWidget *l = getWidget(label,n[i]);

            if(i == 0) update(l,info_base->lba_partition,m[i]);
            if(i == 1) update(l,info_base->bytes_por_sectors,m[i]);
            if(i == 2) update(l,info_base->sectors_saved,m[i]);
            if(i == 3) update(l,info_base->sectors_por_cluster,m[i]);
            if(i == 4) update(l,info_base->sectors_por_fat,m[i]);
            if(i == 5) update(l,info_base->cluster_num,m[i]);
            if(i == 6) update(l,info_base->fat_num,m[i]);
        }

        jump_regiondata(info_base);
        showing_string(info_base);

        GtkTextBuffer *buff = getbuffer(bx_buffer);//OJO EN ESTA LINEA
        GString *msg_buffer = words_convert(info_base->arr_global_folder);
        
        //Actualizacion de los labels de carpeta y creacion de los mismos   
        
        char **f = folder(msg_buffer);
         limpiar_box(c_back->box_buffer);
        for(int s = 0; f[s] != NULL; s++){
		
		 GtkWidget *label_f = gtk_label_new(f[s]);
		 gtk_widget_add_css_class(label_f,"label_f_");
		 gtk_widget_set_name(label_f,f[s]);
		 gtk_box_append(GTK_BOX(c_back->box_buffer),label_f);  //<<<<<------------|
     
		 
		 }
     
        
        
           
        update_buffer(buff,msg_buffer);

        g_idle_add(ui_stop,spinner);
    }
}

static void activate(GtkApplication *app, gpointer user_data){

    char **m = mensaje();
    char **n = nombres();

    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "BYTE TRAVELER // ROOT_ACCESS");
    gtk_window_set_default_size(GTK_WINDOW(window), 1100, 800);

    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    gtk_widget_add_css_class(main_box, "main-container");
    set_margin_all(main_box, 10);
    gtk_window_set_child(GTK_WINDOW(window), main_box);

    /* ================= HEADER ================= */

    GtkWidget *header_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 15);

    GtkWidget *lbl_info = gtk_label_new("› SELECT USB DEVICE");
    gtk_widget_add_css_class(lbl_info, "neon-text");

    GtkWidget *spinner = gtk_spinner_new();
    gtk_widget_set_size_request(spinner, 24, 24);

    GtkWidget *spacer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    gtk_widget_set_hexpand(spacer,TRUE);

    char **devices = dir_usb();
    GtkWidget *device_dropdown = gtk_drop_down_new_from_strings((const char * const *)devices);
    gtk_widget_add_css_class(device_dropdown, "cyber-button");

    gtk_box_append(GTK_BOX(header_box),lbl_info);
    gtk_box_append(GTK_BOX(header_box),spinner);
    gtk_box_append(GTK_BOX(header_box),spacer);
    gtk_box_append(GTK_BOX(header_box),device_dropdown);

    gtk_box_append(GTK_BOX(main_box), header_box);

    /* ================= CENTRAL ================= */

    GtkWidget *scroll_view = gtk_scrolled_window_new();
    gtk_widget_set_vexpand(scroll_view, TRUE);
    gtk_widget_add_css_class(scroll_view, "neon-border");

    GtkWidget *content_box = gtk_box_new(GTK_ORIENTATION_VERTICAL,15);
    set_margin_all(content_box,10);

    /* === MBR SECTION === */

    GtkWidget *box_info = gtk_box_new(GTK_ORIENTATION_VERTICAL,10);
    gtk_widget_add_css_class(box_info,"box_info_");

    GtkWidget *label_mbr = gtk_label_new("1. MBR / LBA INFORMATION");
    gtk_widget_set_name(label_mbr,"label_mbr");
    gtk_widget_add_css_class(label_mbr,"label_mbr_");

    gtk_box_append(GTK_BOX(box_info),label_mbr);

    for(int i = 0; n[i] != NULL; i++){
        GtkWidget *llb = labels(m[i],lba_p);
        gtk_widget_set_name(llb,n[i]);
        gtk_box_append(GTK_BOX(box_info),llb);
    }

    /* === FOLDER SECTION === */

    GtkWidget *box_folder = gtk_box_new(GTK_ORIENTATION_VERTICAL,10);
    gtk_widget_add_css_class(box_folder,"box_folder_");

    GtkWidget *label_folder = gtk_label_new("2. DIRECTORY STRUCTURE");
    gtk_widget_set_name(label_folder,"label_folder");
    gtk_widget_add_css_class(label_folder,"label_folder_");
    gtk_box_append(GTK_BOX(box_folder),label_folder);
     
    
    
    
    gtk_box_append(GTK_BOX(content_box),box_info);
    gtk_box_append(GTK_BOX(content_box),box_folder);

    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scroll_view),content_box);
    gtk_box_append(GTK_BOX(main_box), scroll_view);

    /* ================= FOOTER ================= */

    GtkWidget *footer_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 15);

    GtkWidget *btn_prev = gtk_button_new_with_label("« PREV");
    GtkWidget *btn_next = gtk_button_new_with_label("NEXT »");
    GtkWidget *entry_goto = gtk_entry_new();

    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_goto),"GOTO LBA...");

    gtk_widget_add_css_class(btn_prev, "cyber-button");
    gtk_widget_add_css_class(btn_next, "cyber-button");
    gtk_widget_add_css_class(entry_goto, "cyber-entry");

    gtk_box_append(GTK_BOX(footer_box), btn_prev);
    gtk_box_append(GTK_BOX(footer_box), btn_next);
    gtk_box_append(GTK_BOX(footer_box), entry_goto);

    gtk_box_append(GTK_BOX(main_box), footer_box);

    /* ================= CSS ================= */

    GtkCssProvider *provider = gtk_css_provider_new();	

    gtk_css_provider_load_from_string(provider,
    "window { background-image: linear-gradient(to bottom, #050505, #0b0f14); }"
    ".main-container { border:1px solid #00ff88; border-radius:8px; box-shadow:0 0 25px rgba(0,255,136,0.15); }"
    ".neon-text { color:#00ff88; font-size:16px; font-weight:bold; }"
    ".box_info_, .box_folder_ { background:rgba(0,20,15,0.6); border:1px solid rgba(0,255,136,0.2); border-radius:6px; padding:10px; }"
    ".label_mbr_, .label_folder_ { color:#00ffaa; font-weight:bold; }"
    ".texto_config { color:#00ff88; font-size:13px; }"
    ".label_f_:hover { background:#00ff88; color:#000; }"  
    "textview { background:#0a0f14; color:#8affd1; border-radius:6px; padding:10px; }"
    ".cyber-button { background:#0f141a; color:#00ff88; border:1px solid rgba(0,255,136,0.4); border-radius:6px; padding:6px 18px; }"
    ".cyber-button:hover { background:#00ff88; color:#000; }"
    ".cyber-entry { background:#0f141a; color:#00ff88; border:1px solid rgba(0,255,136,0.4); border-radius:6px; }"
    );

    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );

    CallBack *callback = g_malloc(sizeof(CallBack));
    callback->box = box_info;
    callback->box_buffer = box_folder;
    callback->spinner = spinner;

    g_signal_connect(device_dropdown,"notify::selected",G_CALLBACK(onSettingText),callback);

    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv){
    GtkApplication *app =
        gtk_application_new("com.cyber.traveler",
                            G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect(app, "activate",G_CALLBACK(activate), NULL);

    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
