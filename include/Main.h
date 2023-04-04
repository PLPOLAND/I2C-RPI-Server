#ifndef MAIN_H
#define MAIN_H

#include "I2Ctalker.h"
#include "NetServer.hpp"
#include "Command.h"
#include <fstream>
#include <nlohmann/json.hpp>

#pragma once

class Main
{
public:
    Main();
    ~Main();
    void operator()();
private:
    I2Ctalker* i2c;
    NetServer* net;
};

#endif