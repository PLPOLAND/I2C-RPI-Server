#ifndef COMMAND_H
#define COMMAND_H

#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <cmath>

class Command
{
public:
    Command();
    ~Command();
    Command(uint8_t* ,int , int);

    void setMsg(uint8_t*, int);
    int getMsg(uint8_t*, int);
    void setResponse(uint8_t*, int);
    int getResponse(uint8_t*, int);
    void setAddr(int);
    int getAddr();
    int getMsgSize();

    std::string toString();
private:
    /// Message to send to slave
    uint8_t msg[10];
    /// nuber of bytes in msg
    int msg_size;
    /// response from slave
    uint8_t response[10];
    /// number of bytes in response
    int response_size;

    /// adress of slave to send msg
    int destAddr;


    bool correctAdress(int);
};

#endif