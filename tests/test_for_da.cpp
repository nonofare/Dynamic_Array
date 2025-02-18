#include <iostream>
#include <random>
#include <chrono>
#include "DA.h"

struct some_object {
    int field_1;
    char field_2;
};

std::string so_fun_str(some_object *so) {
    return "(" + std::to_string(so->field_1) + ", " + so->field_2 + ")";
}

bool so_cmp_lgreater(some_object *so1, some_object *so2) {
    if (so1->field_1 == so2->field_1) {
        return so1->field_2 > so2->field_2;
    }
    return so1->field_1 > so2->field_1;
}

int main() {
    constexpr int MAX_ORDER = 6;
    constexpr int LETTERS_SIZE = 26;
    constexpr char LETTERS[LETTERS_SIZE] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
        'W', 'X', 'Y', 'Z'
    };

    static std::random_device rd;
    static std::default_random_engine dre(rd());
    std::uniform_int_distribution<int> rnd_num(0, MAX_ORDER * 1000);
    std::uniform_int_distribution<int> rnd_let(0, LETTERS_SIZE - 1);

    auto *da = new DA::DynArr<some_object *>();

    std::cout << "--------------------------------" << std::endl;
    std::cout << "Pushing phase: " << std::endl;

    const int n = pow(10, MAX_ORDER);
    double max_time_per_element = 0.0;

    std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();
    for (int i = 1; i <= n; i++) {
        auto *so = new some_object();
        so->field_1 = rnd_num(dre);
        so->field_2 = LETTERS[rnd_let(dre)];

        std::chrono::high_resolution_clock::time_point element_start_time = std::chrono::high_resolution_clock::now();
        da->push(so);
        std::chrono::high_resolution_clock::time_point element_end_time = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> time_per_element = element_end_time - element_start_time;
        if (time_per_element.count() > max_time_per_element) {
            max_time_per_element = time_per_element.count();
            std::cout << "New worst push time: " << max_time_per_element << "s, at index: " << i << std::endl;
        }
    }
    std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();

    const std::chrono::duration<double> pushing_time = end_time - start_time;
    std::cout << da->to_str(10, so_fun_str);

    std::cout << "--------------------------------" << std::endl;
    std::cout << "Removing phase: " << std::endl;

    start_time = std::chrono::high_resolution_clock::now();
    da->clear();
    end_time = std::chrono::high_resolution_clock::now();

    const std::chrono::duration<double> removing_time = end_time - start_time;
    std::cout << da->to_str(10, so_fun_str);

    std::cout << "--------------------------------" << std::endl;
    std::cout << "Summary: " << std::endl;

    const double total_time = pushing_time.count() + removing_time.count();

    std::cout << "Elements: " << std::to_string(n) << std::endl;
    std::cout << "Pushing time: " << pushing_time.count() << "s" << std::endl;
    std::cout << "Amortized average pushing time for element: " << pushing_time.count() / n << "s" << std::endl;
    std::cout << "Removing time: " << removing_time.count() << "s" << std::endl;
    std::cout << "Total time: " << total_time << "s";

    delete da;
    return 0;
}
