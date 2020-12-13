#include <gtk/gtk.h>
#include "../neural_network/neural_Tools.h"
#include "../tools/tools.h"

GtkWidget *loading_spin ;

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

void on_Manual_Button_clicked(){
    GtkBuilder *builder;
    GtkWidget  *Manual;
    GtkWidget *blur_factor;
    GtkWidget *bright_factor;
    builder = gtk_builder_new_from_file("glade/Manual.glade");
    Manual = GTK_WIDGET(gtk_builder_get_object(builder, "Manual"));
    blur_factor = GTK_WIDGET(gtk_builder_get_object(builder, "blur_entry"));
    bright_factor = GTK_WIDGET(gtk_builder_get_object(builder, "bright_entry"));
    gtk_builder_connect_signals(builder, NULL);
    g_object_unref(builder);
    gtk_widget_show(Manual);
}

//functions for manual
void on_BnW_clicked(){
    //call fction bnw on image
}

void on_Greyscale_clicked(){

}

void on_Blur_clicked(){

}

void on_Brightness_clicked(){

}

void on_neural_launch_clicked(){
    
}

void on_Automatic_Button_clicked(){
    GtkBuilder *builder;
    GtkWidget  *Automatic;
    GtkWidget *file_chooser;
    builder = gtk_builder_new_from_file("glade/Automatic.glade");
    Automatic = GTK_WIDGET(gtk_builder_get_object(builder, "Automatic"));
    file_chooser = GTK_WIDGET(gtk_builder_get_object(builder,"auto_file"));
    gtk_builder_connect_signals(builder, NULL);
    g_object_unref(builder);
    gtk_widget_show(Automatic);
}

void on_launch_automatic_clicked(){
    //faire les import et appeler ttes les fonctions
}

