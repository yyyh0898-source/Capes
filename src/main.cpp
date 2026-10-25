
#include "CapeLibrary.hpp"
#include <iostream>

int main() {
    bedrock::capes::CapeLibrary library;

    for (const auto& cape : library.list()) {
        std::cout << cape.id << " — "
                  << cape.name << '\n';
    }

    if (library.equip("crimson")) {
        std::cout << "Selected cape: "
                  << library.equipped()->name
                  << '\n';
    }

    return 0;
}
