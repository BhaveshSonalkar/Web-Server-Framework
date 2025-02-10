#include "server.h"
#include "constants.h"
#include "http_parser.h"
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

void Server::client_connection_handler()
{
    struct sockaddr_in client_address;
    socklen_t client_len = sizeof(client_address);

    // accept an incoming connection
    int client_fd = accept(server_fd, (struct sockaddr *)&client_address, &client_len);

    if (client_fd < 0)
    {
        perror("Error accepting connection");
        return;
    }

    std::cout << "Connection accepted from " << inet_ntoa(client_address.sin_addr) << std::endl;

    char buffer[1024] = {0};
    read(client_fd, buffer, sizeof(buffer));

    std::cout << "Received request: " << buffer << std::endl;

    // parse the request
    HttpRequest request;
    if (request.parse(buffer))
    {
        HttpResponse response;
        if (request.method == "GET" && request.path == "/")
        {
            response.status_code = 200;
            response.status_message = "OK";
            response.headers["Content-Type"] = "text/plain";
            response.body = "Welcome to the server!";
        }
        else
        {
            response.status_code = 404;
            response.status_message = "Not Found";
            response.body = "Page not found";
        }

        // send the response to the client
        std::string response_str = response.to_string();
        send(client_fd, response_str.c_str(), response_str.size(), 0);
    }
    close(client_fd);
}

void Server::run()
{
    while (true)
    {
        client_connection_handler();
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