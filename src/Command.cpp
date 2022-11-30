#include "Command.h"

Command::Command()
{
    msg = "";
    destAddr = 127;
}

Command::~Command()
{

}

Command::Command(std::string msg, int adress) {
    try {
        setAddr(adress);
        setMsg(msg);
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

void Command::setMsg(std::string msg) {
    this->msg = msg;
}

std::string Command::getMsg() {
    return this->msg;
}

int Command::getAddr() {
    return this->destAddr;
}


std::string Command::toString() {
    std::string msg = "";
    msg += "Command:(msg=\"";
    msg += this->msg;
    msg += "\"; destAddr=";
    msg += destAddr;
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