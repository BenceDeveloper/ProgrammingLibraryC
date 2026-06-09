#pragma once

#include <algorithm>
#include <concepts>
#include <functional>
#include <numeric>
#include <optional>
#include <span>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

namespace proglib {

// ============================================================
//  Concepts
// ============================================================

template <typename T>
concept Numeric = std::is_arithmetic_v<T>;

template <typename T>
concept Sortable = std::totally_ordered<T>;

// ============================================================
//  SortOrder — rendezési irány erős típussal
// ============================================================
enum class SortOrder { Ascending, Descending };

// ============================================================
//  ArrayManager<T>
//  Generikus tömb-kezelő és algoritmus-gyűjtemény.
//  A tömb memóriáját std::vector kezeli (nincs kézi new/delete).
// ============================================================
template <Sortable T>
class ArrayManager {
public:
    // --- Konstruktorok ---------------------------------------

    /// Másolatot készít a megadott adatokból.
    explicit ArrayManager(std::span<const T> data)
        : data_{ data.begin(), data.end() }
    {}

    /// Inicializáló listából.
    ArrayManager(std::initializer_list<T> values)
        : data_{ values }
    {}

    ArrayManager()                               = default;
    ArrayManager(const ArrayManager&)            = default;
    ArrayManager& operator=(const ArrayManager&) = default;
    ArrayManager(ArrayManager&&)                 = default;
    ArrayManager& operator=(ArrayManager&&)      = default;
    ~ArrayManager()                              = default;

    // --- Adathozzáférés --------------------------------------

    [[nodiscard]] std::size_t          size()  const noexcept { return data_.size(); }
    [[nodiscard]] bool                 empty() const noexcept { return data_.empty(); }
    [[nodiscard]] std::span<const T>   view()  const noexcept { return data_; }
    [[nodiscard]] std::span<T>         view()        noexcept { return data_; }

    [[nodiscard]] const T& operator[](std::size_t i) const { return data_.at(i); }
    [[nodiscard]]       T& operator[](std::size_t i)       { return data_.at(i); }

    // --- Algoritmusok ----------------------------------------

    /// Rendezés a megadott irányban (std::sort alapon).
    void sort(SortOrder order = SortOrder::Ascending)
    {
        if (order == SortOrder::Ascending) {
            std::sort(data_.begin(), data_.end());
        } else {
            std::sort(data_.begin(), data_.end(), std::greater<T>{});
        }
    }

    /// Bubble-sort (nagy tömbre lassú).
    void bubble_sort(SortOrder order = SortOrder::Ascending)
    {
        const auto cmp = make_comparator(order);
        const std::size_t n = data_.size();
        for (std::size_t i = 0; i + 1 < n; ++i) {
            bool swapped = false;
            for (std::size_t j = 0; j + 1 < n - i; ++j) {
                if (cmp(data_[j + 1], data_[j])) {
                    std::swap(data_[j], data_[j + 1]);
                    swapped = true;
                }
            }
            if (!swapped) break;
        }
    }

    /// Insertion-sort.
    void insertion_sort(SortOrder order = SortOrder::Ascending)
    {
        const auto cmp = make_comparator(order);
        for (std::size_t i = 1; i < data_.size(); ++i) {
            T key = data_[i];
            std::size_t j = i;
            while (j > 0 && cmp(key, data_[j - 1])) {
                data_[j] = data_[j - 1];
                --j;
            }
            data_[j] = key;
        }
    }

    /// Shell-sort.
    void shell_sort(SortOrder order = SortOrder::Ascending)
    {
        const auto cmp = make_comparator(order);
        for (std::size_t gap = data_.size() / 2; gap > 0; gap /= 2) {
            for (std::size_t i = gap; i < data_.size(); ++i) {
                T temp = data_[i];
                std::size_t j = i;
                while (j >= gap && cmp(temp, data_[j - gap])) {
                    data_[j] = data_[j - gap];
                    j -= gap;
                }
                data_[j] = temp;
            }
        }
    }

    /// Lineáris keresés; visszaadja az első találat indexét, vagy std::nullopt-ot.
    [[nodiscard]] std::optional<std::size_t> linear_search(const T& target) const noexcept
    {
        for (std::size_t i = 0; i < data_.size(); ++i) {
            if (data_[i] == target) return i;
        }
        return std::nullopt;
    }

    // --- Numerikus műveletek ----

    /// Összes elem összege.
    /// Csak Numeric típusoknál érhető el (requires clause).
    [[nodiscard]] T sum() const noexcept
        requires Numeric<T>
    {
        return std::reduce(data_.begin(), data_.end(), T{ 0 });
    }

    /// Elemek átlaga (double-ként).
    [[nodiscard]] double average() const
        requires Numeric<T>
    {
        if (data_.empty()) throw std::runtime_error{ "ArrayManager: üres tömb" };
        return static_cast<double>(sum()) / static_cast<double>(data_.size());
    }

    // --- Számlálás -----------------

    /// Megszámolja azokat az elemeket, amelyekre igaz.
    template <std::predicate<const T&> Pred>
    [[nodiscard]] std::size_t count_if(Pred&& pred) const noexcept
    {
        return static_cast<std::size_t>(
            std::count_if(data_.begin(), data_.end(), std::forward<Pred>(pred)));
    }

    /// Megszámolja az adott értékkel egyenlő elemeket.
    [[nodiscard]] std::size_t count(const T& value) const noexcept
    {
        return count_if([&value](const T& x) { return x == value; });
    }

    // --- String --------------------------------

    [[nodiscard]] std::string to_string() const
    {
        std::string result = "[";
        for (std::size_t i = 0; i < data_.size(); ++i) {
            if (i > 0) result += ", ";
            result += std::to_string(data_[i]);
        }
        result += ']';
        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const ArrayManager& am)
    {
        return os << am.to_string();
    }

private:
    std::vector<T> data_;

    // Összehasonlító függvény SortOrder-ből
    static auto make_comparator(SortOrder order)
    {
        if (order == SortOrder::Ascending) {
            return std::function<bool(const T&, const T&)>{ std::less<T>{} };
        }
        return std::function<bool(const T&, const T&)>{ std::greater<T>{} };
    }
};

} // namespace proglib
