#include "print.h"

void kernel_main(){
    print_clear();
    print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLUE);
    print_str("Welcome to GOS64");
    print_newline();
    print_str("This is an OS that can do a bunch of cool shit");
}