#include <xlamb/entity.hpp>

namespace xlamb {

Entity::Entity(entt::entity handle, Context* c)
  : entity_handle(handle), context(c) {}

const std::string& Entity::name() { return get_component<TagComponent>().name; }

} // namespace xlamb