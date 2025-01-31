#pragma once

#include <memory>

#include <xlamb/context.hpp>

namespace xlamb {

class Context;

class Builder {
  public:
    Builder() = default;
    ~Builder() = default;

    Context context;
  private:
};

} // namespace xlamb
