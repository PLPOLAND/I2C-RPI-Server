#ifndef WIRINGPISIMULATE_H
#define WIRINGPISIMULATE_H

#pragma once
#include<unistd.h>

#define PUD_OFF 0
#define PUD_UP 1

#define INPUT 1
#define OUTPUT 0

#define LOW 0
#define HIGH 1

void pullUpDnControl(unsigned char line, int mode);

void pinMode(unsigned char line, int mode);

void digitalWrite(unsigned char line, int mode);

int digitalRead(unsigned char line);
void wiringPiSetup();

void delay(__uint64_t usec);


#endif