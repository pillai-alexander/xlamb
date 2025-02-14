#pragma once

#include <unordered_map>

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

    Entity get_entity(std::string);

    template<typename... Ts>
    auto view_entities_with() { return registry.view<Ts...>(); }

    template<typename... Ts>
    auto each_entity_with() { return registry.view<Ts...>().each(); }

    void clear_registry();

  private:
    entt::registry registry;
    std::unordered_map<std::string, entt::entity> entity_lookup;

    friend class Entity;
};

} // namespace xlamb
