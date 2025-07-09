#include "server.h"
#include "urls.h"
#include "logger.h"
#include <iostream>
#include <cstdlib>

int main(int argc, char *argv[])
{
    setup_logging(); // Initialize logging

    int port = 8080; // Default port
    if (argc > 1)
    {
        port = std::atoi(argv[1]);
        if (port == 0)
        {
            spdlog::error("Invalid port number provided. Using default port 8080.");
            port = 8080;
        }
    }

    spdlog::info("Starting server...");

    Server server(port);
    // Register routes externally using the server's router
    register_urls(server.getRouter());

    server.start();
}