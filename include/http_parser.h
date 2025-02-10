#pragma once

#include <string>
#include <map>

class HttpRequest
{
public:
    std::string method;
    std::string path;
    std::string body;
    std::map<std::string, std::string> headers;

    bool parse(const std::string &request);
};

class HttpResponse
{
public:
    int status_code;
    std::string status_message;
    std::map<std::string, std::string> headers;
    std::string body;

    std::string to_string() const;
};
