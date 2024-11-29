#include <iostream>
#include <random>
#include <chrono>
#include "DA.h"

struct some_object {
	int field_1;
	char field_2;
};

std::string some_objects_str(some_object* so) {
	return "(" + std::to_string(so->field_1) + ", " + so->field_2 + ")";
}

bool some_objects_cmp(some_object* so1, some_object* so2) {
	return so1->field_1 > so2->field_1;
}

int main()
{
	const int MAX_ORDER = 6;
	const int LETTES_SIZE = 26;
	const char LETTERS[LETTES_SIZE] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

	static std::random_device rd;
	static std::default_random_engine dre(rd());
	std::uniform_int_distribution<int> rnd_num(0, MAX_ORDER * 1000);
	std::uniform_int_distribution<int> rnd_let(0, LETTES_SIZE - 1);
	
	DA::DynArr<some_object*>* da = new DA::DynArr<some_object*>();

	std::cout << "--------------------------------" << std::endl;
	std::cout << "Pushing phase: " << std::endl;

	int n = pow(10, MAX_ORDER);
	double max_time_per_element = 0.0;

	std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < n; i++) {
		some_object* so = new some_object();
		so->field_1 = rnd_num(dre);
		so->field_2 = LETTERS[rnd_let(dre)];

		std::chrono::high_resolution_clock::time_point element_start_time = std::chrono::high_resolution_clock::now();
		try {
			da->Push(so);
		}
		catch (const std::exception& ex) {
			std::cout << ex.what() << std::endl;
		}
		std::chrono::high_resolution_clock::time_point element_end_time = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double> time_per_element = element_end_time - element_start_time;
		if (time_per_element.count() > max_time_per_element) {
			max_time_per_element = time_per_element.count();
			std::cout << "New worst push time: " << max_time_per_element << "s, at index: " << i << std::endl;
		}
	}
	std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> pushing_time = end_time - start_time;
	std::cout << "Amortized average time for element: " << (pushing_time.count() / n) << "s" << std::endl;
	std::cout << "Time: " << pushing_time.count() << "s" << std::endl << std::endl;
	std::cout << da->ToString(10, some_objects_str);

	std::cout << "--------------------------------" << std::endl;
	std::cout << "Sorting phase: " << std::endl;

	start_time = std::chrono::high_resolution_clock::now();
	try {
		da->Sort(some_objects_cmp);
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
	end_time = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> sorting_time = end_time - start_time;
	std::cout << "Time: " << sorting_time.count() << "s" << std::endl << std::endl;
	std::cout << da->ToString(10, some_objects_str);

	std::cout << "--------------------------------" << std::endl;
	std::cout << "Removing phase: " << std::endl;

	start_time = std::chrono::high_resolution_clock::now();
	try {
		da->Erase();
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
	end_time = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> removing_time = end_time - start_time;
	std::cout << "Time: " << removing_time.count() << "s" << std::endl << std::endl;
	std::cout << da->ToString(10, some_objects_str);

	std::cout << "--------------------------------" << std::endl;
	std::cout << "Summary: " << std::endl;

	double total_time = pushing_time.count() + sorting_time.count() + removing_time.count();
	std::cout << "Total time: " << total_time << "s";

	delete da;
	return 0;
}