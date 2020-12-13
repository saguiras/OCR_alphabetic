# ifndef GRAPHIC_H_
# define GRAPHIC_H_

#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../tools/tools.h"
#include "../treatment/treatment.h"
#include "../CharDetection/CharDetection.h"
#include "../neural_network/neural_network_XOR.h"
#include "../tools/display_tools.h"
#include "../neural_network/neural_network.h"

int main(int argc, char *argv[]);
void on_Menu_destroy();
void on_Training_Button_clicked();
void on_Automatic_Button_clicked();
void on_launch_automatic_clicked();
void file_selected();
void on_treat_button_clicked();

# endif
