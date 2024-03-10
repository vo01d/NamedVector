#include "NamedVector.h"

#include <iostream>

int main() {
    try {
        NamedVector<int> namedVector1;
        namedVector1.reserve(100);

        std::cout << "namedVector1::capacity = " << namedVector1.capacity() << std::endl << std::endl;

        namedVector1.push_back(1, "one");
        namedVector1.push_back(2, "two");
        namedVector1.push_back(3, "three");

        if (namedVector1.empty()) {
            std::cout << "namedVector1 is empty" << std::endl;
        }
        else {
            std::cout << "namedVector1::size = " << namedVector1.size() << std::endl;
        }
        std::cout << std::endl;

        for (const auto& [value, name] : namedVector1) {
            std::cout << "namedVector1::value =  " << value << ", namedVector1::name = " << name << std::endl;
        }
        std::cout << std::endl;

        NamedVector<int> namedVector2 = namedVector1;
        namedVector2.push_back(4, "four");
        namedVector2.push_back(5, "four");

        for (const auto& [value, name] : namedVector2) {
            std::cout << "namedVector2::value =  " << value << ", namedVector1::name = " << name << std::endl;
        }
        std::cout << std::endl;

        std::cout << "namedVector2::name \"four\" value = " << namedVector2["four"] << std::endl << std::endl;

        namedVector2.clear();

        if (namedVector2.empty()) {
            std::cout << "namedVector2 is empty" << std::endl;
        }
        else {
            std::cout << "namedVector2::size = " << namedVector2.size() << std::endl;
        }
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
    catch (...) {
        std::cout << "Something went wrong!" << std::endl;
    }

    return 0;
}