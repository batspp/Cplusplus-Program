// Joshua Battaglia
// 16OCT2022
// This program provides a logistics tool for corner grocer stores.

#include <string>
#include <Python.h>
#include <Windows.h>
#include <cmath>
#include <iostream>
#include <fstream>

using namespace std;

void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("CornerFunc");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

int callIntFunc(string proc, string param)
{
	char* procname = new char[param.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter.
	Py_Initialize();
	// Build the name object.
	pName = PyUnicode_FromString((char*)"CornerFunc");
	// Load the module object.
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference.
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference.
	pFunc = PyDict_GetItemString(pDict, procname);

	if (PyCallable_Check(pFunc)) {
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else {
		PyErr_Print();
	}
	// printf("Result is %d\n, _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up.
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter.
	Py_Finalize();

	// Clean.
	delete[] procname;
	delete[] paramval;

	return _PyLong_AsInt(presult);
}

int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter.
	Py_Initialize();
	// Build the name object.
	pName = PyUnicode_FromString((char*)"CornerFunc");
	// Load the module object.
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference.
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference.
	pFunc = PyDict_GetItemString(pDict, procname);

	if (PyCallable_Check(pFunc)) {
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else {
		PyErr_Print();
	}
	// printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up.
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter.
	Py_Finalize();

	// Clean.
	delete[] procname;

	return _PyLong_AsInt(presult);
}

// Read frequency.dat file created by python.
void gram() {
	ifstream ffile("frequency.dat");

	cout << endl << "            Item histogram" << endl << "=========================================" << endl;

	if (ffile.is_open()) {
		string mychar;

		while (ffile) {
			mychar = ffile.get();

			cout << mychar << callIntFunc("bar", mychar) << endl;
		}
	}
	else {
		cout << "file did not open" << endl;
	}
}

void main()
{
	bool loopVar = true;
	int userChoice;
	string product;

	while (loopVar)
	{
		// Main menu.
		cout << "1: List all items" << endl;
		cout << "2: Search number of sales" << endl;
		cout << "3: Print histogram" << endl;
		cout << "4: Exit" << endl;

		cin >> userChoice;

		// Confirms user input and prompt for selected functions to call from python.
		switch (userChoice)
		{
		case 1:   // Produced list of items from python.
			cout << endl << "          Item List          " << endl << "======================================" << endl;
			CallProcedure("numberList");
			break;

		case 2:   // Find frequency of item.
			cout << "Enter product name: " << endl;
			cin >> product;

			cout << endl << "          Frequency          " << endl;
			cout << "=============================" << endl;
			cout << "frequency: " << callIntFunc("productCount", product) << endl;
			cout << endl;
			break;

		case 3:   // Create histogram file and return graphic.
			cout << endl << "Creating \"frequency.dat\" file" << endl;
			CallProcedure("histogram");

			gram();

			break;

		case 4:   // Exit program.
			cout << endl << "Exiting..." << endl;
			loopVar = false;   // Exits the loop.
			break;

		// If input is invalid.
		default:
			cout << "Invalid input. Try again...";
			break;
		} // Loop restarts.
	}
}