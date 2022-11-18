#include <twowire.h>
#include <iostream>

int main(){
    TwoWire* tw = new TwoWire();
    tw->begin(soft_I2C,4,5);//SDA 4, SCL 5

    tw->i2c_write("LS",2);

    std::cout << "LS" <<std::endl;
}