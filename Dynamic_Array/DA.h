#pragma once
#include <string>

namespace DA {

	template <typename T>
	class DynArr {
		const int FACTOR = 2;

		T* arr_MAIN;
		size_t size_MAIN;
		size_t capacity_MAIN;

		bool ExpandArray() {
			size_t size = capacity_MAIN * FACTOR;
			T* arr = nullptr;

			try {
				arr = new T[size];
			}
			catch (std::bad_alloc&) {
				return false;
			}

			if (TransferMainArray(arr, size)) {
				return true;
			}
			else {
				delete[] arr;
				return false;
			}
		}

		bool DecreaseArray() {
			size_t size = capacity_MAIN / FACTOR;
			T* arr = nullptr;

			try {
				arr = new T[size];
			}
			catch (std::bad_alloc&) {
				return false;
			}

			if (TransferMainArray(arr, size)) {
				return true;
			}
			else {
				delete[] arr;
				return false;
			}
		}

		bool TransferMainArray(T* arr, size_t size) {
			if (!arr || size < size_MAIN) {
				return false;
			}

			if constexpr (std::is_pointer_v<T>) {
				for (int i = 0; i < size_MAIN; i++) {
					arr[i] = arr_MAIN[i];
					arr_MAIN[i] = nullptr;
				}
			}
			else {
				for (int i = 0; i < size_MAIN; i++) {
					arr[i] = arr_MAIN[i];
				}

				RemoveArray(arr_MAIN, size_MAIN);
			}

			capacity_MAIN = size;
			arr_MAIN = arr;

			return true;
		}

		bool RemoveArray(T* arr, size_t size) {
			if (!arr || size < 0) {
				return false;
			}

			if constexpr (std::is_pointer_v<T>) {
				for (int i = 0; i < size; i++) {
					delete arr[i];
				}
			}

			delete[] arr;
			arr = nullptr;

			return true;
		}

	public:
		DynArr() {
			size_MAIN = 0;
			capacity_MAIN = 1;
			arr_MAIN = new T[capacity_MAIN];
		}

		~DynArr() {
			RemoveArray(arr_MAIN, size_MAIN);
		}

		size_t Size() const {
			return size_MAIN;
		}

		bool IsEmpty() const {
			return size_MAIN == 0;
		}

		bool Push(T data) {
			if (size_MAIN == capacity_MAIN) {
				if (!ExpandArray()) {
					return false;
				}
			}

			arr_MAIN[size_MAIN] = data;
			size_MAIN++;

			return true;
		}

		bool Pop(size_t index = size_MAIN - 1) {
			if (size_MAIN == 0 || index >= size_MAIN) {
				return false;
			}

			if (size_MAIN == capacity_MAIN / FACTOR) {
				if (!DecreaseArray()) {
					return false;
				}
			}

			for (size_t i = index; i < size_MAIN - 1; i++) {
				arr_MAIN[i] = arr_MAIN[i + 1];
			}
			size_MAIN--;

			return true;
		}

		void Erase() {
			RemoveArray(arr_MAIN, size_MAIN);
			size_MAIN = 0;
			capacity_MAIN = 1;
			arr_MAIN = new T[capacity_MAIN];
		}

		bool Sort(bool(*cmp)(T, T)) {
			if (cmp) {
				for (int i = 0; i < size_MAIN - 1; i++) {
					for (int j = 0; j < size_MAIN - i - 1; j++) {
						if (cmp(arr_MAIN[j], arr_MAIN[j + 1])) {
							T temp = arr_MAIN[j];
							arr_MAIN[j] = arr_MAIN[j + 1];
							arr_MAIN[j + 1] = temp;
						}
					}
				}
			}
			else if constexpr (std::is_arithmetic_v<T>) {
				for (int i = 0; i < size_MAIN - 1; i++) {
					for (int j = 0; j < size_MAIN - i - 1; j++) {
						if (arr_MAIN[j] > arr_MAIN[j + 1]) {
							T temp = arr_MAIN[j];
							arr_MAIN[j] = arr_MAIN[j + 1];
							arr_MAIN[j + 1] = temp;
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
			if (index < 0 || index >= size_MAIN) {
				throw std::out_of_range("Index is out of range");
			}
			else {
				return arr_MAIN[index];
			}
		}

		T& operator[](size_t index) {
			if (index < 0 || index >= size_MAIN) {
				throw std::out_of_range("Index is out of range");
			}
			else {
				return arr_MAIN[index];
			}
		}

		std::string ToString(unsigned int limit = 0, std::string(*str)(T) = nullptr) const {
			if (limit <= 0 || limit > size_MAIN) {
				limit = size_MAIN;
			}

			std::string text = "Dynamic Array:\n";
			text += "Size: " + std::to_string(int(size_MAIN)) + "\n";
			text += "Capacity: " + std::to_string(int(capacity_MAIN)) + "\n";
			text += "Factor: " + std::to_string(int(FACTOR)) + "\n";
			text += "{\n";
			if (str) {
				for (int i = 0; i < limit; i++) {
					text += str(arr_MAIN[i]);
					text += "\n";
				}
			}
			else if constexpr (std::is_arithmetic_v<T>) {
				for (int i = 0; i < limit; i++) {
					text += std::to_string(arr_MAIN[i]);
					text += "\n";
				}
			}
			else {
				text = "Data type is not supported and no method was provided\n";
			}

			if (limit < size_MAIN) {
				text += "[...]\n";
			}

			text += "}\n";

			return text;
		}
	};
}