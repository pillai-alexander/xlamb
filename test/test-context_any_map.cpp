#include <gtest/gtest.h>
#include <xlamb/xlamb.hpp>

TEST(context_any_map, attach_item) {
    auto context = xlamb::Context();

    struct Foo {
        int a = 1;
    };

    const auto& foo = context.attach<Foo>();
    EXPECT_EQ(foo.a, 1);
}

TEST(context_any_map, get_item) {
    auto context = xlamb::Context();

    struct Foo {
        int a = 1;
    };

    context.attach<Foo>();

    const auto& foo = context.get<Foo>();
    EXPECT_EQ(foo.a, 1);
}

TEST(context_any_map, find_item) {
    auto context = xlamb::Context();

    struct Foo {
        int a = 1;
    };

    context.attach<Foo>();

    const auto foo = context.find<Foo>();
    EXPECT_EQ(foo->a, 1);
}

TEST(context_any_map, has_item) {
    auto context = xlamb::Context();

    struct Foo {
        int a = 1;
    };

    context.attach<Foo>();

    EXPECT_TRUE(context.has<Foo>());
}

TEST(context_any_map, edit_item) {
    auto context = xlamb::Context();

    struct Foo {
        int a = 1;
    };

    auto& foo = context.attach<Foo>();
    for (int i = 0; i < 10; ++i) {
        foo.a = i;
    }
    
    EXPECT_EQ(context.get<Foo>().a, 9);
}

TEST(context_any_map, erase_item) {
    auto context = xlamb::Context();

    struct Foo {
        int a = 1;
    };

    context.attach<Foo>();

    EXPECT_TRUE(context.has<Foo>());
    EXPECT_EQ(context.get<Foo>().a, 1);

    context.erase<Foo>();
    EXPECT_FALSE(context.has<Foo>());
}