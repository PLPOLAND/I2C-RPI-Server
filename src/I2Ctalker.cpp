#include "../include/I2Ctalker.h"

I2Ctalker::I2Ctalker()
{
    arduino = new TwoWire;
    arduino->begin(soft_I2C,8,9);
}

I2Ctalker::~I2Ctalker()
{
    stop = true;
    if (thr!=nullptr)
    {
        this->thr->join();
    }
    
    delete arduino;
}

void I2Ctalker::start(){
    this->thr = new std::thread(&I2Ctalker::operator(), this);
}

void I2Ctalker::operator()(){
    while (!stop)
    {
        if (toSend.size() > 0)
        {
            _send(*toSend.front());//send msg
            recieve(toSend.front()->getAddr());//get response
            cout<<"send:"<<toSend.front()->toString()<<endl;
            delete toSend.front();//delete sent msg to clear memory
            toSend.pop();//delete from queue
        }
        else{
            // cout<<"Nothing to sent"<<endl;
            cout.flush();
            _delay(2);//to reduece processor usage
        }

    }
}

/**
 * @brief Sends Command to slave
 * @param comm command to send
 * @see Command
 */
void I2Ctalker::_send(Command comm){
    uint8_t* buff;
    buff = new uint8_t[comm.getMsgSize()];
    comm.getMsg(buff,comm.getMsgSize());
    
    this->_send(buff,comm.getMsgSize(), comm.getAddr());
    
    delete buff;
}

/**
 * @brief Sends msg to slave on given adress by I2C
 * @param msg - message to send
 * @param adress - slave (destination) adress (9- 127)
 */
void I2Ctalker::_send( uint8_t* msg,int size, int adress){
    arduino->setSlave(adress);
    //TODO sprawdzić czy istnieje taki adres (NACK)
    Wstatus ret;
    int i = 0;
    while ((ret = arduino->i2c_write(msg, size)) != I2C_OK)
    {
        cout << (int)ret<<endl;
        if(ret == I2C_SDA_HELD_LOW){
            _delay(10);
        }
        else if(i++>10 ){
            cout << endl<<"error"<<endl;
            exit(1);
        }
        //TODO dodać sprawdzanie czy slave się nie zawiesił!    
    }
    cout<<"msg sent"<<endl;
}

/**
 * @brief gets next msg from buffor
 * @return string msg
 */
string I2Ctalker::getMsg(){
    return "";
}

void I2Ctalker::recieve(int adress){
    uint8_t buff[8];
    arduino->setSlave(adress);
    //TODO sprawdzić czy istnieje taki adres (NACK)
    Wstatus ret;
    int i = 0;
    while ((ret = arduino->i2c_read(buff,8))!= I2C_OK){
        cout << (int)ret << endl;
        if (ret == I2C_SDA_HELD_LOW){
            _delay(10);
        }
        else if (i++ > 10) {
            cout << endl << "error" << endl;
            exit(1);
        }

        //TODO dodać sprawdzanie czy slave się nie zawiesił!  
    }
    Command * comm = new Command;

    comm->setAddr(adress);
    comm->setMsg(buff,8);
    this->recieved.push(comm);
}   

/**
 * @brief Checks I2C adress is in correct interval
 * @param adr - number to check
 * @return true - if adress is in correct interval
 */
bool I2Ctalker::correctAdress(int adr){
    return !(adr<8 || adr>127);
}

void I2Ctalker::send(uint8_t* msg, int size, int adress ){
    Command* comm = new Command;

    comm->setAddr(adress);
    comm->setMsg(msg, size);
    this->toSend.push(comm);
}

void I2Ctalker::scan(){

    for(int i=8; i<127; i++){
        Wstatus tmp;
        static uint8_t msg[1] = {0};
        arduino->setSlave(i);
        tmp = arduino->i2c_write(msg,1);
        cout<<i<<":\t";
        if(tmp != I2C_SDA_NACK){
            cout << "OK ("<<(int)tmp<<")"<<endl;
        }
        else{
            cout << "NOT CONNECTED(" << (int)tmp << ")" << endl;
        }
    }
}
int I2Ctalker::sentQueueSize(){
    return toSend.size();
}