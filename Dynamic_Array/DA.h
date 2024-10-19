#include <string>

namespace DA {

	template <typename T>
	class DynArr {
		T* arr;
		size_t size;
		size_t capacity;
		const double FACTOR = 2;

		bool expand() {
			size_t newSize = capacity * FACTOR;
			T* newArr = nullptr;

			try {
				newArr = new T[newSize];
			}
			catch (std::bad_alloc&) {
				return false;
			}

			if (copy(newArr, newSize)) {
				remove(arr, size);
				capacity = newSize;
				arr = newArr;

				return true;
			}
			else {
				delete[] newArr;

				return false;
			}
		}

		bool copy(T* extArr, size_t extSize) {
			if (extSize < size) {
				return false;
			}

			for (int i = 0; i < size; i++) {
				extArr[i] = arr[i];
			}

			return true;
		}

		bool decrease() {
			size_t newSize = capacity / FACTOR;
			T* newArr = nullptr;

			try {
				newArr = new T[newSize];
			}
			catch (std::bad_alloc&) {
				return false;
			}

			if (copy(newArr, newSize)) {
				remove(arr, size);
				capacity = newSize;
				arr = newArr;

				return true;
			}
			else {
				delete[] newArr;

				return false;
			}
		}

		bool remove(T* extArr, size_t extSize) {
			if (extArr == nullptr) {
				return false;
			}
			/*
			if constexpr (std::is_pointer_v<T>) {
				for (int i = 0; i < extSize; i++) {
					delete extArr[i];
				}
			}
			*/
			delete[] arr;
			arr = nullptr;

			return true;
		}

	public:
		DynArr() {
			capacity = 1;
			arr = new T[capacity];
			size = 0;
		}

		~DynArr() {
			remove(arr, size);
		}

		// Method purpose: Returns the number of elements in the array
		// Arguments: None
		// Returns: Size of the array
		// Time complexity: Theta(1)
		size_t get_size() const {
			return size;
		}

		// Method purpose: Checks if the array is empty
		// Arguments: None
		// Returns: True if the array is empty, false otherwise
		// Time complexity: Theta(1)
		bool is_empty() const {
			return size == 0;
		}

		// Method purpose: Adds a new element to the end of the array
		// Arguments: Data(T) of a new element
		// Returns: Void
		// Time complexity: Theta(n) if expansion is required, Theta(1) otherwise
		void push(T data) {
			if (size == capacity) {
				expand();
			}
			arr[size] = data;
			size++;
		}

		// Method purpose: Removes an element at the specified index
		// Arguments: Index of the element
		// Returns: Void
		// Time complexity: Theta(n)
		void pop(size_t index = size - 1) {
			if (size == 0 || index >= size) {
				throw std::out_of_range("Index is out of range");
			}

			if (size == capacity / FACTOR) {
				decrease();
			}

			for (size_t i = index; i < size - 1; i++) {
				arr[i] = arr[i + 1];
			}
			size--;
		}

		// Method purpose: Get access to an element by index (read-only)
		// Arguments: Index of a wanted element
		// Returns: Const reference to the element
		// Time complexity: Theta(1)
		const T& operator[](size_t index) const {
			if (index >= size) {
				throw std::out_of_range("Index is out of range");
			}
			else {
				return arr[index];
			}
		}

		// Method purpose: Get access to an element by index
		// Arguments: Index of a wanted element
		// Returns: Reference to the element
		// Time complexity: Theta(1)
		T& operator[](size_t index) {
			if (index >= size) {
				throw std::out_of_range("Index is out of range");
			}
			else {
				return arr[index];
			}
		}

		// Method purpose: Delete all array elements
		// Arguments: None
		// Returns: Void
		// Time complexity: Theta(n) if T is pointer type, Theta(1) otherwise
		void erase() {
			remove(arr, size);
			size = 0;
			capacity = 1;
		}

		// Method purpose: Get string representation of the array
		// Arguments: Specific to_string function if needed, number of elements to show
		// Returns: String representation of the array
		// Time complexity: Theta(n)
		std::string to_str(std::string(*out_to_string)(T) = nullptr, size_t element_count = 0) {
			std::string text;

			if (element_count <= 0 || element_count > size) {
				element_count = size;
			}

			text = "Array has " + std::to_string(int(size)) + " elements:\n";
			if (out_to_string != nullptr) {
				for (int i = 0; i < element_count; i++) {
					text += out_to_string(arr[i]);
				}
			}
			else if constexpr (std::is_arithmetic_v<T>) {
				for (int i = 0; i < element_count; i++) {
					text += std::to_string(arr[i]);
				}
			}
			else {
				text = "Data type is not supported and no method was provided";
			}

			if (element_count < size) {
				text += "[...]\n";
			}

			return text;
		}

		// Method purpose: Sort array elements
		// Arguments: Custom comparator if needed (< operation is default)
		// Returns: Void
		// Time complexity: O(n^2)
		void sort(bool(*cmp)(T, T)) {
			if (cmp != nullptr) {
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
			else {
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
		}
	};
}