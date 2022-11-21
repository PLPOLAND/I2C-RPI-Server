#include <iostream>
#include <unistd.h>
#include "./TwoWire/twowire.h"

int main(){
    TwoWire* tw = new TwoWire();
    tw->setPullup();
    tw->begin(soft_I2C, 8, 9);//SDA 4, SCL 5
    tw->setDebug(true);
    std::cout << tw->linestatus() << std::endl;
    char* buf = "012abscdstggbzxcvAd";
    tw->setSlave(0x08);
    std::cout << tw->i2c_write(buf, 19) << std::endl;
    std::cout << tw->linestatus() << std::endl;
    std::cout << "LS" <<std::endl;
    tw->flush();
    tw->close();
}