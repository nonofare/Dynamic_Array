# Dynamic Array Implementation in C++

This project provides a C++ implementation of a Dynamic Array data structure. The implementation is templated, allowing
it to store any data type. The dynamic array supports common operations such as insertion, deletion and indexing.

## Table of Contents

- [Features](#features)
- [API Documentation](#api-documentation)
- [Example Usage](#example-usage)
- [Installation](#installation)
- [Contributing](#contributing)
- [License](#license)

## Features

- **Templated Implementation:** Works with any data type.

- **Automatic Resizing:**

    - Expands when full.
    - Reduces capacity when underutilized.

- **Common Operations:**

    - Insert elements at the end (`push`).

    - Remove elements by index (`pop`).

    - Clear all elements (`clear`).

- **Indexing:** Access elements using the `[]` operator.

- **String Representation:** Convert the list to a string for a easy visualization.

- **Memory Management:** Automatically deallocates memory when array is destroyed.

## API Documentation

### Class: `DynArr<T>`

#### Template Parameters:

- `T`: The type of data stored in the array.

### Public Methods

#### Constructors:

- `DynArr(size_t capacity = 1, size_t FACTOR = 2)`: Creates a dynamic array with an initial capacity and expansion
  factor.
- `DynArr(const DynArr &other)`: Copy constructor that creates a deep copy of another DynArr instance.

#### Assignment Operator:

- `DynArr &operator=(DynArr other)`: Assignment operator using copy-and-swap idiom.

#### Destructor:

- `~DynArr()`: Automatically deallocates memory when the object is destroyed.

#### Insertion:

- `void push(T data)`: Inserts `data` at the end of the array, expanding if needed.

#### Deletion:

- `bool pop(size_t index)`: Removes the element at 'index' and shifts remaining elements. Reduces capacity when
  necessary.
- `void clear()`: Removes all elements and resets capacity.

#### Accessors:

- `size_t get_size() const`: Returns the current number of elements.
- `size_t get_capacity() const`: Returns the current capacity.
- `size_t get_factor() const`: Returns the resizing factor.

#### Indexing:

- `T& operator[](size_t index)`: Returns the element at index with bounds checking.
- `const T& operator[](size_t index) const`: Const version of the above.

#### Utility:

- `std::string to_str(unsigned int limit = 0, std::string (*fun_str)(T) = nullptr) const`: Converts array to a
  string representation.

## Example Usage

```cpp
#include <iostream>
#include "DH.h"

int main() {
    DA::DynArr<int> arr;
    
    arr.push(10);
    arr.push(20);
    arr.push(30);
    std::cout << arr.to_str() << std::endl;
    
    arr.pop(1);
    std::cout << arr.to_str() << std::endl;
    
    std::cout << std::to_string(arr[0]) << std::endl;
    
    return 0;
}
```

## Installation

1. **Clone the repository:**
   ```bash
   git clone https://github.com/nonofare/Dynamic_Array.git
   ```

2. **Include the `DA.h` file in your project.**

3. **Compile your project with a compiler that supports C++17 or later.**

## Contributing

Please open an issue or submit a pull request for any improvements or bug fixes.

## License

This project is licensed under the MIT License. See the LICENSE file for details.