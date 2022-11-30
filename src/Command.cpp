#include "../include/Command.h"

Command::Command()
{
    msg_size = 0;
    destAddr = 127;
}

Command::~Command()
{

}

Command::Command(uint8_t * msg,int size, int adress) {
    try {
        setAddr(adress);
        setMsg(msg,size);
    }
    catch (const char* error) {
        std::cerr << error << std::endl;
    }
}

void Command::setAddr(int addr) {
    if (correctAdress(addr))
    {
        this->destAddr = addr;
    }
    else {
        throw "Addres must be in [9,127]!";
    }
}

void Command::setMsg(uint8_t* msg, int size) {
    if (size<10){
        std::memcpy(this->msg,msg,size);
        this->msg_size = size;
    }
    else{
        //TODO ERROR!
    }
}

/**
 * @brief copy msg to added buff. Copy min(size,msg_size) bytes!
 * @param buff buff to copy msg
 * @param size size of buff / how many bytes to copy
 * @return number of copied bytes
 */
int Command::getMsg(uint8_t* buff, int size) {
    if (size < 10)
    {
        std::memcpy(buff, msg, std::min(size,msg_size));
    }
    else{
        //TODO ERROR
    }
    
    return std::min(size,msg_size);
}

int Command::getAddr() {
    return this->destAddr;
}

int Command::getMsgSize(){
    return this->msg_size;
}


std::string Command::toString() {
    std::string msg = "";
    msg += "Command:(msg=\"";
    for (size_t i = 0; i < msg_size; i++)
    {
        msg += std::to_string(this->msg[i]);
        msg += " ";
    }
    msg += "\"; destAddr=\"";
    msg += std::to_string((int)destAddr);
    msg += "\")\n";
    return msg;
}


/**
 * @brief Checks I2C adress is in correct interval
 * @param adr - number to check
 * @return true - if adress is in correct interval
 */
bool Command::correctAdress(int adr) {
    return !(adr < 9 || adr>127);
}