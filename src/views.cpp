#include "views.h"

HttpResponse test_get(const HttpRequest &request)
{
    HttpResponse response;
    auto params = request.params;
    std::string name = params["name"];

    response.status_code = 200;
    response.status_message = "OK";
    response.body = "Get request received, name: " + name;

    return response;
}

HttpResponse test_post(const HttpRequest &request)
{
    try
    {
        HttpResponse response;
        std::string name = "";
        auto data = request.json_body;
        if (data.find("name") != data.end())
        {
            name = data["name"];
        }

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
