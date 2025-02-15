#include <gtest/gtest.h>
#include <xlamb/xlamb.hpp>

TEST(context_views, view_entities_with_component) {
    auto context = xlamb::Context();

    // create an entity
    auto e1 = context.create_entity("test_entity_1");
    auto e2 = context.create_entity("test_entity_2");

    struct SomeData {
        int a;
    };

    e2.add_component<SomeData>(1);

    auto view = context.view_entities_with<SomeData, xlamb::TagComponent>();
    for (auto ent : view) {
        auto [data, tag] = view.get(ent);
        data.a = 2;
        tag.name = "test_entity_2_changed";
    }

    const auto& e2data = e2.get_component<SomeData>();

    EXPECT_EQ(e1.name(), "test_entity_1");

    EXPECT_EQ(e2.name(), "test_entity_2_changed");
    EXPECT_EQ(e2data.a, 2);
}

TEST(context_views, each_entity_with_component) {
    auto context = xlamb::Context();

    // create an entity
    auto e1 = context.create_entity("test_entity_1");
    auto e2 = context.create_entity("test_entity_2");

    struct SomeData {
        int a;
    };

    e2.add_component<SomeData>(1);

    for (auto [ent, data, tag] : context.each_entity_with<SomeData, xlamb::TagComponent>()) {
        data.a = 2;
        tag.name = "test_entity_2_changed";
    }

    const auto& e2data = e2.get_component<SomeData>();

    EXPECT_EQ(e1.name(), "test_entity_1");

    EXPECT_EQ(e2.name(), "test_entity_2_changed");
    EXPECT_EQ(e2data.a, 2);
}