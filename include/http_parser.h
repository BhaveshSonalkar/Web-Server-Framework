#pragma once

#include <string>
#include <map>

class HttpRequest
{
    std::string sanitize_string(const std::string &str);
    std::map<std::string, std::string> parse_query_params(const std::string &query_string);
public:
    std::string method;
    std::string path;
    std::string body;
    std::map<std::string, std::string> headers;
    std::map<std::string, std::string> params;

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
