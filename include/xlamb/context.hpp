#pragma once

#include <unordered_map>
#include <string>
#include <memory>

#include <entt/entt.hpp>

#include <xlamb/rng_handler.hpp>

namespace xlamb {

class Entity;

class Context {
  public:
    Context() : rng(std::make_unique<RNG_Handler>()) {};
    ~Context() = default;

    Entity create_entity(const std::string name = "default_entity");

    void destroy_entity(Entity& e);

    template<typename T>
    void clear_component() { registry.clear<T>(); }

    Entity get_entity(std::string name);

    template<typename... Ts>
    auto view_entities_with() { return registry.view<Ts...>(); }

    template<typename... Ts>
    auto each_entity_with() { return registry.view<Ts...>().each(); }

    void clear_registry();

    RNG_Handler* get_rng();

  private:
    entt::registry registry;
    std::unordered_map<std::string, entt::entity> entity_lookup;

    std::unique_ptr<RNG_Handler> rng;

    friend class Entity;
};

} // namespace xlamb
