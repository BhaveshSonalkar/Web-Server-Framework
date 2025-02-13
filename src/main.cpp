#include "server.h"
#include "urls.h"

int main()
{
    Server server(8080);

    // Register routes externally using the server's router
    register_urls(server.getRouter());

    server.start();
}