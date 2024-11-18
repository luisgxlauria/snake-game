#include <termios.h>
#include <unistd.h>
#include "keyboard.h"

static struct termios initialSettings, newSettings;
static int peekCharacter;
void keyboardInit()
void keyboardDestroy()
int keyhit()
int readch()
