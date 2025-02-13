#include "server.h"
#include "constants.h"
#include "http_parser.h"
#include <arpa/inet.h>
#include <spdlog/spdlog.h>

Server::Server(int port) : port(port), server_fd(-1) {}

Router &Server::getRouter()
{
    return router;
}

void Server::setup_socket()
{
    // create socket(IPv4, TCP
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
    {
        spdlog::error("Error creating socket: {}", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // configure the server address
    address.sin_family = AF_INET;         // IPv4
    address.sin_addr.s_addr = INADDR_ANY; // listen to all network interfaces
    address.sin_port = htons(port);       // convert port number to network byte order

    // bind the socket to the server address
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        spdlog::error("Error binding socket: {}", strerror(errno));
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // start listening for incoming connections
    if (listen(server_fd, BACKLOG) < 0)
    {
        spdlog::error("Error listening for connections: {}", strerror(errno));
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    spdlog::info("Server is listening on port {}", port);
}

void Server::client_connection_handler(int client_fd)
{
    try
    {
        char buffer[BUFFER_SIZE] = {0};
        read(client_fd, buffer, sizeof(buffer));

        spdlog::info("Received request: {}", buffer);

        // parse the request
        HttpRequest request;
        if (request.parse(buffer))
        {
            // route the request to the appropriate handler
            HttpResponse response = router.route(request);

            // send the response to the client
            std::string response_str = response.to_string();
            ssize_t bytes_sent = send(client_fd, response_str.c_str(), response_str.size(), 0);
            if (bytes_sent < 0)
            {
                spdlog::error("Error sending response: {}", strerror(errno));
            }
            else
            {
                spdlog::info("Response sent: {}", response_str);
            }
        }
    }
    catch (const std::exception &e)
    {
        spdlog::error("Error handling client connection: {}", e.what());
    }

    // close the connection
    close(client_fd);
}

void Server::run()
{
    while (true)
    {
        struct sockaddr_in client_address;
        socklen_t client_len = sizeof(client_address);
        int client_fd = accept(server_fd, (struct sockaddr *)&client_address, &client_len);
        if (client_fd < 0)
        {
            spdlog::error("Error accepting connection: {}", strerror(errno));
            continue;
        }

        spdlog::info("Connection accepted from {}", inet_ntoa(client_address.sin_addr));
        worker_threads.emplace_back(&Server::client_connection_handler, this, client_fd);
    }
}

void Server::start()
{
    // setup the socket
    setup_socket();
    run();
}

Server::~Server()
{
    if (server_fd != -1)
    {
        close(server_fd);
        spdlog::info("Server shut down");
    }
    spdlog::info("Waiting for worker threads to finish");
    for (std::thread &worker : worker_threads)
    {
        if (worker.joinable())
        {
            worker.join();
        }
    }
    spdlog::info("All worker threads finished");
}