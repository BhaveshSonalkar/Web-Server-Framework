#include "http_parser.h"
#include <sstream>
#include <iostream>

bool HttpRequest::parse(const std::string &raw_request)
{
    try
    {
        std::istringstream request_stream(raw_request);
        std::string line;

        // Parse the first line
        if (std::getline(request_stream, line))
        {
            std::istringstream line_stream(line);
            line_stream >> method >> path;
        }

        // Parse headers
        while (std::getline(request_stream, line) && line != "\r")
        {
            auto colon_pos = line.find(':');
            if (colon_pos != std::string::npos)
            {
                std::string header_name = line.substr(0, colon_pos);
                std::string header_value = line.substr(colon_pos + 1);
                headers[header_name] = header_value;
            }
        }

        // Parse body
        if (request_stream.rdbuf()->in_avail() > 0)
        {
            std::getline(request_stream, body, '\0');
        }

        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error parsing request: " << e.what() << std::endl;
        return false;
    }
}

std::string HttpResponse::to_string() const
{
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
        std::cerr << "Error converting response to string: " << e.what() << std::endl;
        return "";
    }
}