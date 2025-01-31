#pragma once

#include <entt/entt.hpp>

namespace xlamb {

class Context {
  public:
    Context();
    ~Context();

    entt::entity create_entity();
    void destroy_entity(entt::entity);

  private:
    entt::registry registry;
};

} // namespace xlamb
