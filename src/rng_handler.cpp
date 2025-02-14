#include <xlamb/rng_handler.hpp>

#include <xlamb/logger.hpp>

namespace xlamb {

RNG_Handler::~RNG_Handler() {
    for (auto [key, rng] : generators) {
        gsl_rng_free(rng);
    }
}

void RNG_Handler::create_generator(const std::string& key) {
    if (not generator_exists(key)) {
        generators[key] = gsl_rng_alloc(gsl_rng_mt19937);
    } else {
        XLAMB_ERROR("Attempting to overwrite existing RNG ({}).", key);
    }
}

void RNG_Handler::set_seed(seed_type seed) {
    for (auto [key, rng] : generators) {
        gsl_rng_set(rng, seed);
    }
}

void RNG_Handler::set_seed(const std::string& key, seed_type seed) {
    if (generator_exists(key)) {
        gsl_rng_set(generators.at(key), seed);
    } else {
        XLAMB_ERROR("Attempting to set seed for nonexistant RNG ({}).", key);
    }
}

double RNG_Handler::draw(const std::string& key) {
    if (generator_exists(key)) {
        return gsl_rng_uniform(generators.at(key));
    } else {
        XLAMB_ERROR("Attempting to draw from nonexistant RNG ({}).", key);
        return -1;
    }
}

double RNG_Handler::inspect_next_draw(const std::string& key) {
    if (generator_exists(key)) {
        auto rng_copy = gsl_rng_clone(generators.at(key));
        const double next_draw = gsl_rng_uniform(rng_copy);
        gsl_rng_free(rng_copy);
        return next_draw;
    } else {
        XLAMB_ERROR("Attempting to inspect a nonexistant RNG ({}).", key);
        return -1;
    }
}

bool RNG_Handler::generator_exists(const std::string& key) {
    return generators.count(key) == 1;
}

} // namespace xlamb
