#pragma once

#include <concepts>
#include <functional>
#include <memory>
#include <optional>
#include <ostream>
#include <stdexcept>
#include <vector>

namespace proglib {

// ============================================================
//  Concept: Ordered
//  A BinaryTree csak olyan típusokkal használható, amelyek
//  rendelkeznek < és == operátorral (pl. int, double, string).
// ============================================================
template <typename T>
concept Ordered = std::totally_ordered<T>;

// ============================================================
//  BinarySearchTree<T>
//  Generikus bináris keresőfa.
//  - unique_ptr kezeli a memóriát (nincs kézzel írt delete)
//  - Concepts korlátozza a típusparamétert
//  - Traversal eredménye visszaadható vector-ban, nem csak cout
// ============================================================
template <Ordered T>
class BinarySearchTree {
private:
    struct Node {
        T                    value;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;

        explicit Node(T val) : value{ std::move(val) } {}
    };

    std::unique_ptr<Node> root_;
    std::size_t           size_{ 0 };

    // ----- Privát rekurzív segédfüggvények -------------------

    static std::unique_ptr<Node> insert_impl(std::unique_ptr<Node> node, T value)
    {
        if (!node) {
            return std::make_unique<Node>(std::move(value));
        }
        if (value < node->value) {
            node->left  = insert_impl(std::move(node->left),  std::move(value));
        } else if (value > node->value) {
            node->right = insert_impl(std::move(node->right), std::move(value));
        }
        // egyenlő érték: nem szúrunk be duplikátumot
        return node;
    }

    static bool contains_impl(const Node* node, const T& value) noexcept
    {
        if (!node)              return false;
        if (value == node->value) return true;
        if (value < node->value)  return contains_impl(node->left.get(),  value);
        return                           contains_impl(node->right.get(), value);
    }

    static void inorder_impl(const Node* node, std::vector<T>& out)
    {
        if (!node) return;
        inorder_impl(node->left.get(),  out);
        out.push_back(node->value);
        inorder_impl(node->right.get(), out);
    }

    static void preorder_impl(const Node* node, std::vector<T>& out)
    {
        if (!node) return;
        out.push_back(node->value);
        preorder_impl(node->left.get(),  out);
        preorder_impl(node->right.get(), out);
    }

    static void postorder_impl(const Node* node, std::vector<T>& out)
    {
        if (!node) return;
        postorder_impl(node->left.get(),  out);
        postorder_impl(node->right.get(), out);
        out.push_back(node->value);
    }

    static const Node* min_node(const Node* node) noexcept
    {
        while (node->left) node = node->left.get();
        return node;
    }

    static const Node* max_node(const Node* node) noexcept
    {
        while (node->right) node = node->right.get();
        return node;
    }

    static int height_impl(const Node* node) noexcept
    {
        if (!node) return 0;
        return 1 + std::max(height_impl(node->left.get()),
                            height_impl(node->right.get()));
    }

public:
    // --- Konstruktorok / Rule of five ------------------------
    BinarySearchTree()                                   = default;
    BinarySearchTree(const BinarySearchTree&)            = delete;  // deep copy drága, explicit tiltjuk
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;
    BinarySearchTree(BinarySearchTree&&)                 = default;
    BinarySearchTree& operator=(BinarySearchTree&&)      = default;
    ~BinarySearchTree()                                  = default;

    BinarySearchTree(std::initializer_list<T> values)
    {
        for (auto& v : values) insert(v);
    }

    // --- Módosítók -------------------------------------------

    void insert(T value)
    {
        const bool was_present = contains(value);
        root_ = insert_impl(std::move(root_), std::move(value));
        if (!was_present) ++size_;
    }

    // --- Lekérdezők ------------------------------------------

    [[nodiscard]] bool contains(const T& value) const noexcept
    {
        return contains_impl(root_.get(), value);
    }

    [[nodiscard]] bool empty() const noexcept { return root_ == nullptr; }

    [[nodiscard]] std::size_t size() const noexcept { return size_; }

    [[nodiscard]] int height() const noexcept
    {
        return height_impl(root_.get());
    }

    /// A fa minimuma.
    /// @throws std::runtime_error üres fánál.
    [[nodiscard]] const T& min() const
    {
        if (empty()) throw std::runtime_error{ "BinarySearchTree: üres fa" };
        return min_node(root_.get())->value;
    }

    /// A fa maximuma.
    /// @throws std::runtime_error üres fánál.
    [[nodiscard]] const T& max() const
    {
        if (empty()) throw std::runtime_error{ "BinarySearchTree: üres fa" };
        return max_node(root_.get())->value;
    }

    // --- Bejárások (visszaad egy std::vector<T>-t) -----------

    [[nodiscard]] std::vector<T> inorder()   const
    {
        std::vector<T> result;
        result.reserve(size_);
        inorder_impl(root_.get(), result);
        return result;
    }

    [[nodiscard]] std::vector<T> preorder()  const
    {
        std::vector<T> result;
        result.reserve(size_);
        preorder_impl(root_.get(), result);
        return result;
    }

    [[nodiscard]] std::vector<T> postorder() const
    {
        std::vector<T> result;
        result.reserve(size_);
        postorder_impl(root_.get(), result);
        return result;
    }

    // --- kiírás ---------------------------------------

    friend std::ostream& operator<<(std::ostream& os, const BinarySearchTree& tree)
    {
        os << "[ ";
        for (const auto& v : tree.inorder()) os << v << ' ';
        os << ']';
        return os;
    }
};

} // namespace proglib
