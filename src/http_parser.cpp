#include "http_parser.h"
#include <sstream>
#include <iostream>
#include <spdlog/spdlog.h>

std::map<std::string, std::string> HttpRequest::parse_query_params(const std::string &query_string)
{
    /*
    This function parses the query string and returns a map of key-value pairs.
    */
    std::map<std::string, std::string> params;
    std::stringstream query_stream(query_string);
    std::string key, value;

    while (std::getline(query_stream, key, '=') && std::getline(query_stream, value, '&'))
    {
        params[key] = value;
    }
    return params;
}

nlohmann::json HttpRequest::parse_json_body() const
{
    /*
    This function parses the JSON body and returns a nlohmann::json object.
    */
    try
    {
        return nlohmann::json::parse(body);
    }
    catch (const nlohmann::json::parse_error &e)
    {
        spdlog::error("Error parsing JSON body: {}", e.what());
        return nlohmann::json();
    }
}

std::map<std::string, std::string> HttpRequest::parse_headers(std::istringstream &request_stream)
{
    /*
    This function parses the headers and returns a map of key-value pairs.
    */
    std::map<std::string, std::string> headers;
    std::string line;
    while (std::getline(request_stream, line) && line != "\r")
    {
        auto colon_pos = line.find(':');
        if (colon_pos != std::string::npos)
        {
            std::string header_name = sanitize_string(line.substr(0, colon_pos));
            std::string header_value = sanitize_string(line.substr(colon_pos + 1));

            headers[header_name] = header_value;
            spdlog::info("Parsed header: {} = {}", header_name, header_value);
        }
        else
        {
            spdlog::error("Malformed header: {}", line);
        }
    }
    return headers;
}

std::string HttpRequest::sanitize_string(const std::string &str)
{
    /*
    This function trims whitespace from the beginning and end of a string
    and returns the sanitized string.
    */
    std::string sanitized_string;
    // Trim whitespace from the beginning and end
    size_t start = str.find_first_not_of(" \t");
    size_t end = str.find_last_not_of(" \t");

    if (start == std::string::npos || end == std::string::npos)
    {
        return "";
    }
    sanitized_string = str.substr(start, end - start + 1);

    return sanitized_string;
}

bool HttpRequest::parse(const std::string &raw_request)
{
    /*
    This function parses the raw request string and populates the HttpRequest object.
    It returns true if the request is parsed successfully, false otherwise.
    */
    try
    {
        spdlog::info("Starting to parse the HTTP request.");
        std::istringstream request_stream(raw_request);
        std::string line;

        // Parse the first line
        if (std::getline(request_stream, line))
        {
            std::istringstream line_stream(line);
            line_stream >> method >> path;

            std::string http_version;
            line_stream >> http_version;

            // Check if the path contains query parameters
            size_t question_mark_pos = path.find('?');
            if (question_mark_pos != std::string::npos)
            {
                // Extract the base path and query parameters
                std::string base_path = path.substr(0, question_mark_pos);
                params = parse_query_params(path.substr(question_mark_pos + 1));

                // Update the path with the base path
                path = base_path;
            }

            // Check if the HTTP version is valid
            if (http_version.substr(0, 5) != "HTTP/")
            {
                spdlog::error("Invalid HTTP version: {}", http_version);
                return false;
            }
            spdlog::info("Parsed request line: Method = {}, Path = {}, Version = {}", method, path, http_version);
        }
        else
        {
            spdlog::error("Request line is missing");
            return false;
        }

        // Parse headers
        headers = parse_headers(request_stream);

        // Parse body
        if (request_stream.rdbuf()->in_avail() > 0)
        {
            std::getline(request_stream, body, '\0');
            spdlog::info("Parsed body: {}", body);

            // check if content type is application/json
            auto it = headers.find("Content-Type");
            if (it != headers.end() && it->second == "application/json")
            {
                json_body = parse_json_body();
            }
        }

        spdlog::info("Finished parsing the HTTP request.");
        return true;
    }
    catch (const std::exception &e)
    {
        spdlog::error("Error parsing request: {}", e.what());
        return false;
    }
}

std::string HttpResponse::to_string() const
{
    /*
    This function converts the HttpResponse object to a string.
    It returns the string representation of the response.
    */
    try
    {
        std::ostringstream response_stream;
        response_stream << "HTTP/1.1 " << status_code << " " << status_message << "\r\n";

        for (const auto &header : headers)
        {
            response_stream << header.first << ": " << header.second << "\r\n";
        }

        response_stream << "\r\n"
                        << body;

        return response_stream.str();
    }
    catch (const std::exception &e)
    {
        spdlog::error("Error converting response to string: {}", e.what());
        return "";
    }
}