#include "views.h"

HttpResponse home_view(const HttpRequest &request)
{
    HttpResponse response;
    auto params = request.params;
    std::string name = params["name"];

    response.status_code = 200;
    response.status_message = "OK";
    response.body = "Get request received, name: " + name;

    return response;
}

HttpResponse test_post_view(const HttpRequest &request)
{
    try
    {
        HttpResponse response;
        std::string name = request.json_body["name"];

        response.status_code = 200;
        response.status_message = "OK";
        response.body = "Post request received, name: " + name;

        return response;
    }
    catch (const std::exception &e)
    {
        HttpResponse response;
        response.status_code = 400;
        response.status_message = "Bad Request";
        response.body = "Post request received, but no name was provided";
        return response;
    }
}
