#include "urls.h"
#include "views.h"
#include <spdlog/spdlog.h>

void register_urls(Router &router)
{
    spdlog::info("Registering URLs...");

    router.register_route("GET", "/test_get", test_get);
    router.register_route("POST", "/test_post", test_post);

    spdlog::info("URLs successfully registered");
}
