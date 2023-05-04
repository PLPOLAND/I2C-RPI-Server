#ifndef MAIN_H
#define MAIN_H

#include "I2Ctalker.h"
#include "NetServer.hpp"
#include "Command.h"
#include <thread>
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>

#pragma once

class Main
{
public:
    Main();
    ~Main();
    void operator()();


    void runCommunication();
    void processCommands();

    void stop();
private:

    thread* thr = nullptr;

    bool _stop = false;
    std::vector<Command*> commands;
    I2Ctalker* i2c;
    NetServer* net;
};

#endif