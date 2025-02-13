#pragma once

#include "http_parser.h"

// Define function signatures for request handlers.
HttpResponse home_view(const HttpRequest &request);
HttpResponse test_post_view(const HttpRequest &request);
