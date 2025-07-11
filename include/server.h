#pragma once

#include <iostream>
#include <string>
#include <netinet/in.h> // for sockaddr_in
#include <unistd.h>     // for close
#include "router.h"
#include "thread_pool.h"

class Server
{
public:
    Server(int port);
    ~Server();
    void start();

    // Expose the router for external route registration.
    Router &getRouter();

private:
    int server_fd;
    struct sockaddr_in address;
    int port;
    Router router;
    ThreadPool pool;

    // setup the server socket
    void setup_socket();

    // main loop to handle client connections
    void run();

    // handle single client connection
    void client_connection_handler(int client_fd);
};
