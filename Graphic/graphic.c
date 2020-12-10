#include <gtk/gtk.h>



int main(int argc, char *argv[])
{
    GtkBuilder      *builder; 
    GtkWidget       *window;
    GdkColor color ;
    gdk_color_parse( "#0080FF", &color );

    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("glade/Menu.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "Menu"));
    gtk_widget_override_background_color(window, GTK_STATE_NORMAL, &color);
    
    gtk_builder_connect_signals(builder, NULL);

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
    GtkBuilder *builder;
    GtkWidget  *Training;
    builder = gtk_builder_new_from_file("glade/Training.glade");
    Training = GTK_WIDGET(gtk_builder_get_object(builder, "Training"));
    gtk_builder_connect_signals(builder, NULL);
    g_object_unref(builder);
    gtk_widget_show(Training);
}

void on_Manual_Button_clicked(){
    GtkBuilder *builder;
    GtkWidget  *Manual;
    builder = gtk_builder_new_from_file("glade/Manual.glade");
    Manual = GTK_WIDGET(gtk_builder_get_object(builder, "Manual"));
    gtk_builder_connect_signals(builder, NULL);
    g_object_unref(builder);
    gtk_widget_show(Manual);
}

void on_Automatic_Button_clicked(){
    GtkBuilder *builder;
    GtkWidget  *Automatic;
    builder = gtk_builder_new_from_file("glade/Automatic.glade");
    Automatic = GTK_WIDGET(gtk_builder_get_object(builder, "Automatic"));
    gtk_builder_connect_signals(builder, NULL);
    g_object_unref(builder);
    gtk_widget_show(Automatic);
}