#pragma once

#include <memory>
#include <string>

namespace spdlog { class logger; };

namespace xlamb {

class Log{
  public:
    static void init();

    static void trace(std::string);
    static void debug(std::string);
    static void info(std::string);
    static void warn(std::string);
    static void error(std::string);
    static void critical(std::string);

  private:
    static std::shared_ptr<spdlog::logger> logger;
};

} // namespace xlamb