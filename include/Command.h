#ifndef COMMAND_H
#define COMMAND_H

#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
class Command
{
public:
    Command(int);
    ~Command();
    Command(int, uint8_t* ,int , int);

    enum State {
        CREATED,
        SENT,
        RECIEVED,
        PROCESSED,
        ERROR,
    };

    void setMsg(uint8_t*, int);
    int getMsg(uint8_t*, int);
    void setResponse(uint8_t*, int);
    int getResponse(uint8_t*, int);
    void setAddr(int);
    int getAddr();
    int getMsgSize();
    int getResponseSize();
    int getId();
    State getState();
    void setState(State);

    static Command fromJsonObj(nlohmann::json);

    std::string toString();

    
private:
    /// id of command
    int id;
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

    /// state of processing the command
    State state;

    /// checks if adress is correct
    bool correctAdress(int);
};



#endif