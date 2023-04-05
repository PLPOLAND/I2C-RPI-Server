#include "../include/NetServer.hpp"
#include <iostream>

NetServer::NetServer()
{
    charBuffor = new char[1024];
    charBuffor[1023] = 0;
    //Create socket file descriptor
    if ((server_file = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }


    //attach to port

    int opt = 1;
    if (setsockopt(server_file, SOL_SOCKET,
        SO_REUSEADDR | SO_REUSEPORT, &opt,
        sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(9803);

    //attaching socket to the port

    if (bind(server_file, (struct sockaddr*)&address,
        sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_file, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }




}

NetServer::~NetServer()
{
    close(gnd);
    delete charBuffor;
}

void NetServer::connect() {
    if ((gnd = accept(server_file, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
}

void NetServer::write(std::string msg, int size) {
    std::cout << "Sending: " << msg << std::endl;
    int tmp = send(gnd, msg.c_str(), size, 0);
    std::cout << "Sent: " << msg << " :"<< tmp << std::endl;
}

int NetServer::recv() {

    int bytesRead = read(gnd, charBuffor, 1024);

    buffor = std::string(charBuffor).substr(0, bytesRead);

    return bytesRead;
}