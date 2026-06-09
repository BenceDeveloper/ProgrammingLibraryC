#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_range_equals.hpp>

#include <proglib/binary_tree.hpp>

using namespace proglib;
using Catch::Matchers::RangeEquals;

// ================================================================
//  BinarySearchTree tesztek
// ================================================================

TEST_CASE("BinarySearchTree – alapok", "[tree]") {
    BinarySearchTree<int> tree;

    SECTION("üres fa") {
        REQUIRE(tree.empty());
        REQUIRE(tree.size() == 0);
        REQUIRE(tree.height() == 0);
    }

    SECTION("insert után nem üres") {
        tree.insert(5);
        REQUIRE_FALSE(tree.empty());
        REQUIRE(tree.size() == 1);
    }
}

TEST_CASE("BinarySearchTree – duplikátum kezelés", "[tree]") {
    BinarySearchTree<int> tree{ 5, 5, 5 };
    REQUIRE(tree.size() == 1);
}

TEST_CASE("BinarySearchTree – contains", "[tree]") {
    BinarySearchTree<int> tree{ 5, 3, 7, 1, 4 };

    REQUIRE(tree.contains(5));
    REQUIRE(tree.contains(1));
    REQUIRE(tree.contains(7));
    REQUIRE_FALSE(tree.contains(99));
    REQUIRE_FALSE(tree.contains(0));
}

TEST_CASE("BinarySearchTree – inorder rendezetten ad vissza", "[tree][traversal]") {
    BinarySearchTree<int> tree{ 5, 3, 7, 1, 4, 6, 8 };
    REQUIRE_THAT(tree.inorder(), RangeEquals(std::vector{ 1, 3, 4, 5, 6, 7, 8 }));
}

TEST_CASE("BinarySearchTree – preorder", "[tree][traversal]") {
    BinarySearchTree<int> tree{ 5, 3, 7 };
    REQUIRE_THAT(tree.preorder(), RangeEquals(std::vector{ 5, 3, 7 }));
}

TEST_CASE("BinarySearchTree – postorder", "[tree][traversal]") {
    BinarySearchTree<int> tree{ 5, 3, 7 };
    REQUIRE_THAT(tree.postorder(), RangeEquals(std::vector{ 3, 7, 5 }));
}

TEST_CASE("BinarySearchTree – min / max", "[tree]") {
    BinarySearchTree<int> tree{ 5, 3, 7, 1, 9 };

    REQUIRE(tree.min() == 1);
    REQUIRE(tree.max() == 9);
}

TEST_CASE("BinarySearchTree – min/max üres fánál kivételt dob", "[tree]") {
    BinarySearchTree<int> tree;
    REQUIRE_THROWS_AS(tree.min(), std::runtime_error);
    REQUIRE_THROWS_AS(tree.max(), std::runtime_error);
}

TEST_CASE("BinarySearchTree – magasság", "[tree]") {
    BinarySearchTree<int> tree;
    REQUIRE(tree.height() == 0);

    tree.insert(5);
    REQUIRE(tree.height() == 1);

    tree.insert(3);
    tree.insert(7);
    REQUIRE(tree.height() == 2);

    tree.insert(1);
    REQUIRE(tree.height() == 3);
}

TEST_CASE("BinarySearchTree – initializer_list konstruktor", "[tree]") {
    BinarySearchTree<int> tree{ 4, 2, 6, 1, 3, 5, 7 };
    REQUIRE(tree.size() == 7);
    REQUIRE_THAT(tree.inorder(), RangeEquals(std::vector{ 1, 2, 3, 4, 5, 6, 7 }));
}

TEST_CASE("BinarySearchTree – string típus (concept teszt)", "[tree][template]") {
    BinarySearchTree<std::string> tree{ "banana", "apple", "cherry" };
    REQUIRE_THAT(tree.inorder(),
                 RangeEquals(std::vector<std::string>{ "apple", "banana", "cherry" }));
}

TEST_CASE("BinarySearchTree – move semantics", "[tree]") {
    BinarySearchTree<int> a{ 1, 2, 3 };
    BinarySearchTree<int> b = std::move(a);
    REQUIRE(b.size() == 3);
    REQUIRE(b.contains(2));
}
