#include <stdint.h>
#include <stddef.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY ((volatile uint16_t*) 0xB8000)

static int vga_column = 0;
static int vga_row = 0;
static uint8_t vga_color = 0x0F; // Biały tekst na czarnym tle

void vga_clear(void) {
    vga_column = 0;
    vga_row = 0;
    // Dokładnie 80 * 25 = 2000 słów 16-bitowych!
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        VGA_MEMORY[i] = (uint16_t)' ' | ((uint16_t)vga_color << 8);
    }
}

void vga_putchar(char c) {
    if (c == '\n') {
        vga_column = 0;
        vga_row++;
    }
    else if (c == '\b'){
    	if (vga_column > 0){
    		vga_column--;
    	}
    	int index = vga_row * VGA_WIDTH + vga_column;
    	VGA_MEMORY[index] = (uint16_t)' ' | ((uint16_t)vga_color << 8);
    } else {
        int index = vga_row * VGA_WIDTH + vga_column;
        VGA_MEMORY[index] = (uint16_t)c | ((uint16_t)vga_color << 8);
        vga_column++;
        if (vga_column >= VGA_WIDTH) {
            vga_column = 0;
            vga_row++;
        }
    }

    // Zabezpieczenie przed wyjściem poza dół ekranu
    if (vga_row >= VGA_HEIGHT) {
        vga_clear(); // Narazie czyścimy ekran, gdy dojdziemy do dna
    }
}

void vga_print(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        vga_putchar(str[i]);
    }
}
