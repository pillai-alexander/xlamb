#pragma once

#include <string>

#include <entt/entt.hpp>

#include <xlamb/context.hpp>

namespace xlamb {

struct TagComponent {
    std::string name;
};

class Entity {
  public:
    Entity() = default;
    Entity(entt::entity handle, Context* c);
    Entity(const Entity& other) = default;
    ~Entity() = default;

    template<typename T, typename... Args>
    T& add_component(Args&&... args) {
        T& component = context->registry.emplace<T>(entity_handle, std::forward<Args>(args)...);
        return component;
    }

    template<typename T, typename... Args>
    T& add_or_replace_component(Args&&... args) {
        T& component = context->registry.emplace_or_replace<T>(entity_handle, std::forward<Args>(args)...);
        return component;
    }

    template<typename... T>
    bool has_all_of() {
        return context->registry.all_of<T...>(entity_handle);
    }

    template<typename... T>
    bool has_any_of() {
        return context->registry.any_of<T...>(entity_handle);
    }

    template<typename T>
    T& get_component() {
        return context->registry.get<T>(entity_handle);
    }

    template<typename... Ts>
    auto get_components() {
        return context->registry.get<Ts...>(entity_handle);
    }

    template<typename T>
    void remove_component() {
        return context->registry.remove<T>(entity_handle);
    }

    const std::string& name();

  private:
    entt::entity entity_handle;
    Context* context;

    friend class Context;
};

} // namespace xlamb
