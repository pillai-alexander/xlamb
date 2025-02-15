#include <gtest/gtest.h>
#include <xlamb/xlamb.hpp>

TEST(context_rng, create_named_and_seeded_rng) {
    auto context = xlamb::Context();
    auto rng = context.get_rng();

    EXPECT_NO_THROW(rng->create_generator("test"));
    EXPECT_NO_THROW(rng->set_seed("test", 0));
}

TEST(context_rng, seed_multiple_rngs) {
    auto context = xlamb::Context();
    auto rng = context.get_rng();

    rng->create_generator("test1");
    rng->create_generator("test2");

    EXPECT_NO_THROW(rng->set_seed(0));
}

TEST(context_rng, rng_unif) {
    auto context = xlamb::Context();
    auto rng = context.get_rng();

    rng->create_generator("test");
    rng->set_seed("test", 0);

    const auto draw = rng->unif("test");

    EXPECT_GE(draw, 0);
    EXPECT_LE(draw, 1);
}

TEST(context_rng, rng_safe_inspect) {
    auto context = xlamb::Context();
    auto rng = context.get_rng();

    rng->create_generator("test");
    rng->set_seed("test", 0);

    const auto next_draw = rng->inspect_next_unif("test");
    const auto draw      = rng->unif("test");

    EXPECT_EQ(next_draw, draw);
}