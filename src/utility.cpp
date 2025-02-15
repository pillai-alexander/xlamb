#include <xlamb/utility.hpp>

#include <cmath>

namespace xlamb {

namespace util {

double logistic(const double log_odds) {
    return 1.0 / (1.0 + std::exp(-1.0 * log_odds));
}

double logit(const double prob) {
    return std::log(prob / (1.0 - prob));
}

double exp_decay_rate_from_half_life(const double half_life) {
    return std::log(2.0) / half_life;
}

double exp_decay(const double rate, const double time) {
    return std::exp(-1.0 * rate * time);
}

} // namespace util


} // namespace xlamb
