#include "urls.h"
#include "views.h"
#include <spdlog/spdlog.h>

void register_urls(Router &router)
{
    spdlog::info("Registering URLs...");

    router.register_route("GET", "/", home_view);
    router.register_route("POST", "/submit", test_post_view);

    spdlog::info("URLs successfully registered");
}
