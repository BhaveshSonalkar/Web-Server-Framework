#pragma once

#include <iostream>
#include <string>
#include <netinet/in.h> // for sockaddr_in
#include <unistd.h>     // for close
#include "router.h"

class Server
{
public:
    Server(int port);
    ~Server();
    void start();

private:
    int server_fd;
    struct sockaddr_in address;
    int port;
    Router router;

    // setup the server socket
    void setup_socket();

    // main loop to handle client connections
    void run();

    // register routes
    void register_routes();

    // handle single client connection
    void client_connection_handler();
};
