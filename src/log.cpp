#include <xlamb/log.hpp>

#include <vector>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace xlamb {

std::shared_ptr<spdlog::logger> Log::logger;

void Log::init() {
    std::vector<spdlog::sink_ptr> sinks;
    sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_st>());
    sinks.push_back(std::make_shared<spdlog::sinks::stderr_color_sink_st>());

    sinks[0]->set_level(spdlog::level::trace);
    sinks[1]->set_level(spdlog::level::warn);

    logger = std::make_shared<spdlog::logger>("XLAMB", begin(sinks), end(sinks));
    logger->set_level(spdlog::level::trace);
    logger->flush_on(spdlog::level::trace);
    logger->set_pattern("%^[%l]%$ %n: %v");
}

void Log::trace(std::string s)    { logger->trace(s); }
void Log::debug(std::string s)    { logger->debug(s); }
void Log::info(std::string s)     { logger->info(s); }
void Log::warn(std::string s)     { logger->warn(s); }
void Log::error(std::string s)    { logger->error(s); }
void Log::critical(std::string s) { logger->critical(s); }

} // namespace xlamb
