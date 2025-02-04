#include <xlamb/logger.hpp>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace xlamb {

struct Log {
    Log(log_level l, std::string s) : level(l), entry(s) {}
    log_level level;
    std::string entry;
};

std::shared_ptr<spdlog::logger> Logger::spdlogger;

Logger::Logger(bool console) : console_logs(console) {
    std::vector<spdlog::sink_ptr> sinks;

    sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_st>());
    sinks[0]->set_level(spdlog::level::trace);
    sinks[0]->set_pattern("%^[%l]%$ %n: %v");

    // sinks.push_back(std::make_shared<spdlog::sinks::stderr_color_sink_st>());
    // sinks[1]->set_level(spdlog::level::warn);
    // sinks[1]->set_pattern("%^[%l]%$ %n: %v");

    spdlogger = std::make_shared<spdlog::logger>("XLAMB", begin(sinks), end(sinks));
    spdlogger->set_level(spdlog::level::trace);
    spdlogger->flush_on(spdlog::level::trace);
}

Logger& Logger::get() {
    static Logger instance{};
    return instance;
}

void Logger::set_console_printing(bool setting) { console_logs = setting; }

} // namespace xlamb
