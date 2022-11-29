#ifndef NETSERVER_H
#define NETSERVER_H

#pragma once

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

class NetServer
{
public:
    NetServer();
    ~NetServer();

    struct sockaddr_in address;
    const int addrlen = sizeof(address);
    char* buffor;

    /**
     * Running "accept". Makes server to wait for the connection.
    */
    void connect();
    /**
     * Recievs data from client, save it to buffor
     * @return int - how many bytes was recieved
    */
    int recv();
    /**
     * Sends data to client
     * @param msg data to send
     * @param size size of data
     */
    void write(uint8_t* msg, int size);

private:
    int server_file;
    int gnd; 

};

#endif