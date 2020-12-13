#include <gtk/gtk.h>
#include <SDL/SDL.h>
#include "../neural_network/neural_Tools.h"
#include "../tools/tools.h"

GtkWidget *loading_spin ;
GtkWidget *file_chooser;
GtkWidget *contrast;
GtkWidget *brightness;
GtkWidget *wimage;

int main(int argc, char *argv[])
{
    GtkBuilder      *builder; 
    GtkWidget       *window;

    builder = gtk_builder_new_from_file("glade/Menu.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "Menu"));
    
    gtk_builder_connect_signals(builder, NULL);
    loading_spin = GtK_WIDGET(gtk_builder_get_object(builder, "loading_spin"));

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

void on_Training_Button_clicked(){
    gtk_spinner_start(loading_spin);
    Learn_NN();
    gtk_spinner_stop(loading_spin);
}


void on_Automatic_Button_clicked(){
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

}


void file_selected(){
    char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(filechooser));
    gtk_image_set_from_file(GTK_IMAGE(wimage),filename);
}

void on_treat_button_clicked(){
    SDL_Surface *surf = load_image(filename);
    greyscale(surf);
    Contrast(surf,float(gtk_entry_get_text(contrast)));
    blur(surf);
    Brightness(surf,float(gtk_entry_get_text(brightness)));
    blacknwhite(surf);
}

