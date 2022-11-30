#include "../include/NetServer.hpp"

NetServer::NetServer()
{
    buffor = new char[1024];
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
    delete buffor;
}

void NetServer::connect() {
    if ((gnd = accept(server_file, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
}

void NetServer::write(uint8_t* msg, int size) {
    send(gnd, msg, size, 0);
}

int NetServer::recv() {
    return read(gnd, buffor, 1024);
}