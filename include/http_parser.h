#pragma once

#include <string>
#include <map>
#include <nlohmann/json.hpp>

class HttpRequest
{
public:
    std::string method;
    std::string path;
    std::string body;
    std::map<std::string, std::string> headers;
    std::map<std::string, std::string> params;
    nlohmann::json json_body;

    bool parse(const std::string &request);

private:
    std::string sanitize_string(const std::string &str);
    std::map<std::string, std::string> parse_query_params(const std::string &query_string);
    nlohmann::json parse_json_body() const;
    std::map<std::string, std::string> parse_headers(std::istringstream &request_stream);
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
