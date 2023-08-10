#include <stdio.h>

void clear_screen() {
    printf("\033[2J\033[1;1H"); // Limpiar la pantalla
}

int main() {
    int x = 0;
    int y = 0;
    char letter = 'A';

    while (1) {
        clear_screen(); // Limpiar la pantalla

        // Mover el cursor a la posición (x, y)
        printf("\033[%d;%dH", y + 1, x + 1);

        printf("%c", letter); // Imprimir la letra

        char key = getchar(); // Leer la tecla presionada

        switch (key) {
            case 'w':
            case 'W':
                y--;
                break;
            case 's':
            case 'S':
                y++;
                break;
            case 'a':
            case 'A':
                x--;
                break;
            case 'd':
            case 'D':
                x++;
                break;
        }
    }

    return 0;
}
