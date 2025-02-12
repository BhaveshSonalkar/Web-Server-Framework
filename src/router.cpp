#include "router.h"
#include <spdlog/spdlog.h>

void Router::register_route(const std::string &method, const std::string &path, Handler handler)
{
    routes[method][path] = handler;
}

HttpResponse Router::route(const HttpRequest &request) const
{
    try
    {
        auto method_it = routes.find(request.method);
        if (method_it != routes.end())
        {
            auto path_it = method_it->second.find(request.path);
            if (path_it != method_it->second.end())
            {
                return path_it->second(request);
            }
        }

        // Return 404 if no route is found
        HttpResponse response;
        response.status_code = 404;
        response.status_message = "Not Found";
        response.body = "The requested resource was not found.";
        response.headers["Content-Type"] = "text/plain";
        return response;
    }
    catch (const std::exception &e)
    {
        spdlog::error("Error routing request: {}", e.what());
        HttpResponse response;
        response.status_code = 500;
        response.status_message = "Internal Server Error";
        response.body = "An internal server error occurred while routing the request.";
        response.headers["Content-Type"] = "text/plain";
        return response;
    }
}