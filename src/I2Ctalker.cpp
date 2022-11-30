#include "../include/I2Ctalker.h"

I2Ctalker::I2Ctalker()
{
    arduino = new TwoWire;
}

I2Ctalker::~I2Ctalker()
{
    delete arduino;
}

/**
 * @brief Sends Command to slave
 * @param comm command to send
 * @see Command
 */
void I2Ctalker::send(Command comm){
    this->send(comm.getMsg(), comm.getAddr());
}

/**
 * @brief Sends msg to slave on given adress by I2C
 * @param msg - message to send
 * @param adress - slave (destination) adress (9- 127)
 */
void I2Ctalker::send( string msg, int adress){
    arduino->setSlave(adress);
    //TODO sprawdzić czy istnieje taki adres (NACK)
    while (arduino->i2c_write(msg.c_str(), msg.length()) != I2C_OK)
    {
        //TODO dodać sprawdzanie czy slave się nie zawiesił!    
    }
    
}

/**
 * @brief gets next msg from buffor
 * @return string msg
 */
string I2Ctalker::getMsg(){
    return "";
}

/**
 * @brief Checks I2C adress is in correct interval
 * @param adr - number to check
 * @return true - if adress is in correct interval
 */
bool I2Ctalker::correctAdress(int adr){
    return !(adr<9 || adr>127);
}