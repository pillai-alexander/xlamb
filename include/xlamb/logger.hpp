#pragma once

#include <memory>
#include <string>
#include <vector>

#include <spdlog/spdlog.h>

using log_level = spdlog::level::level_enum;

namespace xlamb {

struct log;

class logger {
  public:
    logger(const logger&)            = delete;
    logger& operator=(const logger&) = delete;

    static logger& get();

    void set_log_storage(bool);
    void set_console_printing(bool);

    void trace(std::string);
    void debug(std::string);
    void info(std::string);
    void warn(std::string);
    void error(std::string);
    void critical(std::string);

  private:
    logger(bool storage = false, bool console = true);
    ~logger() = default;

    bool store_logs;
    bool console_logs;

    void store_log(log_level, std::string);

    std::vector<log> log_entries;

    static std::shared_ptr<spdlog::logger> spdlogger;
};

} // namespace xlamb

#define XLAMB_TRACE(s) xlamb::logger::get().trace(s);
#define XLAMB_DEBUG(s) xlamb::logger::get().debug(s);
#define XLAMB_INFO(s) xlamb::logger::get().info(s);
#define XLAMB_WARN(s) xlamb::logger::get().warn(s);
#define XLAMB_ERROR(s) xlamb::logger::get().error(s);
#define XLAMB_CRITICAL(s) xlamb::logger::get().critical(s);