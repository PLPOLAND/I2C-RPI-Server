#include "../include/Main.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

Main::Main()
{
    i2c = new I2Ctalker;
    net = new NetServer;
    // i2c->start();
}

Main::~Main()
{
    delete i2c;
    delete net;
}

void Main::operator()(){
    // i2c->scan();
    Command cmd(0);
    cmd.setMsg(((uint8_t*)"I"),1);
    cmd.setAddr(0x0E);
    i2c->sendAndRecive(&cmd);
    cout << cmd.toString() << endl;
    this->thr = new std::thread(&Main::runCommunication, this);
    // for(;;)
    // _delay(1000);
    
    while (i2c->sentQueueSize() > 0)
        {
            _delay(100);
        }
}

void Main::runCommunication(){
    net->connect(); //wait for connection
    while(!this->_stop) {
        int recieved = net->recv(); // wait for data, return number of bytes recieved, recieve data to net->buffor
        if (recieved <= 0)
            continue;
        try {
            json j = json::parse(net->buffor); // parse json from buffor
            Command cmd = Command::fromJsonObj(j); // create command from json
            cout << cmd.toString() << endl; // print command info
            this->commands.push_back(&cmd); // add command to commands vector
            auto tmp = std::to_string((int)j["id"]);
            cout << tmp.length() << endl;
        }
        catch (json::parse_error& e) {
            cout << "Error while parsing json: " << e.what() << endl;
            cout << "Error on parsing: " << net->buffor << endl;
            continue;
        }
        for_each(commands.begin(), commands.end(), [this](Command* cmd) {
            if (cmd->getState() == Command::State::CREATED) { // command was created
                i2c->sendAndRecive(cmd); // send command to slave and recive response
                cmd->setState(Command::State::SENT); // set state to sent
                cmd->setState(Command::State::RECIEVED); // set state to recieved

            }
            else if (cmd->getState() == Command::State::RECIEVED) { // command was sent to slave and response was recieved
                try {
                    json j;
                    j["id"] = cmd->getId();
                    j["response"] = json::array();
                    uint8_t buff[10];
                    cmd->getResponse(buff, cmd->getResponseSize());
                    for (size_t i = 0; i < cmd->getResponseSize(); i++)
                    {
                        j["response"].push_back(buff[i]);
                    }
                    cout << "Sending response: " << j.dump() << endl;
                    net->write(j.dump(), j.dump().length());
                    cmd->setState(Command::State::PROCESSED);
                }
                catch (json::parse_error& e) {
                    cout << "Error while parsing json: " << e.what() << endl;
                    cout << "Error on parsing: " << net->buffor << endl;
                    return;
                }
            }

        });
        cout << endl;
    }
}

void Main::processCommands() {
    // while (!this->_stop) {
    //     for_each(commands.begin(), commands.end(), [this](Command* cmd) {
    //         if (cmd->getState() == Command::State::CREATED) { // command was created
    //             i2c->sendAndRecive(cmd); // send command to slave and recive response
    //             cmd->setState(Command::State::SENT); // set state to sent
    //             cmd->setState(Command::State::RECIEVED); // set state to recieved

    //         }
    //     });
    // }
}

void Main::stop(){
    this->_stop = true;
}