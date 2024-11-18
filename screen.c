#include "screen.h"

static inline void screenHomeCursor() {
    printf("%s%s", ESC, HOMECURSOR);
}

static inline void screenShowCursor() {
    printf("%s%s", ESC, SHOWCURSOR);
}

static inline void screenHideCursor() {
    printf("%s%s", ESC, HIDECURSOR);
}

static inline void screenClear() {
    printf("%s%s", ESC, CLEARSCREEN);
    screenHomeCursor();
}

static inline void screenUpdate() {
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