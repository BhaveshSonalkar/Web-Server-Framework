#include "routes.h"
#include "http_parser.h"
#include <spdlog/spdlog.h>

void register_routes(Router &router)
{
    spdlog::info("Registering routes...");

    router.register_route("GET", "/", [](const HttpRequest &request) -> HttpResponse
                          {
        HttpResponse response;
        std::string name = request.params.at("name");

        response.status_code = 200;
        response.status_message = "OK";
        response.body = "Get request received, name: " + name;
        return response; });

    router.register_route("POST", "/submit", [](const HttpRequest &request) -> HttpResponse
                          {
        HttpResponse response;
        response.status_code = 200;
        response.status_message = "OK";
        response.body = "Post request received";
        return response; });
    spdlog::info("Routes successfully registered");
}