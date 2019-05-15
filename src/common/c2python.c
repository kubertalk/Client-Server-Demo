#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include "socket_control.h"
/*Python version: cpython 3.7.0
vs	   version: vs2017       */


int main() {
	//initilize the python environment
	PyObject * pModule = NULL;
	PyObject * pFunc = NULL;
	Py_Initialize();
	//add python file path
	PyRun_SimpleString("import sys;sys.path.append('./')");
	//import module
	pModule = PyImport_ImportModule("hello");
	if (pModule == NULL) {
		printf("pModule null...\n"); system("pause"); return 0;
	}
	//get the specific function
	pFunc = PyObject_GetAttrString(pModule, "printmain");
	if (pFunc == NULL) {
		printf("pFunc null...\n"); system("pause"); return 0;
	}
	//call the specific function
	PyEval_CallObject(pFunc, NULL);
	//release the python environment
	Py_Finalize();
	system("pause");
	return 0;
}
