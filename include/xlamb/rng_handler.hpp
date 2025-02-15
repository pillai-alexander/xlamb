#pragma once

#include <unordered_map>
#include <string>

#include <gsl/gsl_rng.h>

namespace xlamb {

using seed_type = unsigned long int;

class RNG_Handler {
  public:
    RNG_Handler() = default;
    ~RNG_Handler();

    void create_generator(const std::string& key);

    void set_seed(seed_type seed);

    void set_seed(const std::string& key, seed_type seed);

    double unif(const std::string& key);

    double inspect_next_unif(const std::string& key);

  private:
    bool generator_exists(const std::string& key);

    std::unordered_map<std::string, gsl_rng*> generators;
};

} // namespace xlamb