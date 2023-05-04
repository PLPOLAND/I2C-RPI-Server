#ifndef I2CTALKER_H
#define I2CTALKER_H

#pragma once

#include <string>
#include "twowire.h"
#include "Command.h"
#include <queue>
#include <thread>
#include <atomic>

using namespace std;

class I2Ctalker
{
public:
    I2Ctalker();
    ~I2Ctalker();

    void send(uint8_t*, int, int);
    void sendAndRecive(Command*);
    string getMsg();

    void start();
    void scan();
    int sentQueueSize();

private:
    std::atomic<bool> stop = false;

    TwoWire* arduino; //obj to send and read to/from slaves

    queue<Command*> toSend; //buffor for messages to send
    queue<Command*> recieved; //buffor for messages recieved from slaves

    thread* thr = nullptr;


    void _send(Command comm);
    void _send(uint8_t* msg, int size, int adress);
    
    void recieve(int adress);
    void recieve(Command* comm);

    void operator()();


    bool correctAdress(int);


};

#endif