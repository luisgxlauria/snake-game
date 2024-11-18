#include "timer.h"
#include <sys/time.h>
#include <stdio.h>

static struct timeval timer, now;
static int delay = -1;

void timerInit(int valueMilliSec)
{
    delay = valueMilliSec;
    gettimeofday(&timer, NULL);
}