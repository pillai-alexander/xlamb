#include <xlamb/entity.hpp>

namespace xlamb {

Entity::Entity(entt::entity handle, Context* c)
  : entity_handle(handle), context(c) {}

} // namespace xlamb