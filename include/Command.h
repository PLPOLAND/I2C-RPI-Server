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
    void setAddr(int);
    int getMsg(uint8_t*, int);
    int getAddr();
    int getMsgSize();

    std::string toString();
private:
    uint8_t msg[10];
    int msg_size;
    int destAddr;


    bool correctAdress(int);
};

#endif