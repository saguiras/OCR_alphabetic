#include "graphic.h"

GtkWidget *loading_spin ;
GtkWidget *file_chooser;
GtkWidget *contrast;
GtkWidget *brightness;
GtkWidget *wimage;

int launch_menu()
{
    GtkBuilder      *builder; 
    GtkWidget       *window;

    gtk_init(NULL,NULL);

    builder = gtk_builder_new_from_file("glade/Menu.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "Menu"));
    
    gtk_builder_connect_signals(builder, NULL);

    loading_spin = GTK_WIDGET(gtk_builder_get_object(builder, "loading_spin"));

    g_object_unref(builder);

    gtk_widget_show(window);                
    gtk_main();

    return 0;
}

// called when window is closed
void on_Menu_destroy()
{
    gtk_main_quit();
}

void on_training_clicked(){
    gtk_spinner_start(GTK_SPINNER(loading_spin));
    Learn_NN();
    gtk_spinner_stop(GTK_SPINNER(loading_spin));
}


void on_automatic_clicked(){
    GtkBuilder *builder;
    GtkWidget  *Automatic;
    

    builder = gtk_builder_new_from_file("glade/Automatic.glade");
    Automatic = GTK_WIDGET(gtk_builder_get_object(builder, "Automatic"));
    file_chooser = GTK_WIDGET(gtk_builder_get_object(builder,"auto_file"));
    contrast = GTK_WIDGET(gtk_builder_get_object(builder,"contrast_entry"));
    brightness = GTK_WIDGET(gtk_builder_get_object(builder,"bright_entry"));
    wimage = GTK_WIDGET(gtk_builder_get_object(builder,"image"));


    gtk_builder_connect_signals(builder, NULL);
    g_object_unref(builder);
    gtk_widget_show(Automatic);
}

void on_launch_automatic_clicked(){
    GtkBuilder *builder;
    GtkWidget  *result;
    

    builder = gtk_builder_new_from_file("glade/result.glade");
    result = GTK_WIDGET(gtk_builder_get_object(builder, "result"));
    



    gtk_builder_connect_signals(builder, NULL);
    g_object_unref(builder);
    gtk_widget_show(result);

}


void file_selected(){
    char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_chooser));
    gtk_image_set_from_file(GTK_IMAGE(wimage),filename);
}

void on_treat_button_clicked(){
    char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_chooser));
    SDL_Surface *surf = load_image(filename);
    greyscale(surf);
    Contrast(surf,atof(gtk_entry_get_text(GTK_ENTRY(contrast))));
    blur(surf);
    Brightness(surf,atof(gtk_entry_get_text(GTK_ENTRY(brightness))));
    blacknwhite(surf);
}

