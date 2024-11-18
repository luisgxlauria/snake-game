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

void timerDestroy()
{
    delay = -1;
}

    void timerUpdateTimer(int valueMilliSec)
    {
        delay = valueMilliSec;
        gettimeofday(&timer, NULL);
    }

int timerTimeOver()
{
    int ret = 0;

    if (getTimeDiff() > delay)
    {
        ret = 1;
        gettimeofday(&timer, NULL);
    }

    return ret;
}

void timerPrint()
{
    printf("Timer:  %d", getTimeDiff());
}