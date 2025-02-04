#pragma once

#include <memory>

#include <xlamb/context.hpp>

namespace xlamb {

class Context;

class Architect {
  public:
    Architect() = default;
    ~Architect() = default;

    xlamb::Context context;
  private:
};

} // namespace xlamb
