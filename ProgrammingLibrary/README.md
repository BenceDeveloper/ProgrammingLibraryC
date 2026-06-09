# ProgrammingLibraryC — C++20 header-only könyvtár

## Projektstruktúra

```
ProgramingLibrary/
├── include/
│   └── proglib/
│       ├── proglib.hpp
│       ├── array_management.hpp
│       ├── binary_tree.hpp
│       └── file_handling.hpp
├── tests/
│   ├── CMakeLists.txt
│   ├── test_array_management.cpp
│   ├── test_binary_tree.cpp
│   └── test_file_handling.cpp
├── cmake/
│   └── proglibConfig.cmake.in
├── CMakeLists.txt
└── README.md
```

## Gyors használat

```cpp
#include <proglib/proglib.hpp>

// ArrayManager
proglib::ArrayManager<int> arr{ 5, 3, 8, 1, 9 };
arr.sort(proglib::SortOrder::Ascending);
auto idx = arr.linear_search(8);   // std::optional<size_t>
int  s   = arr.sum();

// BinarySearchTree
proglib::BinarySearchTree<int> tree{ 5, 3, 7, 1, 4 };
tree.insert(6);
bool found = tree.contains(4);
auto sorted = tree.inorder();      // std::vector<int>

// FileHandler
proglib::FileHandler fh{ "adat.txt" };
fh.read();
std::string tartalom = fh.to_string();
```

## Build & tesztek futtatása

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
ctest --test-dir build --output-on-failure
```

## Beépítés FetchContent-tel

```cmake
include(FetchContent)
FetchContent_Declare(ProgrammingLibraryC
    GIT_REPOSITORY https://github.com/BenceDeveloper/ProgrammingLibraryC.git
    GIT_TAG        v1.0.0
)
FetchContent_MakeAvailable(ProgrammingLibraryC)
target_link_libraries(ProgrammingLibraryC PRIVATE proglib::proglib)
```