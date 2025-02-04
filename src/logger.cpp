#include <xlamb/logger.hpp>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace xlamb {

struct log {
    log(log_level l, std::string s) : level(l), entry(s) {}
    log_level level;
    std::string entry;
};

std::shared_ptr<spdlog::logger> logger::spdlogger;

logger::logger(bool storage, bool console) : store_logs(storage), console_logs(console) {
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

logger& logger::get() {
    static logger instance{};
    return instance;
}

void logger::set_log_storage(bool setting)      { store_logs = setting; }
void logger::set_console_printing(bool setting) { console_logs = setting; }

void logger::store_log(log_level level, std::string entry) {
    log_entries.emplace_back(level, entry);
}

void logger::trace(std::string s) {
    if (console_logs) spdlogger->trace(s);
    if (store_logs)   store_log(log_level::trace, s);
}

void logger::debug(std::string s) {
    if (console_logs) spdlogger->debug(s);
    if (store_logs)   store_log(log_level::debug, s);
}

void logger::info(std::string s) {
    if (console_logs) spdlogger->info(s);
    if (store_logs)   store_log(log_level::info, s);
}

void logger::warn(std::string s) {
    if (console_logs) spdlogger->warn(s);
    if (store_logs)   store_log(log_level::warn, s);
}

void logger::error(std::string s) {
    if (console_logs) spdlogger->error(s);
    if (store_logs)   store_log(log_level::err, s);
}

void logger::critical(std::string s) {
    if (console_logs) spdlogger->critical(s);
    if (store_logs)   store_log(log_level::critical, s);
}

} // namespace xlamb
