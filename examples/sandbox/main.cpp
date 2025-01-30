#include <xlamb/log.hpp>

int main() {
{ // testing logging
    xlamb::Log::init();
    xlamb::Log::trace("trace");
    xlamb::Log::debug("debug");
    xlamb::Log::info("info");
    xlamb::Log::warn("warn");
    xlamb::Log::error("error");
    xlamb::Log::critical("critical");
}

    return 0;
}