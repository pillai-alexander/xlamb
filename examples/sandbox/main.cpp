#include <xlamb/xlamb.hpp>

struct SusceptibilityComponent {
    float susceptibility;
};

int main() {
    // testing logging
    XLAMB_TRACE("trace");
    XLAMB_DEBUG("debug");
    XLAMB_INFO("info");
    XLAMB_WARN("warn");
    XLAMB_ERROR("error");
    XLAMB_CRITICAL("critical");

    xlamb::Architect architect;
    auto& context = architect.context;

    for(auto i = 0u; i < 10u; ++i) {
        const auto entity = context.create_entity();
        context.destroy_entity(entity);
    }

    auto default_entity = context.create_entity();
    XLAMB_INFO("default name = {}", default_entity.name());
    context.destroy_entity(default_entity);

    auto named_entity = context.create_entity("named_entity");
    named_entity.add_component<SusceptibilityComponent>(1.0);
    XLAMB_INFO("entity ({}) w/ suscep = {}",
      named_entity.name(),
      named_entity.get_component<SusceptibilityComponent>().susceptibility
    );

    context.clear_registry();

    for (int i = 0; i < 10; ++i) {
        auto ent = context.create_entity("entity_" + std::to_string(i));
        const auto baseline_suscep = (i < 5) ? 0.5 : 1.0;
        ent.add_component<SusceptibilityComponent>(baseline_suscep);
    }

    auto view = context.view_entities_with<xlamb::TagComponent, SusceptibilityComponent>();
    for (auto ent : view) {
        const auto [tag, suscep] = view.get(ent);

        const auto n = tag.name;
        const auto s = suscep.susceptibility;
        XLAMB_INFO("{} suscep = {}", n, s);
    }

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