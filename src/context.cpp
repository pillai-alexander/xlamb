#include <xlamb/context.hpp>

#include <entt/entt.hpp>

#include <xlamb/entity.hpp>

namespace xlamb {

Context::Context() {
    attach<std::unique_ptr<RNG_Handler>>(std::make_unique<RNG_Handler>());
}

Entity Context::create_entity(const std::string name) {
    Entity e = {registry.create(), this};
    auto& tag = e.add_component<TagComponent>();
    tag.name = name;

    entity_lookup[name] = e.entity_handle;
    return e;
}

void Context::destroy_entity(Entity& e) {
    registry.destroy(e.entity_handle);
}

Entity Context::get_entity(std::string name) {
    return {entity_lookup.at(name), this};
}

void Context::clear_registry() { registry.clear(); }

RNG_Handler* Context::get_rng() { return get<std::unique_ptr<RNG_Handler>>().get(); }

} // namespace xlamb
