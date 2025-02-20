#pragma once

#include <unordered_map>
#include <string>

#include <entt/entt.hpp>

#include <xlamb/rng_handler.hpp>

namespace xlamb {

class Entity;

class Context {
  public:
    Context();
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

    template<typename T, typename... Args>
    T& attach(Args&&... args) {
        T& item = registry.ctx().emplace<T>(std::forward<Args>(args)...);
        return item;
    }

    template<typename T>
    T* find() { return registry.ctx().find<T>(); }

    template<typename T>
    T& get() { return registry.ctx().get<T>(); }

    template<typename T>
    bool has() { return registry.ctx().contains<T>(); }

    template<typename T>
    void erase() { registry.ctx().erase<T>(); }

    void clear_registry();

    RNG_Handler* get_rng();

  private:
    entt::registry registry;
    std::unordered_map<std::string, entt::entity> entity_lookup;

    friend class Entity;
};

} // namespace xlamb
