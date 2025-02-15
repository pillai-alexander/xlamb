#pragma once

#include <memory>
#include <string>
#include <vector>

#include <spdlog/spdlog.h>

using log_level = spdlog::level::level_enum;

namespace xlamb {

struct Log;

class Logger {
  public:
    Logger(const Logger& other)            = delete;
    Logger& operator=(const Logger& other) = delete;

    static Logger& get();

    void set_console_printing(bool console);

    template<typename... Args>
    void trace(Args&&... args) {
        if (console_logs) spdlogger->trace(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void debug(Args&&... args) {
        if (console_logs) spdlogger->debug(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void info(Args&&... args) {
        if (console_logs) spdlogger->info(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void warn(Args&&... args) {
        if (console_logs) spdlogger->warn(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void error(Args&&... args) {
        if (console_logs) spdlogger->error(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void critical(Args&&... args) {
        if (console_logs) spdlogger->critical(std::forward<Args>(args)...);
    }

  private:
    Logger(bool console = true);
    ~Logger() = default;

    bool console_logs;

    static std::shared_ptr<spdlog::logger> spdlogger;
};

} // namespace xlamb

#define XLAMB_TRACE(...) xlamb::Logger::get().trace(__VA_ARGS__);
#define XLAMB_DEBUG(...) xlamb::Logger::get().debug(__VA_ARGS__);
#define XLAMB_INFO(...) xlamb::Logger::get().info(__VA_ARGS__);
#define XLAMB_WARN(...) xlamb::Logger::get().warn(__VA_ARGS__);
#define XLAMB_ERROR(...) xlamb::Logger::get().error(__VA_ARGS__);
#define XLAMB_CRITICAL(...) xlamb::Logger::get().critical(__VA_ARGS__);