#include "server.h"
#include "constants.h"
#include <arpa/inet.h>

Server::Server(int port) : port(port), server_fd(-1) {}

void Server::setup_socket()
{
    // create socket(IPv4, TCP
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
    {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // configure the server address
    address.sin_family = AF_INET;         // IPv4
    address.sin_addr.s_addr = INADDR_ANY; // listen to all network interfaces
    address.sin_port = htons(port);       // convert port number to network byte order

    // bind the socket to the server address
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("Error binding socket");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // start listening for incoming connections
    if (listen(server_fd, BACKLOG) < 0)
    {
        perror("Error listening for connections");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    std::cout << "Server is listening on port " << port << std::endl;
}

void Server::run()
{
    while (true)
    {
        struct sockaddr_in client_address;
        socklen_t client_len = sizeof(client_address);

        // accept an incoming connection
        int client_fd = accept(server_fd, (struct sockaddr *)&client_address, &client_len);

        if (client_fd < 0)
        {
            perror("Error accepting connection");
            continue;
        }

        std::cout << "Connection accepted from " << inet_ntoa(client_address.sin_addr) << std::endl;

        // send a proper HTTP/1.1 response to the client
        const std::string response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: 25\r\n"
            "\r\n"
            "Welcome to the server!\n";

        send(client_fd, response.c_str(), response.size(), 0);

        // close the connection
        close(client_fd);
    }
}

void Server::start()
{
    setup_socket();
    run();
}

Server::~Server()
{
    if (server_fd != -1)
    {
        close(server_fd);
        std::cout << "Server shut down" << std::endl;
    }
}