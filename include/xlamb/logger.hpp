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
    Logger(const Logger&)            = delete;
    Logger& operator=(const Logger&) = delete;

    static Logger& get();

    void set_log_storage(bool);
    void set_console_printing(bool);

    void trace(std::string);
    void debug(std::string);
    void info(std::string);
    void warn(std::string);
    void error(std::string);
    void critical(std::string);

  private:
    Logger(bool storage = false, bool console = true);
    ~Logger() = default;

    bool store_logs;
    bool console_logs;

    void store_log(log_level, std::string);

    std::vector<Log> log_entries;

    static std::shared_ptr<spdlog::logger> spdlogger;
};

} // namespace xlamb

#define XLAMB_TRACE(s) xlamb::Logger::get().trace(s);
#define XLAMB_DEBUG(s) xlamb::Logger::get().debug(s);
#define XLAMB_INFO(s) xlamb::Logger::get().info(s);
#define XLAMB_WARN(s) xlamb::Logger::get().warn(s);
#define XLAMB_ERROR(s) xlamb::Logger::get().error(s);
#define XLAMB_CRITICAL(s) xlamb::Logger::get().critical(s);