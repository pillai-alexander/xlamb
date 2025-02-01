#include <xlamb/xlamb.hpp>

int main() {
    // testing logging
    XLAMB_TRACE("trace");
    XLAMB_DEBUG("debug");
    XLAMB_INFO("info");
    XLAMB_WARN("warn");
    XLAMB_ERROR("error");
    XLAMB_CRITICAL("critical");

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