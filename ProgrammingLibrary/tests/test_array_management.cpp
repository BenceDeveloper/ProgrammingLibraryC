#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_range_equals.hpp>

#include <proglib/array_management.hpp>

using namespace proglib;
using Catch::Matchers::RangeEquals;

// ================================================================
//  ArrayManager tesztek
// ================================================================

TEST_CASE("ArrayManager – alapok", "[array]") {
    ArrayManager<int> am{ 3, 1, 4, 1, 5, 9, 2, 6 };

    SECTION("méret") {
        REQUIRE(am.size() == 8);
        REQUIRE_FALSE(am.empty());
    }

    SECTION("üres manager") {
        ArrayManager<int> empty{};
        REQUIRE(empty.empty());
        REQUIRE(empty.size() == 0);
    }

    SECTION("indexelés") {
        REQUIRE(am[0] == 3);
        REQUIRE(am[4] == 5);
    }
}

TEST_CASE("ArrayManager – numerikus műveletek", "[array][numeric]") {
    ArrayManager<int> am{ 1, 2, 3, 4, 5 };

    SECTION("sum") {
        REQUIRE(am.sum() == 15);
    }

    SECTION("average") {
        REQUIRE(am.average() == 3.0);
    }

    SECTION("sum üres tömbnél kivételt dob") {
        ArrayManager<int> empty{};
        REQUIRE_THROWS_AS(empty.average(), std::runtime_error);
    }
}

TEST_CASE("ArrayManager – rendezés: std::sort", "[array][sort]") {
    SECTION("növekvő") {
        ArrayManager<int> am{ 5, 3, 1, 4, 2 };
        am.sort(SortOrder::Ascending);
        REQUIRE_THAT(am.view(), RangeEquals(std::vector{ 1, 2, 3, 4, 5 }));
    }

    SECTION("csökkenő") {
        ArrayManager<int> am{ 5, 3, 1, 4, 2 };
        am.sort(SortOrder::Descending);
        REQUIRE_THAT(am.view(), RangeEquals(std::vector{ 5, 4, 3, 2, 1 }));
    }
}

TEST_CASE("ArrayManager – bubble_sort", "[array][sort]") {
    SECTION("növekvő") {
        ArrayManager<int> am{ 5, 2, 8, 1, 9 };
        am.bubble_sort(SortOrder::Ascending);
        REQUIRE_THAT(am.view(), RangeEquals(std::vector{ 1, 2, 5, 8, 9 }));
    }

    SECTION("csökkenő") {
        ArrayManager<int> am{ 5, 2, 8, 1, 9 };
        am.bubble_sort(SortOrder::Descending);
        REQUIRE_THAT(am.view(), RangeEquals(std::vector{ 9, 8, 5, 2, 1 }));
    }

    SECTION("már rendezett tömb") {
        ArrayManager<int> am{ 1, 2, 3, 4, 5 };
        am.bubble_sort();
        REQUIRE_THAT(am.view(), RangeEquals(std::vector{ 1, 2, 3, 4, 5 }));
    }

    SECTION("egy elemű tömb") {
        ArrayManager<int> am{ 42 };
        am.bubble_sort();
        REQUIRE(am[0] == 42);
    }
}

TEST_CASE("ArrayManager – insertion_sort", "[array][sort]") {
    ArrayManager<int> am{ 5, 2, 8, 1, 9 };
    am.insertion_sort(SortOrder::Ascending);
    REQUIRE_THAT(am.view(), RangeEquals(std::vector{ 1, 2, 5, 8, 9 }));
}

TEST_CASE("ArrayManager – shell_sort", "[array][sort]") {
    ArrayManager<int> am{ 64, 25, 12, 22, 11 };
    am.shell_sort(SortOrder::Ascending);
    REQUIRE_THAT(am.view(), RangeEquals(std::vector{ 11, 12, 22, 25, 64 }));
}

TEST_CASE("ArrayManager – lineáris keresés", "[array][search]") {
    ArrayManager<int> am{ 10, 20, 30, 40, 50 };

    SECTION("megtalált elem") {
        auto idx = am.linear_search(30);
        REQUIRE(idx.has_value());
        REQUIRE(*idx == 2);
    }

    SECTION("nem létező elem → nullopt") {
        REQUIRE_FALSE(am.linear_search(99).has_value());
    }

    SECTION("első elem") {
        REQUIRE(*am.linear_search(10) == 0);
    }

    SECTION("utolsó elem") {
        REQUIRE(*am.linear_search(50) == 4);
    }
}

TEST_CASE("ArrayManager – count", "[array]") {
    ArrayManager<int> am{ 1, 2, 2, 3, 2, 4 };

    SECTION("count konkrét értékre") {
        REQUIRE(am.count(2) == 3);
        REQUIRE(am.count(9) == 0);
    }

    SECTION("count_if predikátummal") {
        REQUIRE(am.count_if([](int x) { return x > 2; }) == 2);
    }
}

TEST_CASE("ArrayManager – double tömb (template variáció)", "[array][template]") {
    ArrayManager<double> am{ 3.5, 1.2, 2.8 };
    am.sort();
    REQUIRE(am[0] == 1.2);
    REQUIRE(am.sum() == Catch::Approx(7.5));
}

TEST_CASE("ArrayManager – string tömb (csak rendezés)", "[array][template]") {
    ArrayManager<std::string> am{ "banana", "apple", "cherry" };
    am.sort();
    REQUIRE(am[0] == "apple");
    REQUIRE(am[1] == "banana");
    REQUIRE(am[2] == "cherry");
}
