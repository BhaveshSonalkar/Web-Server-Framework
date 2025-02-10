#pragma once

#include "http_parser.h"
#include <functional>
#include <map>

class Router
{
public:
    using Handler = std::function<HttpResponse(const HttpRequest &)>;

    void register_route(const std::string &method, const std::string &path, Handler handler);
    HttpResponse route(const HttpRequest &request) const;

private:
    std::map<std::string, std::map<std::string, Handler>> routes;
};