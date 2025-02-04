#pragma once

#include <memory>

#include <xlamb/context.hpp>

namespace xlamb {

class context;

class architect {
  public:
    architect() = default;
    ~architect() = default;

    xlamb::context context;
  private:
};

} // namespace xlamb
