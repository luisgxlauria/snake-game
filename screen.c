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