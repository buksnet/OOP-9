#include <iostream>
#include "List.h"
#include "ListExceptions.h"
using namespace std;


int main()
{
	try {
		int count, in_value, index;
		List<int> list1;
		Iter<int> iter;

		cout << "Enter quantity of elements: ";
		cin >> count;
		cout << endl;

		cout << "Enter elements:" << endl;
		for (int i = 0; i < count; ++i)
		{
			cin >> in_value;
			list1.push(in_value);
		}
		cout << endl;
		iter = list1.first();

		cout << "Enter element's index: ";
		cin >> index;
		cout << list1[index] << endl;
		cout << endl;

		cout << "Enter number to move for from first element: ";
		cin >> index;
		iter + index;
		cout << *iter << endl;
		cout << endl;
	}
	catch (BaseException &e) {
		e.what();
	}
	return 0;
}