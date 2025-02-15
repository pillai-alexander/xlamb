#include <gtest/gtest.h>
#include <xlamb/xlamb.hpp>

#include <string>

TEST(context_entity_handling, create_named_entity) {
    auto context = xlamb::Context();

    // create an entity
    auto e = context.create_entity("test_entity");

    auto name = e.name();
    EXPECT_EQ(name, "test_entity");
}

TEST(context_entity_handling, add_component_to_entity) {
    auto context = xlamb::Context();

    // create an entity
    auto e = context.create_entity("test_entity");

    struct Identification {
        std::string first_name;
        std::string last_name;
        size_t age;
    };

    const auto& id = e.add_component<Identification>("Test", "Entity", 42);

    const auto has_id = e.has_all_of<Identification>();
    EXPECT_TRUE(has_id);

    EXPECT_EQ(id.first_name, "Test");
    EXPECT_EQ(id.last_name, "Entity");
    EXPECT_EQ(id.age, 42);

}

TEST(context_entity_handling, get_component) {
    auto context = xlamb::Context();

    // create an entity
    auto e = context.create_entity("test_entity");

    struct Identification {
        std::string first_name;
        std::string last_name;
        size_t age;
    };

    e.add_component<Identification>("Test", "Entity", 42);

    const auto has_id = e.has_all_of<Identification>();
    EXPECT_TRUE(has_id);

    const auto& id = e.get_component<Identification>();
    EXPECT_EQ(id.first_name, "Test");
    EXPECT_EQ(id.last_name, "Entity");
    EXPECT_EQ(id.age, 42);
}

TEST(context_entity_handling, replace_component) {
    auto context = xlamb::Context();

    // create an entity
    auto e = context.create_entity("test_entity");

    struct Identification {
        std::string first_name;
        std::string last_name;
        size_t age;
    };

    auto& id = e.add_component<Identification>("Test", "Entity", 42);
    
    const auto has_id = e.has_all_of<Identification>();
    EXPECT_TRUE(has_id);

    EXPECT_EQ(id.first_name, "Test");
    EXPECT_EQ(id.last_name, "Entity");
    EXPECT_EQ(id.age, 42);

    e.add_or_replace_component<Identification>("ABC", "DEF", 123);

    id = e.get_component<Identification>();
    EXPECT_EQ(id.first_name, "ABC");
    EXPECT_EQ(id.last_name, "DEF");
    EXPECT_EQ(id.age, 123);
}

TEST(context_entity_handling, get_multiple_components) {
    auto context = xlamb::Context();

    // create an entity
    auto e = context.create_entity("test_entity");

    struct Identification {
        std::string first_name;
        std::string last_name;
        size_t age;
    };

    struct Employment {
        std::string position;
        std::string employer;
    };

    e.add_component<Identification>("Test", "Entity", 42);
    e.add_component<Employment>("Tester", "Entity Factory");

    const auto has_id_and_job = e.has_all_of<Identification, Employment>();
    EXPECT_TRUE(has_id_and_job);

    const auto& [id, job] = e.get_components<Identification, Employment>();
    EXPECT_EQ(id.first_name, "Test");
    EXPECT_EQ(id.last_name, "Entity");
    EXPECT_EQ(id.age, 42);

    EXPECT_EQ(job.position, "Tester");
    EXPECT_EQ(job.employer, "Entity Factory");
}

TEST(context_entity_handling, has_all_of) {
    auto context = xlamb::Context();

    // create an entity
    auto e1 = context.create_entity("test_entity_1");
    auto e2 = context.create_entity("test_entity_2");

    struct Identification {
        std::string first_name;
        std::string last_name;
        size_t age;
    };

    struct Employment {
        std::string position;
        std::string employer;
    };

    e1.add_component<Identification>("Test", "Entity", 42);
    e1.add_component<Employment>("Tester", "Entity Factory");

    e2.add_component<Identification>("ABC", "DEF", 123);

    const auto e1_has_all = e1.has_all_of<Identification, Employment>();
    const auto e2_has_all = e2.has_all_of<Identification, Employment>();

    EXPECT_TRUE(e1_has_all);
    EXPECT_FALSE(e2_has_all);
}

TEST(context_entity_handling, has_any_of) {
    auto context = xlamb::Context();

    // create an entity
    auto e1 = context.create_entity("test_entity_1");
    auto e2 = context.create_entity("test_entity_2");
    auto e3 = context.create_entity("test_entity_3");

    struct Identification {
        std::string first_name;
        std::string last_name;
        size_t age;
    };

    struct Employment {
        std::string position;
        std::string employer;
    };

    e1.add_component<Identification>("Test", "Entity", 42);
    e1.add_component<Employment>("Tester", "Entity Factory");

    e2.add_component<Identification>("ABC", "DEF", 123);

    e3.add_component<Employment>("Tester", "Entity Factory");

    const auto e1_has_any = e1.has_any_of<Identification, Employment>();
    const auto e2_has_any = e2.has_any_of<Identification, Employment>();
    const auto e3_has_any = e3.has_any_of<Identification, Employment>();

    EXPECT_TRUE(e1_has_any);
    EXPECT_TRUE(e2_has_any);
    EXPECT_TRUE(e3_has_any);
}