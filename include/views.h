#pragma once

#include "http_parser.h"

// Define function signatures for request handlers.
HttpResponse test_get(const HttpRequest &request);
HttpResponse test_post(const HttpRequest &request);
