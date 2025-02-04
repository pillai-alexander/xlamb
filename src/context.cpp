#include <xlamb/context.hpp>

#include <entt/entt.hpp>

namespace xlamb {

context::context() {}

context::~context() {}

entt::entity context::create_entity() {
    auto entity = registry.create();
    return entity;
}

void context::destroy_entity(entt::entity entity) {
    registry.destroy(entity);
}

} // namespace xlamb
