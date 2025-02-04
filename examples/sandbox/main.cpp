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

    xlamb::Architect architect;
    auto& context = architect.context;

    for(auto i = 0u; i < 10u; ++i) {
        const auto entity = context.create_entity();
        context.destroy_entity(entity);
    }

    auto default_entity = context.create_entity();
    auto default_name = default_entity.get_component<xlamb::TagComponent>();
    XLAMB_INFO("default name = {}", default_name.name);

    auto named_entity = context.create_entity("named_entity");
    auto new_name = named_entity.get_component<xlamb::TagComponent>().name;
    XLAMB_INFO("entity w/ name = {}", new_name);

/* API PLANNING

    # in user main.cpp
    int main(int argc, char* argv[]) {
        xlamb::architect app(argc, argv);
        return app.run();
    }

    # xlamb::architect::run() plan
      # read config files
      # read from database (single or batch)
      # set up/run simulation(s)
      # calculate metrics + save to file/database

*/

    return EXIT_SUCCESS;
}