#include <xlamb/context.hpp>

#include <entt/entt.hpp>

namespace xlamb {

Context::Context() {}

Context::~Context() {}

entt::entity Context::create_entity() {
    auto entity = registry.create();
    return entity;
}

void Context::destroy_entity(entt::entity entity) {
    registry.destroy(entity);
}

} // namespace xlamb
