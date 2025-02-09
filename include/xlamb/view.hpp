#pragma once

#include <entt/entt.hpp>

namespace xlamb {

template<typename... Ts>
class View {
  public:
    View(entt::basic_view<Ts...> v) : view(v) {};
    ~View() = default;

    View(const View& other) : view(other.view) {};
    View& operator=(const View& other) { return View(other); };

  private:
    entt::basic_view<Ts...> view;
};

} // namespace xlamb