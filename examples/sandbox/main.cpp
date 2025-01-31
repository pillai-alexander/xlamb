#include <xlamb/xlamb.hpp>

int main() {
    // testing logging
    xlamb::Log::init();
    xlamb::Log::trace("trace");
    xlamb::Log::debug("debug");
    xlamb::Log::info("info");
    xlamb::Log::warn("warn");
    xlamb::Log::error("error");
    xlamb::Log::critical("critical");


    // testing EnTT
    struct position {
        int x;
        int y;
    };

    struct velocity {
        float x;
        float y;
    };

    xlamb::Builder builder;

    for(auto i = 0u; i < 10u; ++i) {
        const auto entity = builder.context.create_entity();
        builder.context.destroy_entity(entity);
    }


    return EXIT_SUCCESS;
}