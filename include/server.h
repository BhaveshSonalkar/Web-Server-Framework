#pragma once

#include <iostream>
#include <string>
#include <netinet/in.h> // for sockaddr_in
#include <unistd.h>     // for close

class Server
{
private:
    int server_fd;
    struct sockaddr_in address;
    int port;

    // setup the server socket
    void setup_socket();

    // main loop to handle client connections
    void run();

public:
    Server(int port);
    ~Server();
    void start();
};
