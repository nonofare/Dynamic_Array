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
				throw std::runtime_error("ExpandArray() -> " + std::string(ex.what()));
			}
			catch (const std::exception& ex) {
				delete[] new_arr;
				throw std::runtime_error("ExpandArray() -> " + std::string(ex.what()));
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
				throw std::runtime_error("ReduceArray() -> " + std::string(ex.what()));
			}
			catch (const std::exception& ex) {
				delete[] new_arr;
				throw std::runtime_error("ReduceArray() -> " + std::string(ex.what()));
			}
		}

		void TransferMainArray(T* in_arr, size_t in_capacity) {
			if (!in_arr) { throw std::invalid_argument("TransferMainArray() -> in_array was null"); }
			if (in_capacity < size) { throw std::length_error("TransferMainArray() -> in_capacity is smaller than the array size"); }

			for (int i = 0; i < size; i++) {
				in_arr[i] = arr[i];
			}
			
			delete[] arr;
			capacity = in_capacity;
			arr = in_arr;
		}

	public:
		DynArr() {
			size = 0;
			capacity = 1;
			try {
				arr = new T[capacity];
			}
			catch (const std::bad_alloc& ex) {
				throw std::runtime_error("Constructor -> " + std::string(ex.what()));
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

		void Push(T data) {
			if (size == capacity) {
				try {
					ExpandArray();
				}
				catch (const std::exception& ex) {
					throw std::runtime_error("Push() -> " + std::string(ex.what()));
				}
			}

			arr[size] = data;
			size++;
		}

		void Pop(size_t index = size - 1) {
			if (index >= size) { throw std::length_error("Pop() -> index is greater than array size"); }

			if (size == capacity / FACTOR) {
				try {
					ReduceArray();
				}
				catch (const std::exception& ex) {
					throw std::runtime_error("Pop() -> " + std::string(ex.what()));
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
				throw std::runtime_error("Erase() -> " + std::string(ex.what()));
			}
		}

		void Sort(bool(*cmp)(T, T)) {
			if (cmp) {
				for (int i = 0; i < size - 1; i++) {
					for (int j = 0; j < size - i - 1; j++) {
						if (cmp(arr[j], arr[j + 1])) {
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
				throw std::runtime_error("Sort() -> T is not arithmetic and no cmp was provided");
			}
		}

		const T& operator[](size_t index) const {
			if (index < 0 || index >= size) { throw std::out_of_range("Operator[] -> index is out of range"); }
			
			return arr[index];
		}

		T& operator[](size_t index) {
			if (index < 0 || index >= size) { throw std::out_of_range("Operator[] -> index is out of range\n"); }

			return arr[index];
		}

		std::string ToString(unsigned int limit = 0, std::string(*str)(T) = nullptr) const {
			if (limit <= 0 || limit > size) {
				limit = size;
			}

			std::string text = "Dynamic Array:\n";
			text += "size: " + std::to_string(int(size)) + "\n";
			text += "capacity: " + std::to_string(int(capacity)) + "\n";
			text += "factor: " + std::to_string(int(FACTOR)) + "\n";
			text += "{\n";
			if (str) {
				for (int i = 0; i < limit; i++) {
					text += str(arr[i]);
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