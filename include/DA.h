#pragma once
#include <string>

namespace DA {
    template<typename T>
    class DynArr {
        T *arr;
        size_t size;
        size_t capacity;
        size_t FACTOR;

        void expand() {
            const size_t new_capacity = capacity * FACTOR;
            T *new_arr = new T[new_capacity];
            set_new_main_array(new_arr, new_capacity);
        }

        void reduce() {
            const size_t new_capacity = capacity / FACTOR;
            T *new_arr = new T[new_capacity];
            set_new_main_array(new_arr, new_capacity);
        }

        void set_new_main_array(T *new_arr, const size_t new_capacity) {
            if (!new_arr || new_capacity < size) {
                throw std::runtime_error("Error occurred while setting new main array");
            }

            for (size_t i = 0; i < size; i++) {
                new_arr[i] = arr[i];
            }

            delete[] arr;
            capacity = new_capacity;
            arr = new_arr;
        }

    public:
        explicit DynArr(const size_t capacity = 1, const size_t FACTOR = 2) : size(0), capacity(capacity),
                                                                              FACTOR(FACTOR) {
            if (capacity < 1) throw std::invalid_argument("Capacity must be >= 1.");
            if (FACTOR <= 1) throw std::invalid_argument("FACTOR must be > 1.");
            arr = new T[capacity]();
        }

        DynArr(const DynArr &other) : arr(new T[other.capacity]),
                                      size(other.size),
                                      capacity(other.capacity),
                                      FACTOR(other.FACTOR) {
            for (size_t i = 0; i < size; i++) {
                arr[i] = other.arr[i];
            }
        }

        DynArr &operator=(DynArr other) {
            swap(*this, other);
            return *this;
        }

        ~DynArr() {
            delete[] arr;
        }

        size_t get_size() const {
            return size;
        }

        size_t get_capacity() const {
            return capacity;
        }

        size_t get_factor() const {
            return FACTOR;
        }

        void push(T data) {
            if (size == capacity) { expand(); }
            arr[size] = data;
            size++;
        }

        bool pop(const size_t index) {
            if (index >= size) { return false; }

            if (size == capacity / FACTOR) { reduce(); }
            for (size_t i = index; i < size - 1; i++) {
                arr[i] = arr[i + 1];
            }
            size--;

            return true;
        }

        void clear(const bool save_capacity = false) {
            size = 0;
            if (!save_capacity) { capacity = 1; }
            delete[] arr;
            arr = new T[capacity];
        }

        T &operator[](const size_t index) {
            if (index >= size) {
                throw std::out_of_range(
                    "Error: index " + std::to_string(index) + " was not in array range <0," +
                    std::to_string(static_cast<int>(size)) + ")");
            }

            return arr[index];
        }

        const T &operator[](const size_t index) const {
            if (index >= size) {
                throw std::out_of_range(
                    "Error: index " + std::to_string(index) + " was not in array range <0," +
                    std::to_string(static_cast<int>(size)) + ")");
            }

            return arr[index];
        }

        std::string to_str(unsigned int limit = 0, std::string (*fun_str)(T) = nullptr) const {
            if (limit == 0 || limit > size) {
                limit = size;
            }

            std::string text = "Dynamic Array:\n";
            text += "size: " + std::to_string(static_cast<int>(size)) + "\n";
            text += "capacity: " + std::to_string(static_cast<int>(capacity)) + "\n";
            text += "factor: " + std::to_string(static_cast<int>(FACTOR)) + "\n";
            text += "{\n";
            if (fun_str) {
                for (int i = 0; i < limit; i++) {
                    text += fun_str(arr[i]);
                    text += "\n";
                }
            } else if constexpr (std::is_arithmetic_v<T>) {
                for (int i = 0; i < limit; i++) {
                    text += std::to_string(arr[i]);
                    text += "\n";
                }
            } else {
                text = "T is not arithmetic and no cmp was provided\n";
            }

            if (limit < size) {
                text += "[...]\n";
            }
            text += "}\n";

            return text;
        }
    };
}
