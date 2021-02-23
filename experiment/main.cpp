#include <vector>
#include <algorithm>
#include <iostream>

int main() {
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {4, 5, 6};
    std::vector<int> v3 = {7, 8, 9};
    std::vector<int> a;

    {
        std::vector<int> dest;
        dest.reserve(6);

        std::set_union(v1.begin(), v1.end(),
                    v2.begin(), v2.end(),                  
                    std::back_inserter(dest));

        for (const auto &i : dest) {
            std::cout << i << ' ';
        }
        std::cout << "\n";
        a = dest;
    }
    std::cout << "a\n";
    for (const auto &i : a) {
            std::cout << i << ' ';
    }
    std::cout << '\n';  

    {
        std::vector<int> dest;
        std::set_union(a.begin(), a.end(),
                    v3.begin(), v3.end(),                  
                    std::back_inserter(dest));
        a = dest;
    }
    std::cout << "a\n";
    for (const auto &i : a) {
            std::cout << i << ' ';
    }
    std::cout << '\n';
    
    return 0;
}