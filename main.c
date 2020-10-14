void help()
{
    printf("   --help  To picture commands\n");
    printf("   --XOR  To show the neural network for the XOR function\n");
    printf("   --OCR  To show the neural network for OCR\n");
    printf("   (No args)  Launch GUI\n");
}

int main(int argc, char *argv[])
{
    if(argc>1)
    {
        if(strcmp(argv[1], "--help") == 0)
        {
            help();
        }
        if(strcmp(argv[1], "--XOR") == 0)
        {
           // XOR();
        }
        if(strcmp(argv[1], "--OCR") == 0)
        {
           // trainNN();
        }
    }
    else
    {
      printf("#-----------------------#\n");
      printf("|         Welcome       |\n");
      printf("#-----------------------#\n");
      //Create GTK window
      create_window(argc,argv);
    }
    return(EXIT_SUCCESS);
}
