#include "router.h"

void Router::register_route(const std::string &method, const std::string &path, Handler handler)
{
    routes[method][path] = handler;
}

HttpResponse Router::route(const HttpRequest &request) const
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