#include <xlamb/context.hpp>

#include <entt/entt.hpp>

#include <xlamb/entity.hpp>

namespace xlamb {

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

RNG_Handler* Context::get_rng() { return rng.get(); }

} // namespace xlamb
