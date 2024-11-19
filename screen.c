#include "screen.h"
#include <stdio.h>

void screenHomeCursor() {
    printf("%s%s", ESC, HOMECURSOR);
}

void screenShowCursor() {
    printf("%s%s", ESC, SHOWCURSOR);
}

void screenHideCursor() {
    printf("%s%s", ESC, HIDECURSOR);
}

void screenClear() {
    printf("%s%s", ESC, CLEARSCREEN);
    screenHomeCursor();
}

void screenUpdate() {
    fflush(stdout);
}

void screenSetColor(screenColor fg, screenColor bg) {
    printf("%s[3%dm", ESC, fg); // Foreground color
    printf("%s[4%dm", ESC, bg); // Background color
}

void screenGotoxy(int x, int y) {
    printf("%s[%d;%dH", ESC, y, x);
}

void screenBoxEnable() {
    printf("%s(0", ESC); // Enable box drawing mode
}

void screenBoxDisable() {
    printf("%s(B", ESC); // Disable box drawing mode
}

void screenInit(int drawBorders) {
    screenClear();
    if (drawBorders) {
        for (int i = SCRSTARTY; i <= SCRENDY; i++) {
            screenGotoxy(SCRSTARTX, i);
            printf("|");
            screenGotoxy(SCRENDX, i);
            printf("|");
        }
    }
    screenUpdate();
}

void screenDestroy() {
    screenClear();
    screenShowCursor();
}

void screenSetNormal() {
    printf("%s%s", ESC, NORMALTEXT); // Resetando as cores e o estilo do texto
    screenUpdate();
}
