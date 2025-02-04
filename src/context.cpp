#include <xlamb/context.hpp>

#include <entt/entt.hpp>

#include <xlamb/entity.hpp>

namespace xlamb {

Context::Context() {}

Context::~Context() {}

Entity Context::create_entity(const std::string name) {
    Entity e = {registry.create(), this};
    auto& tag = e.add_component<TagComponent>();
    tag.name = name;
    return e;
}

void Context::destroy_entity(Entity e) {
    registry.destroy(e.entity_handle);
}

void Context::clear_registry() { registry.clear(); }

} // namespace xlamb
