#pragma once

#include <entt/entt.hpp>

namespace xlamb {

class Entity;

class Context {
  public:
    Context();
    ~Context();

    Entity create_entity(const std::string = "default_entity");
    void destroy_entity(Entity e);

    template<typename T>
    void clear_component() { registry.clear<T>(); }

    template<typename... Ts>
    auto view_entities_with() { return registry.view<Ts...>(); }

    void clear_registry();

  private:
    entt::registry registry;

    friend class Entity;
};

} // namespace xlamb
