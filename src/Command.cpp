#include "../include/Command.h"

/**
 * @brief Construct a new Command object
 * 
 * @param id id of command
 */
Command::Command(int id)
{
    this->id = id;
    this->msg_size = 0;
    this->destAddr = 127;
    this->state = CREATED;
}

Command::~Command()
{

}

/**
 * @brief Construct a new Command object
 * @param msg uint8_t array with message to send
 * @param size size of msg
 * @param adress adress of slave to send msg
 */
Command::Command(int id, uint8_t * msg,int size, int adress) {
    this->id = id;
        try {
        setAddr(adress);
        setMsg(msg,size);
        for (size_t i = 0; i < 10; i++)
        {
            response[i] = 0;
        }
        response_size = 0;
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

///TODO: check if response is not empty

/**
 * @brief gets response to buff. Copy min(size,response_size) bytes!
 * @param buff buffer to copy response to
 * @param size size of buff
 * @return number of copied bytes
 */
int Command::getResponse(uint8_t* buff, int size) {
    if (size < 10)
    {
        std::memcpy(buff, response, std::min(size,response_size));
    }
    else{
        //TODO ERROR
    }
    
    return std::min(size,response_size);
}

/**
 * @brief sets response to Command
 * @param resp response bytes to set
 * @param size size of resp
 */
void Command::setResponse(uint8_t* resp, int size) {
    if (size<10){
        std::memcpy(this->response,resp,size);
        this->response_size = size;
    }
    else{
        //TODO ERROR!
    }
}

int Command::getResponseSize() {
    return this->response_size;
}

int Command::getId() {
    return this->id;
}

Command::State Command::getState() {
    return this->state;
}

void Command::setState(Command::State state) {
    this->state = state;
}

/**
 * @brief returns string with Command info
 * @return string with Command info
 */
std::string Command::toString() {
    std::string msg = "";
    msg += "Command:(msg=\"";
    for (size_t i = 0; i < msg_size; i++)
    {
        msg += std::to_string(this->msg[i]);
        msg += ", ";
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
    return !(adr < 8 || adr>127);
}


Command Command::fromJsonObj(nlohmann::json obj) {
    Command cmd(obj["id"]);
    cmd.setAddr(obj["address"]);
    uint8_t msg[10];
    uint8_t size = obj["command"].size();
    for (size_t i = 0; i < size; i++)
    {
        msg[i] = obj["command"][i];
    }
    cmd.setMsg(msg,size);
    return cmd;
}