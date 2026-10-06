// keyboard.c
#include "io.h"
#include <stdint.h>

// Tablica mapowania Scan Code (Set 1) -> ASCII
static const char scancode_ascii[] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
  '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
     0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
     0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    '*', 0, ' '
};

char keyboard_getchar(void) {
    // 1. Sprawdzamy czy port statusu PS/2 (0x64) ma bit 0 ustawiony na 1 (dane gotowe)
    if (inb(0x64) & 0x01) {
        uint8_t scancode = inb(0x60); // Odczytujemy bajt z portu danych

        // Jeśli scancode jest większy lub równy 0x80, oznacza to ZWOLNIENIE klawisza.
        // Ignorujemy go i czekamy na kolejne wciśnięcie.
        if (scancode & 0x80) {
            return 0;
        }

        // Jeśli scancode mieści się w naszej tablicy ASCII, zwracamy znak
        if (scancode < sizeof(scancode_ascii)) {
            return scancode_ascii[scancode];
        }
    }
    
    return 0; // Brak nowego znaku
}
