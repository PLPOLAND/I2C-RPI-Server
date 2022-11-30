#ifndef I2CTALKER_H
#define I2CTALKER_H

#pragma once

#include <string>
#include "twowire.h"
#include "Command.h"
#include <vector>
#include <thread>

using namespace std;

class I2Ctalker
{
public:
    I2Ctalker();
    ~I2Ctalker();

    string getMsg();

    
private:
    TwoWire* arduino; //obj to send and read to/from slaves

    vector<Command> toSend; //buffor for messages to send
    vector<Command> recieved; //buffor for messages recieved from slaves

    thread* thread = nullptr;

    void send(Command comm);
    void send(string msg, int adress);
    bool correctAdress(int);
};

#endif