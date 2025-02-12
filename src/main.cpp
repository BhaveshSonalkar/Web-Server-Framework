#include "server.h"
#include "routes.h"

int main()
{
    Server server(8080);

    // Register routes externally using the server's router
    register_routes(server.getRouter());

    server.start();
}