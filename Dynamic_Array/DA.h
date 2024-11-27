#pragma once
#include <string>

namespace DA {

	template <typename T>
	class DynArr {
		const int FACTOR = 2;

		T* arr;
		size_t size;
		size_t capacity;

		bool ExpandArray() {
			size_t new_size = capacity * FACTOR;
			T* new_arr = nullptr;

			try {
				new_arr = new T[new_size];
			}
			catch (std::bad_alloc&) {
				return false;
			}

			if (TransferMainArray(new_arr, new_size)) {
				return true;
			}
			else {
				delete[] new_arr;
				return false;
			}
		}

		bool DecreaseArray() {
			size_t new_size = capacity / FACTOR;
			T* new_arr = nullptr;

			try {
				new_arr = new T[new_size];
			}
			catch (std::bad_alloc&) {
				return false;
			}

			if (TransferMainArray(new_arr, new_size)) {
				return true;
			}
			else {
				delete[] new_arr;
				return false;
			}
		}

		bool TransferMainArray(T* in_arr, size_t in_size) {
			if (!in_arr || in_size < size) {
				return false;
			}

			for (int i = 0; i < size; i++) {
				in_arr[i] = arr[i];
			}

			RemoveArray(arr);

			capacity = in_size;
			arr = in_arr;

			return true;
		}

		bool RemoveArray(T* in_arr) {
			if (!in_arr) {
				return false;
			}

			delete[] in_arr;
			in_arr = nullptr;

			return true;
		}

	public:
		DynArr() {
			size = 0;
			capacity = 1;
			arr = new T[capacity];
		}

		~DynArr() {
			RemoveArray(arr);
		}

		size_t Size() const {
			return size;
		}

		size_t Capacity() const {
			return capacity;
		}

		bool IsEmpty() const {
			return size == 0;
		}

		bool Push(T data) {
			if (size == capacity) {
				if (!ExpandArray()) {
					return false;
				}
			}

			arr[size] = data;
			size++;

			return true;
		}

		bool Pop(size_t index = size - 1) {
			if (size == 0 || index >= size) {
				return false;
			}

			if (size == capacity / FACTOR) {
				if (!DecreaseArray()) {
					return false;
				}
			}

			for (size_t i = index; i < size - 1; i++) {
				arr[i] = arr[i + 1];
			}
			size--;

			return true;
		}

		bool Erase() {
			if (!RemoveArray(arr)) {
				return false;
			}

			size = 0;
			capacity = 1;
			arr = new T[capacity];

			return true;
		}

		bool Sort(bool(*cmp)(T, T)) {
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
				return false;
			}

			return true;
		}

		const T& operator[](size_t index) const {
			if (index < 0 || index >= size) {
				throw std::out_of_range("Index is out of range");
			}
			else {
				return arr[index];
			}
		}

		T& operator[](size_t index) {
			if (index < 0 || index >= size) {
				throw std::out_of_range("Index is out of range");
			}
			else {
				return arr[index];
			}
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
				text = "Data type is not supported and no method was provided\n";
			}

			if (limit < size) {
				text += "[...]\n";
			}

			text += "}\n";

			return text;
		}
	};
}