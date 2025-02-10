# WebServer Project

## Overview

This project is a simple web server implemented in C++. It is designed to handle HTTP requests and provide appropriate responses. The server is built with modular components, including a router for handling different routes and an HTTP parser for processing incoming requests.

## Features

- **Socket Programming**: Utilizes low-level socket programming to handle client connections.
- **HTTP Parsing**: Includes a custom HTTP parser to interpret incoming requests.
- **Routing**: Supports routing of requests to different handlers based on the HTTP method and path.
- **Logging**: Uses `spdlog` for logging server activities and errors.

## Components

- **Server**: The main server class that sets up the socket, listens for connections, and handles client requests.
  - **Setup Socket**: Initializes and binds the server socket.
  - **Client Connection Handler**: Manages individual client connections and processes their requests.
  - **Register Routes**: Registers available routes and their handlers.

- **Router**: Manages the routing of HTTP requests to the appropriate handler functions.
  - **Register Route**: Allows registration of routes with specific HTTP methods and paths.
  - **Route**: Directs requests to the correct handler or returns a 404 response if no route is found.

- **HTTP Parser**: Parses raw HTTP requests into structured `HttpRequest` objects and converts `HttpResponse` objects into strings for transmission.

## Getting Started

### Prerequisites

- CMake 3.10 or higher
- A C++17 compatible compiler

### Building the Project

1. Clone the repository.
2. Run `cmake` to configure the project.
3. Build the project using `make`.

### Running the Server

Execute the compiled binary to start the server. By default, it listens on port 8080.