#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include <time.h>
#include "DA.h"

using namespace std;
using namespace DA;

struct some_object {
	int field_1;
	char field_2;
};

std::string some_objects_str(some_object* so) {
	std::string text = "(" + std::to_string(so->field_1) + ", " + so->field_2 + ")\n";
	return text;
}

bool some_objects_cmp1(some_object* so1, some_object* so2) {
	return so1->field_1 == so2->field_1;
}

bool some_objects_cmp2(some_object* so1, some_object* so2) {
	return so1->field_1 >= so2->field_1;
}

int main()
{
	const int MAX_ORDER = 7;
	const int n = pow(10, MAX_ORDER);
	
	DynArr <some_object*>* da = new DynArr <some_object*>();

	// Pushing
	cout << "Starting the element pushing phase" << endl;
	double max_time_per_element = 0.0;
	clock_t t1 = clock();
	for (int i = 0; i < n; i++) {
		some_object* so = new some_object();
		so->field_1 = rand() % 100;
		so->field_2 = 'A' + rand() % 26;

		clock_t t2_element_start = clock();
		da->push(so);
		clock_t t2_element_end = clock();

		double time_per_element = double(t2_element_end - t2_element_start) / CLOCKS_PER_SEC;
		if (time_per_element > max_time_per_element) {
			max_time_per_element = time_per_element;
			cout << "New worst push time: " << max_time_per_element << "s, at index: " << i << endl;
		}
	}
	clock_t t2 = clock();
	cout << "Element pushing phase done" << endl;

	double pushing_time = double(t2 - t1) / CLOCKS_PER_SEC;
	double amortized_time = pushing_time / n;
	cout << da->to_str(some_objects_str, 10);
	cout << "Average time for element (amortized): " << amortized_time << "s" << endl;
	cout << "Pushing time: " << pushing_time << "s" << endl << endl;

	// Sorting
	cout << "Starting the element sorting phase" << endl;
	clock_t t3 = clock();
	da->sort(some_objects_cmp2);
	clock_t t4 = clock();
	cout << "Element sorting phase done" << endl;

	cout << da->to_str(some_objects_str, 10);
	double sorting_time = (double(t4 - t3) / CLOCKS_PER_SEC) - pushing_time;
	cout << "Sorting time: " << sorting_time << "s" << endl << endl;

	// Poping
	cout << "Starting the element poping phase" << endl;
	clock_t t5 = clock();
	da->erase();
	clock_t t6 = clock();
	cout << "Element poping phase done" << endl;

	cout << da->to_str(some_objects_str, 10);
	double poping_time = (double(t6 - t5) / CLOCKS_PER_SEC) - (pushing_time + sorting_time);
	cout << "Poping time: " << sorting_time << "s" << endl << endl;

	cout << "Total time: " << pushing_time + sorting_time + sorting_time << "s";

	delete da;
	return 0;
}