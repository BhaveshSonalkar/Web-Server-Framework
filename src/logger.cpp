#include "logger.h"
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <vector>
#include <iostream>

void setup_logging()
{
    try
    {
        // Create console and file sinks
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("server.log", 5 * 1024 * 1024, 3);

        // Combine both sinks into a single logger
        std::vector<spdlog::sink_ptr> sinks{console_sink, file_sink};
        auto combined_logger = std::make_shared<spdlog::logger>("server_logger", sinks.begin(), sinks.end());

        // Set the logger as default
        spdlog::set_default_logger(combined_logger);

        // Set log level (options: trace, debug, info, warn, error, critical)
        spdlog::set_level(spdlog::level::info);

        spdlog::info("Logging initialized successfully.");
    }
    catch (const spdlog::spdlog_ex &ex)
    {
        std::cerr << "Logging initialization failed: " << ex.what() << std::endl;
    }
}
