#include "io.h"

void kernel_main(){
    
    print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLUE);
    print_str("Welcome to GOS64");
    print_newline();
    print_str("This is an OS that can do a bunch of cool shit");
    print_newline();
    initialize_input();

    
    while(1){
        print_str(">");
        char* input = read_input();
        print_newline();
        print_str("you typed: ");
        print_str(input);
        print_newline();
    }
    print_clear();
   
}