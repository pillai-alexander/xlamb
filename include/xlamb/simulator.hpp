#pragma once

#include <memory>
#include <functional>

#include <xlamb/context.hpp>

namespace xlamb {

class Simulator {
  public:
    Simulator() = default;
    ~Simulator() = default;

    void bind(std::function<void(xlamb::Context&)>,
              std::function<void(xlamb::Context&)>,
              std::function<void(xlamb::Context&)>);

    int run();

  private:
    std::function<void(xlamb::Context&)> setup;
    std::function<void(xlamb::Context&)> simulate;
    std::function<void(xlamb::Context&)> report;

    xlamb::Context context;
};

} // namespace xlamb
