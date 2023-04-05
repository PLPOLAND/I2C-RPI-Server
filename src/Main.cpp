#include "../include/Main.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

Main::Main()
{
    i2c = new I2Ctalker;
    net = new NetServer;
    i2c->start();
}

Main::~Main()
{
    delete i2c;
    delete net;
}

void Main::operator()(){
    i2c->scan();
    // uint8_t tmp[] = { 0,2,0,4,5,6,7 };
    // // i2c->send(tmp, 7, 16);
    // // _delay(100);
    // for(int i=0; i < 1000;i++){
    //     i2c->send(tmp, 7, 16);
    //     _delay(100);
    // }
    // while (i2c->sentQueueSize()>0)
    // {
    //     _delay(100);
    // }
    net->connect();
    for(;;){
        int recieved = net->recv();
        if(recieved<=0)
            break;
        try{
            json j = json::parse(net->buffor);
            cout << j["command"] << endl;
            auto tmp = std::to_string((int)j["id"]);
            cout << tmp.length() << endl;
            json j2 = {
                {"id", j["id"]},
                {"responseString", "ack"}
            };
            net->write(j2.dump() + "\n", (j2.dump() + "\n").length());
        }
        catch(json::parse_error& e){
            cout << "Error while parsing json: " << e.what() << endl;
            cout << "Error on parsing: " << net->buffor << endl;
            continue;
        }
        // for(int i =0; i<1024; i++){
        //     cout<<net->buffor[i];
            
        // }
        cout <<endl;
        // i2c->send((uint8_t*)net->buffor,recieved, 16);
    }
    while (i2c->sentQueueSize() > 0)
        {
            _delay(100);
        }
}