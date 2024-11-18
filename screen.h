#ifndef SCREEN_H
#define SCREEN_H

#include <stdio.h>

/* ANSI Terminal Control Sequences */
#define ESC            "\033"
#define NORMALTEXT     "[0m"
#define BOLDTEXT       "[1m"
#define HOMECURSOR     "[H"
#define SHOWCURSOR     "[?25h"
#define HIDECURSOR     "[?25l"
#define CLEARSCREEN    "[2J"

#endif / SCREEN_H */

void screenHomeCursor();
void screenShowCursor();
void screenHideCursor();
void screenClear();
void screenUpdate();
typedef enum {
    BLACK, RED, GREEN, BROWN, BLUE, MAGENTA, CYAN, LIGHTGRAY,
    DARKGRAY, LIGHTRED, LIGHTGREEN, YELLOW, LIGHTBLUE, LIGHTMAGENTA, LIGHTCYAN, WHITE
} screenColor;

void screenSetColor(screenColor fg, screenColor bg);