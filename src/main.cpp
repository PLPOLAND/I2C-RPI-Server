#include <ctime>
#include <iostream>
#include <unistd.h>
#include "../include/twowire.h"

using namespace std;

int main(){

    clock_t t;

    TwoWire* tw = new TwoWire();
    tw->setPullup();
    tw->setClock(200);
    tw->begin(soft_I2C, 8, 9);
    tw->setDebug(true);
    std::cout << tw->linestatus() << std::endl;
    char* buf = "012abscdstggbzxcvAd";
    tw->setSlave(0x08);
    t = clock();
    for (;;)
    {
        std::cout<< "diff = " << (1000*(clock() - t))/CLOCKS_PER_SEC<<std::endl;
        std::cout << tw->i2c_write(buf, 19) << std::endl;
        t = clock();
    }
    std::cout << tw->linestatus() << std::endl;
    
    delay(10);
    std::cout << "LS" <<std::endl;
    tw->DispClockStretch();
    tw->flush();
    tw->close();
}