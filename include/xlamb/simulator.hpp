#pragma once

#include <memory>

#include <xlamb/context.hpp>

namespace xlamb {

class Context;

class Simulator {
  public:
    Simulator() = default;
    ~Simulator() = default;

    xlamb::Context context;
  private:
};

} // namespace xlamb
