#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>



enum{
    PRINT_COLOR_BLACK = 0,
    PRINT_COLOR_BLUE = 1,
    PRINT_COLOR_GREEN = 2,
    PRINT_COLOR_CYAN = 3,
    PRINT_COLOR_RED = 4,
    PRINT_COLOR_MAGENTA = 5,
    PRINT_COLOR_BROWN = 6,
    PRINT_COLOR_LIGHT_GRAY = 7,
    PRINT_COLOR_DARK_GRAY = 8,
    PRINT_COLOR_LIGHT_BLUE = 9,
    PRINT_COLOR_LIGHT_GREEN = 10,
    PRINT_COLOR_LIGHT_CYAN = 11,
    PRINT_COLOR_LIGHT_RED = 12,
    PRINT_COLOR_PINK = 13,
    PRINT_COLOR_YELLOW = 14,
    PRINT_COLOR_WHITE = 15,
};




#include <stdint.h>

// Scan code to ASCII mapping for a standard US QWERTY keyboard
static const char scan_code_to_ascii_map[256] = {
    0,   0,   '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', // 0x00 - 0x0E
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',     // 0x0F - 0x1C
    0,    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,       // 0x1D - 0x2A
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ',    // 0x2B - 0x39
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,        // 0x3A - 0x45
    '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', '.',            // 0x46 - 0x53
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,        // 0x54 - 0x5F
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,        // 0x60 - 0x6B
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,        // 0x6C - 0x77
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,        // 0x78 - 0x83
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,        // 0x84 - 0x8F
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,        // 0x90 - 0x9B
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,        // 0x9C - 0xA7
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,        // 0xA8 - 0xB3
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,        // 0xB4 - 0xBF
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,        // 0xC0 - 0xCB
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,        // 0xCC - 0xD7
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,        // 0xD8 - 0xE3
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,        // 0xE4 - 0xEF
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,        // 0xF0 - 0xFB
};

// Scan code to ASCII mapping for shifted keys
static const char scan_code_to_ascii_shift_map[256] = {
    0,   0,   '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b', // 0x00 - 0x0E
    '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',     // 0x0F - 0x1C
    0,    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~', 0,       // 0x1D - 0x2A
    '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0, '*', 0, ' ',     // 0x2B - 0x39
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,        // 0x3A - 0x45
    '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', '.',            // 0x46 - 0x53
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,        // 0x54 - 0x5F
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,        // 0x60 - 0x6B
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,        // 0x6C - 0x77
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,        // 0x78 - 0x83
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,        // 0x84 - 0x8F
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,        // 0x90 - 0x9B
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,        // 0x9C - 0xA7
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,        // 0xA8 - 0xB3
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,        // 0xB4 - 0xBF
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,        // 0xC0 - 0xCB
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,        // 0xCC - 0xD7
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,        // 0xD8 - 0xE3
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,        // 0xE4 - 0xEF
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,        // 0xF0 - 0xFB
};



void print_clear();
void print_char(char character);
void print_str(char* string);
void print_set_color(uint8_t foreground, uint8_t background);
void print_newline();

void initialize_input();
void clear_input_buffer();
void handle_keyboard_input(uint8_t scan_code);
char* read_input();

char scan_code_to_ascii(uint8_t scancode);