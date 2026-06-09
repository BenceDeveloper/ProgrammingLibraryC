#pragma once

#include <filesystem>
#include <fstream>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

namespace proglib {

// ============================================================
//  FileHandler
//  Fájl olvasás / írás RAII wrapper.
//  A puffer mérete dinamikusan változik std::vector<char> alapon.
// ============================================================
class FileHandler {
public:
    // --- Konstruktorok -------------------------------------------
    explicit FileHandler(std::filesystem::path path)
        : path_{ std::move(path) }
    {}

    /// Előre lefoglalt puffer-kapacitással
    FileHandler(std::filesystem::path path, std::size_t max_size)
        : path_{ std::move(path) }
    {
        buffer_.reserve(max_size);
    }

    // Rule of five: vector kezeli a memóriát, nincs kézzel írt destruktor.
    FileHandler(const FileHandler&)            = default;
    FileHandler& operator=(const FileHandler&) = default;
    FileHandler(FileHandler&&)                 = default;
    FileHandler& operator=(FileHandler&&)      = default;
    ~FileHandler()                             = default;

    // --- Műveletek -----------------------------------------------

    /// Beolvassa a fájl tartalmát a belső pufferbe.
    /// @throws std::runtime_error ha a fájl nem nyitható meg.
    void read()
    {
        std::ifstream file{ path_, std::ios::binary | std::ios::ate };
        if (!file.is_open()) {
            throw std::runtime_error{ "Nem lehet megnyitni a fájlt olvasásra: "
                                      + path_.string() };
        }

        const auto file_size = static_cast<std::size_t>(file.tellg());
        const auto read_size = (buffer_.capacity() > 0)
                                   ? std::min(file_size, buffer_.capacity())
                                   : file_size;

        buffer_.resize(read_size);
        file.seekg(0);
        file.read(buffer_.data(), static_cast<std::streamsize>(read_size));
    }

    /// Kiírja a belső puffer tartalmát a fájlba.
    /// @throws std::runtime_error ha a fájl nem nyitható meg.
    void write() const
    {
        std::ofstream file{ path_, std::ios::binary };
        if (!file.is_open()) {
            throw std::runtime_error{ "Nem lehet megnyitni a fájlt írásra: "
                                      + path_.string() };
        }
        file.write(buffer_.data(), static_cast<std::streamsize>(buffer_.size()));
    }

    // --- Adathozzáférés ------------------------------------------


    [[nodiscard]] std::string to_string() const
    {
        return { buffer_.begin(), buffer_.end() };
    }

    /// Nyers hozzáférés a pufferhez (read-only span).
    [[nodiscard]] std::span<const char> data() const noexcept
    {
        return buffer_;
    }

    /// Nyers hozzáférés a pufferhez (módosítható span).
    [[nodiscard]] std::span<char> data() noexcept
    {
        return buffer_;
    }

    /// Visszaadja az elérési utat.
    [[nodiscard]] const std::filesystem::path& path() const noexcept
    {
        return path_;
    }

    /// A pufferben lévő bájtok száma.
    [[nodiscard]] std::size_t size() const noexcept
    {
        return buffer_.size();
    }

    [[nodiscard]] bool empty() const noexcept
    {
        return buffer_.empty();
    }

    /// Közvetlen írás a pufferbe (pl. teszteléshez vagy generáláshoz).
    void set_data(std::string_view content)
    {
        buffer_.assign(content.begin(), content.end());
    }

private:
    std::filesystem::path path_;
    std::vector<char>     buffer_;
};

} // namespace proglib
