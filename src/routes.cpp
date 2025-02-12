#include "routes.h"
#include "http_parser.h"
#include <spdlog/spdlog.h>

void register_routes(Router &router)
{
    spdlog::info("Registering routes...");

    // Example route registration for GET /
    router.register_route("GET", "/", [](const HttpRequest &request) -> HttpResponse
                          {
        HttpResponse response;
        response.status_code = 200;
        response.status_message = "OK";
        response.body = "Hi to the server!";
        return response; });

    spdlog::info("Routes successfully registered");
}