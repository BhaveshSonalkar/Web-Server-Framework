#include "server.h"
#include "urls.h"
#include "logger.h"

int main()
{
    setup_logging(); // Initialize logging

    spdlog::info("Starting server...");

    Server server(8080);
    // Register routes externally using the server's router
    register_urls(server.getRouter());

    server.start();
}