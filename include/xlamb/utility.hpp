#pragma once

#include <vector>

namespace xlamb {

namespace util {

extern double logistic(const double log_odds);

extern double logit(const double prob);

extern double exp_decay_rate_from_half_life(const double half_life);

extern double exp_decay(const double rate, const double time);

} // namespace util
  
} // namespace xlamb
