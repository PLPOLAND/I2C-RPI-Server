#ifndef COMMAND_H
#define COMMAND_H

#pragma once

#include <iostream>
#include <string>

class Command
{
public:
    Command();
    ~Command();
    Command(std::string , int);

    void setMsg(std::string);
    void setAddr(int);
    std::string getMsg();
    int getAddr();

    std::string toString();
private:
    std::string msg;
    int destAddr;


    bool correctAdress(int);
};

#endif