#include "../include/wiringPISimulate.h"


void pullUpDnControl(unsigned char line, int mode){

};

void pinMode(unsigned char line, int mode){

};

void digitalWrite(unsigned char line, int mode){

};

int digitalRead(unsigned char line){
    return 0;
};
void wiringPiSetup(){

};

void delay(__uint64_t usec){ 
    unsigned int microsecond = 1000000;
    usleep(3 * microsecond);//sleeps for 3 second
};