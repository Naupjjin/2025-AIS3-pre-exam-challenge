#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Python.h>

char blacklist[0x5E] = {
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
    0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
    0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
    0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
    0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E
};

int is_blacklisted(char c) {
    for (int i = 0; i < 0x5E; i++) {
        if (c == blacklist[i]) {
            return 1;
        }
    }
    return 0; 
}

int filter(const char *input_str) {
    int size = strlen(input_str);
    char *str = (char *)malloc(size + 1);
    if (str == NULL) {
        return 0; 
    }

    strcpy(str, input_str);

    for (int i = 0; i < size; i++) {
        if (is_blacklisted(str[i])) {
            free(str);
            return 0; 
        }
    }
    free(str);
    return 1; 
}

static PyObject* py_filter(PyObject* self, PyObject* args) {
    PyObject* input_obj;

    if (!PyArg_ParseTuple(args, "S", &input_obj)) {
        return NULL;
    }

    const char* input_str = PyBytes_AsString(input_obj);
    if (input_str == NULL) {
        return NULL; 
    }

    int result = filter(input_str);
    return PyLong_FromLong(result);
}

static PyMethodDef filter_methods[] = {
    {"check_filter", py_filter, METH_VARARGS, "Check if the string is valid based on the blacklist."},
    {NULL, NULL, 0, NULL} 
};

static struct PyModuleDef filter_module = {
    PyModuleDef_HEAD_INIT,
    "filter",  
    "A module to filter strings based on blacklist.",  
    -1,  
    filter_methods
};

PyMODINIT_FUNC PyInit_filter(void) {
    return PyModule_Create(&filter_module);
}
