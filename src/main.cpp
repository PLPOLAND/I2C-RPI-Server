#include <ctime>
#include <iostream>
#include <unistd.h>
#include "../include/twowire.h"
#include <wiringPiI2C.h>

#include "../include/NetServer.hpp"

// #include <netinet/in.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <sys/socket.h>
// #include <unistd.h>

#include <thread>

using namespace std;

int main(){

    // clock_t t;

    // TwoWire* tw = new TwoWire();
    // tw->setPullup();
    // tw->begin(soft_I2C, 8, 9);
    // tw->setClock(400);
    // tw->setDebug(true);
    // std::cout << tw->linestatus() << std::endl;
    // char* buf = "012abscdstggbzxcvAd";
    // char read[255];
    // t = clock();
    // for (;;)
    // {
    //     std::cout<< "diff = " << (1000*(clock() - t))/CLOCKS_PER_SEC<<std::endl;
    //     tw->setSlave(0x10);
    //     std::cout << tw->i2c_write(buf, 19) << std::endl;
    //     tw->setSlave(0x10);
    //     std::cout << tw->i2c_read(read, 20) << std::endl;
    //     for (size_t i = 0; i < 20; i++){
    //         std::cout << (int)read[i] << " ";    
    //     }
    //         std::cout << std::endl;    
    //     t = clock();
    // }
    // std::cout << tw->linestatus() << std::endl;
    
    // // delay(10);
    // // std::cout << "LS" <<std::endl;
    // tw->DispClockStretch();
    // tw->flush();
    // tw->close();
    
    /////////////////////////////////////////////////////////////////
    //                netTEST
    /////////////////////////////////////////////////////////////////

    // NetServer* server = new NetServer;

    // server->connect();
    // server->recv();
    // std::cout<< server->buffor;
    
    // server->write((uint8_t*)"HakunaMatata", 13);

    // int server_fd, new_socket, valread;
    // struct sockaddr_in address;
    // int opt = 1;
    // int addrlen = sizeof(address);
    // char buffer[1024] = {0};
    // char *hello = "It's me I2C BOY";

    // // Creating socket file descriptor
    // if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    // {
    //     perror("socket failed");
    //     exit(EXIT_FAILURE);
    // }

    // // Forcefully attaching socket to the port 8080
    // if (setsockopt(server_fd, SOL_SOCKET,
    //                SO_REUSEADDR | SO_REUSEPORT, &opt,
    //                sizeof(opt)))
    // {
    //     perror("setsockopt");
    //     exit(EXIT_FAILURE);
    // }
    // address.sin_family = AF_INET;
    // address.sin_addr.s_addr = INADDR_ANY;
    // address.sin_port = htons(9803);

    // // Forcefully attaching socket to the port 8080
    // if (bind(server_fd, (struct sockaddr *)&address,
    //          sizeof(address)) < 0)
    // {
    //     perror("bind failed");
    //     exit(EXIT_FAILURE);
    // }
    // if (listen(server_fd, 3) < 0)
    // {
    //     perror("listen");
    //     exit(EXIT_FAILURE);
    // }
    // if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
    //                          (socklen_t *)&addrlen)) < 0)
    // {
    //     perror("accept");
    //     exit(EXIT_FAILURE);
    // }
    // valread = read(new_socket, buffer, 1024);
    // printf("%s\n", buffer);
    // send(new_socket, hello, strlen(hello), 0);
    // printf("MSG sent\n");

    // // closing the connected socket
    // close(new_socket);
    // // closing the listening socket
    // shutdown(server_fd, SHUT_RDWR);

    ///////////////////////////////////////////////////
    //////////////////THREAD TEST//////////////////////
    ///////////////////////////////////////////////////

    thread t1([](){
        cout<< "hi" << endl;
    });

    t1.join();

    return 0;
}