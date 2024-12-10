#pragma once
#include <string>

namespace DA {

	template <typename T>
	class DynArr {

		T* arr;
		size_t size;
		size_t capacity;
		const int FACTOR = 2;

		void ExpandArray() {
			size_t new_capacity = capacity * FACTOR;
			T* new_arr = nullptr;

			try {
				new_arr = new T[new_capacity];
				TransferMainArray(new_arr, new_capacity);
			}
			catch (const std::bad_alloc& ex) {
				throw std::runtime_error("DA::ExpandArray() -> " + std::string(ex.what()));
			}
			catch (const std::exception& ex) {
				delete[] new_arr;
				throw std::runtime_error("DA::ExpandArray() -> " + std::string(ex.what()));
			}
		}

		void ReduceArray() {
			size_t new_capacity = capacity / FACTOR;
			T* new_arr = nullptr;

			try {
				new_arr = new T[new_capacity];
				TransferMainArray(new_arr, new_capacity);
			}
			catch (const std::bad_alloc& ex) {
				throw std::runtime_error("DA::ReduceArray() -> " + std::string(ex.what()));
			}
			catch (const std::exception& ex) {
				delete[] new_arr;
				throw std::runtime_error("DA::ReduceArray() -> " + std::string(ex.what()));
			}
		}

		void TransferMainArray(T* in_arr, size_t in_capacity) {
			if (!in_arr) { throw std::invalid_argument("DA::TransferMainArray(): in_array was null"); }
			if (in_capacity < size) { throw std::length_error("DA::TransferMainArray(): in_capacity (" + std::to_string(in_capacity) + ") was smaller than the array size (" + std::to_string(int(size)) + ")"); }

			for (int i = 0; i < size; i++) {
				in_arr[i] = arr[i];
			}
			
			delete[] arr;
			capacity = in_capacity;
			arr = in_arr;
		}

	public:
		DynArr(size_t in_capacity = 1) {
			size = 0;
			capacity = in_capacity;
			try {
				arr = new T[capacity]{ nullptr };
			}
			catch (const std::bad_alloc& ex) {
				throw std::runtime_error("DA::Constructor -> " + std::string(ex.what()));
			}
		}

		~DynArr() {
			delete[] arr;
		}

		size_t Size() const {
			return size;
		}

		size_t Capacity() const {
			return capacity;
		}

		const int Factor() {
			return FACTOR;
		}

		void Push(T data) {
			if (size == capacity) {
				try {
					ExpandArray();
				}
				catch (const std::exception& ex) {
					throw std::runtime_error("DA::Push() -> " + std::string(ex.what()));
				}
			}

			arr[size] = data;
			size++;
		}

		void Pop(size_t index = size - 1) {
			if (index >= size) { throw std::length_error("DA::Pop(): index (" + std::to_string(index) + ") was greater or equal to array size (" + std::to_string(int(size)) + ")"); }

			if (size == capacity / FACTOR) {
				try {
					ReduceArray();
				}
				catch (const std::exception& ex) {
					throw std::runtime_error("DA::Pop() -> " + std::string(ex.what()));
				}
			}

			for (size_t i = index; i < size - 1; i++) {
				arr[i] = arr[i + 1];
			}
			size--;
		}

		void Erase() {
			delete[] arr;
			arr = nullptr;

			size = 0;
			capacity = 1;
			try {
				arr = new T[capacity];
			}
			catch (const std::bad_alloc& ex) {
				throw std::runtime_error("DA::Erase() -> " + std::string(ex.what()));
			}
		}

		void Sort(bool(*cmp_lgreater)(T, T)) {
			if (cmp_lgreater) {
				for (int i = 0; i < size - 1; i++) {
					for (int j = 0; j < size - i - 1; j++) {
						if (cmp_lgreater(arr[j], arr[j + 1])) {
							T temp = arr[j];
							arr[j] = arr[j + 1];
							arr[j + 1] = temp;
						}
					}
				}
			}
			else if constexpr (std::is_arithmetic_v<T>) {
				for (int i = 0; i < size - 1; i++) {
					for (int j = 0; j < size - i - 1; j++) {
						if (arr[j] > arr[j + 1]) {
							T temp = arr[j];
							arr[j] = arr[j + 1];
							arr[j + 1] = temp;
						}
					}
				}
			}
			else {
				throw std::runtime_error("DA::Sort(): T was not arithmetic and no cmp was provided");
			}
		}

		const T& operator[](size_t index) const {
			if (index >= capacity) { throw std::out_of_range("DA::Operator[]: index (" + std::to_string(index) + ") was greater or equal to array capacity (" + std::to_string(int(size)) + ")"); }
			
			return arr[index];
		}

		T& operator[](size_t index) {
			if (index >= capacity) { throw std::out_of_range("DA::Operator[]: index (" + std::to_string(index) + ") was greater or equal to array capacity (" + std::to_string(int(size)) + ")"); }

			return arr[index];
		}

		std::string ToString(unsigned int limit = 0, std::string(*cmp_string)(T) = nullptr) const {
			if (limit <= 0 || limit > size) {
				limit = size;
			}

			std::string text = "Dynamic Array:\n";
			text += "size: " + std::to_string(int(size)) + "\n";
			text += "capacity: " + std::to_string(int(capacity)) + "\n";
			text += "factor: " + std::to_string(int(FACTOR)) + "\n";
			text += "{\n";
			if (cmp_string) {
				for (int i = 0; i < limit; i++) {
					text += cmp_string(arr[i]);
					text += "\n";
				}
			}
			else if constexpr (std::is_arithmetic_v<T>) {
				for (int i = 0; i < limit; i++) {
					text += std::to_string(arr[i]);
					text += "\n";
				}
			}
			else {
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