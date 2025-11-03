#include "io.h"


struct Char {
    uint8_t character;
    uint8_t color;
};

const static size_t NUM_COLS = 80;
const static size_t NUM_ROWS = 25;
#define MAX_INPUT_BUFFER_SIZE 256


struct Char* buffer = (struct Char*) 0xb8000;


char input_buffer[MAX_INPUT_BUFFER_SIZE];
size_t input_buffer_index = 0;
bool input_ready = false;


size_t col = 0;
size_t row = 0;
uint8_t color = PRINT_COLOR_WHITE | PRINT_COLOR_BLACK << 4;


void clear_row(size_t row) {
    struct Char empty = (struct Char) {
        character: ' ',
        color: color,
    };

    for (size_t col = 0; col < NUM_COLS; col++) {
        buffer[col + NUM_COLS * row] = empty;
    }
}

void print_clear() {
    for (size_t i = 0; i < NUM_ROWS; i++) {
        clear_row(i);
    }
    row = 0;
    col = 0;
    print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK); // Reset color to default
}

void print_set_color(uint8_t foreground, uint8_t background) {
    color = foreground + (background << 4);
}

void print_newline() {
    col = 0;

    if (row < NUM_ROWS - 1) {
        row++;
        return;
    }

    for (size_t i = 1; i < NUM_ROWS; i++) {
        for (size_t j = 0; j < NUM_COLS; j++) {
            buffer[j + NUM_COLS * (i - 1)] = buffer[j + NUM_COLS * i];
        }
    }

    clear_row(NUM_ROWS - 1);
}

void print_char(char character) {
    // Handle backspace: Move cursor back and write a space character
    if (character == '\b') {
        if (col > 0) {
            col--;
            buffer[col + NUM_COLS * row] = (struct Char) {
                character: ' ',
                color: color,
            };
        }
        return;
    }

    if (character == '\n') {
        print_newline();
        return;
    }

    if (col >= NUM_COLS) {
        print_newline();
    }

    buffer[col + NUM_COLS * row] = (struct Char) {
        character: (uint8_t) character,
        color: color,
    };

    col++;
}

void print_str(char* str) {
    for (size_t i = 0; 1; i++) {
        char character = (uint8_t) str[i];

        if (character == '\0') {
            return;
        }

        print_char(character);
    }
}

void initialize_input() {
    // Ensure the input buffer is zeroed out and state is reset on OS start
    for(int i = 0; i < MAX_INPUT_BUFFER_SIZE; i++) {
        input_buffer[i] = '\0';
    }
    input_ready = false;
    input_buffer_index = 0;
}


// This function is called by the Assembly ISR
void handle_keyboard_input(uint8_t scan_code){
    char character = scan_code_to_ascii(scan_code);

    if (character == '\b') {  // Backspace
        if (input_buffer_index > 0) {
            input_buffer_index--;  // Remove the last character from the buffer
            input_buffer[input_buffer_index] = '\0'; // Null-terminate
            print_char('\b'); // Echo backspace to the screen
        }
    } else if (character == '\n') {  // Enter key
        input_buffer[input_buffer_index] = '\0';  // Null-terminate the buffer
        input_ready = true;  // Signal that input is complete
        print_char('\n'); // Move to the next line
    } else if (character != 0 && input_buffer_index < MAX_INPUT_BUFFER_SIZE - 1) {  // Printable character
        input_buffer[input_buffer_index] = character;  // Add to buffer
        input_buffer_index++;
        print_char(character); // Echo character to screen
    }
}


char* read_input(){
    input_ready = false;
    input_buffer_index = 0;

    // Zero out the buffer before use
    for(int i = 0; i < MAX_INPUT_BUFFER_SIZE; i++) {
        input_buffer[i] = '\0';
    }

    while(!input_ready){
        // Halt the CPU until an interrupt (the keyboard) occurs
        __asm__ volatile("hlt");
    }
    
    return input_buffer;
}


// Function to convert scan code to ASCII (existing code)
char scan_code_to_ascii(uint8_t scan_code) {
    static bool shift_pressed = false;

    // Handle special keys
    switch (scan_code) {
        case 0x2A:  // Left Shift press
        case 0x36:  // Right Shift press
            shift_pressed = true;
            return 0;
        case 0xAA:  // Left Shift release
        case 0xB6:  // Right Shift release
            shift_pressed = false;
            return 0;
        case 0x1C:  // Enter key
            return '\n';
        case 0x0E:  // Backspace key
            return '\b';
        // Add more special keys as needed (e.g., Caps Lock, Ctrl, Alt)
    }

    // Lookup table for unshifted characters
    static const char unshifted_map[256] = {
        0,   0,   '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', // 0x00 - 0x0E
        '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', // 0x0F - 0x1D (1C is Enter, 1D is Ctrl)
        0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',   0, '\\', // 0x1E - 0x2C (2A/36 is Shift)
        'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0, // 0x2D - 0x37
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 0x38 - 0x47 (Functional keys/Numpad)
        // ... rest of the map, mostly 0 for keys not needing shift
    };

    // Lookup table for shifted characters
    static const char shifted_map[256] = {
        0,   0,   '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
        '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
        0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '\"', '~',   0, '|',
        'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0, '*', 0, ' ', 0,
        // ...
    };

    // Check for character based on shift state
    if (scan_code < 256) {
        if (shift_pressed) {
            return shifted_map[scan_code];
        } else {
            return unshifted_map[scan_code];
        }
    }

    return 0; // Unknown scan code
}