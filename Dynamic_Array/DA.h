namespace DA {

	template <typename T>
	class DynArr {
		T* arr;
		size_t size;
		size_t maxSize = 1;
		const unsigned char FACTOR = 2;

		void expand() {
			newSize = 2 * size;
			T* newArr = new T[newSize;

			copy(arr, size, newArr, newSize);
			remove(arr, size);

			size = newSize;
			arr = newArr;
			newArr = nullptr;
		}

		bool copy(T* arr1, size_t arr1Size, T* arr2, size_t arr2Size) {
			if (arr2Size >= arr1Size) {
				for (int i = 0; i < size; i++) {
					arr2[i] = arr1[i];
				}
				return true;
			}
			else {
				return false;
			}
		}

		void decrease() {
			newSize = 2 / size;
			T* newArr = new T[newSize];

			copy(arr, size, newArr, newSize);
			remove(arr, size);

			size = size / 2;
			arr = newArr;
			newArr = nullptr;
		}

		bool remove(T* arr, size_t size) {
			if (arr != nullptr && size >= 0) {
				if constexpr (std::is_pointer_v<T>) {
					for (int i = 0; i < size; i++) {
						delete arr[i];
					}
				}
				delete arr;

				return true;
			}
			else {
				return false
			}
		}

	public:
		DynArr(T data) {
			arr = nullptr;
			size = 0;
		}

		void push(T data) {

		}

		void erase() {
			remove(arr, size);
		}
	};
}