#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

int main() {

    static struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    int key = 0;
    while (1) {
        key = getc(stdin);
        if (key == '\033') {
            getc(stdin);
            printf("ARROW PRESSED! ");
            switch(getc(stdin)) {
                case 'A': printf("up\n"); break;
                case 'B': printf("down\n"); break;
                case 'C': printf("right\n"); break;
                case 'D': printf("left\n"); break;
            }
        } else {
            printf("%d\n", key);
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return 0;
}