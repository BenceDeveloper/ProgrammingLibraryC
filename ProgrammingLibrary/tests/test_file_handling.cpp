#include <catch2/catch_test_macros.hpp>

#include <proglib/file_handling.hpp>

#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;
using namespace proglib;

// ================================================================
//  Segédfüggvény: ideiglenes tesztfájl létrehozása
// ================================================================
static fs::path make_temp_file(const std::string& content = "")
{
    auto tmp = fs::temp_directory_path() / "proglib_test_XXXXXX";
    // egyedi névgenerálás tmpnam helyett
    static int counter = 0;
    tmp = fs::temp_directory_path() / ("proglib_test_" + std::to_string(++counter) + ".txt");
    if (!content.empty()) {
        std::ofstream f{ tmp };
        f << content;
    }
    return tmp;
}

// ================================================================
//  FileHandler tesztek
// ================================================================

TEST_CASE("FileHandler – read meglévő fájlból", "[file]") {
    const std::string content = "Hello, proglib!";
    auto path = make_temp_file(content);

    FileHandler fh{ path };
    fh.read();

    REQUIRE(fh.to_string() == content);
    REQUIRE(fh.size() == content.size());
    REQUIRE_FALSE(fh.empty());

    fs::remove(path);
}

TEST_CASE("FileHandler – write majd visszaolvas", "[file]") {
    auto path = make_temp_file();

    FileHandler writer{ path };
    writer.set_data("Teszt írás.");
    writer.write();

    FileHandler reader{ path };
    reader.read();
    REQUIRE(reader.to_string() == "Teszt írás.");

    fs::remove(path);
}

TEST_CASE("FileHandler – nem létező fájl olvasása kivételt dob", "[file]") {
    FileHandler fh{ "/nem/letezik/valami.txt" };
    REQUIRE_THROWS_AS(fh.read(), std::runtime_error);
}

TEST_CASE("FileHandler – nem írható helyre kivételt dob", "[file]") {
    FileHandler fh{ "/root/nem_irhat_ide.txt" };
    fh.set_data("adat");
    REQUIRE_THROWS_AS(fh.write(), std::runtime_error);
}

TEST_CASE("FileHandler – empty() üres puffernél", "[file]") {
    FileHandler fh{ "/valami.txt" };
    REQUIRE(fh.empty());
    REQUIRE(fh.size() == 0);
}

TEST_CASE("FileHandler – max_size korlátoz", "[file]") {
    const std::string long_content(500, 'A');
    auto path = make_temp_file(long_content);

    FileHandler fh{ path, 100 };
    fh.read();

    REQUIRE(fh.size() == 100);

    fs::remove(path);
}

TEST_CASE("FileHandler – bináris adat (null byte-ok)", "[file]") {
    auto path = fs::temp_directory_path() / "proglib_binary_test.bin";
    {
        std::ofstream f{ path, std::ios::binary };
        std::vector<char> data{ 0x00, 0x01, 0x02, 0xFF };
        f.write(data.data(), static_cast<std::streamsize>(data.size()));
    }

    FileHandler fh{ path };
    fh.read();
    REQUIRE(fh.size() == 4);
    REQUIRE(static_cast<unsigned char>(fh.data()[3]) == 0xFF);

    fs::remove(path);
}
