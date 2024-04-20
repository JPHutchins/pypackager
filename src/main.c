#define PY_SSIZE_T_CLEAN
#include <Python.h>

int main(int const argc, char const * const argv[argc]) {
    wchar_t * const program = Py_DecodeLocale(argv[0], NULL);
    if (program == NULL) {
        fprintf(stderr, "Fatal error: cannot decode argv[0] %s\n", argv[0]);
        exit(1);
    }

    Py_SetProgramName(program);  /* optional but recommended */

    Py_Initialize();

    PyObject * const sys_module = PyImport_ImportModule("sys");
    if (sys_module == NULL) {
        PyErr_Print();
        exit(2);
    }

    PyObject * const sys_path = PyObject_GetAttrString(sys_module, "path");
    if (sys_path == NULL) {
        PyErr_Print();
        exit(3);
    }

    if (PyList_Append(sys_path, PyUnicode_DecodeFSDefault(".")) < 0) {
        PyErr_Print();
        exit(4);
    }
    if (PyList_Append(sys_path, PyUnicode_DecodeFSDefault(".venv/lib/python3.10/site-packages")) < 0) {
        PyErr_Print();
        exit(5);
    }

    wchar_t * wchar_argv[64];
    for (int i = 0; i < argc; ++i) {
        wchar_argv[i] = Py_DecodeLocale(argv[i], NULL);
        if (wchar_argv[i] == NULL) {
            fprintf(stderr, "Fatal error: cannot decode argv[%d] %s\n", i, argv[i]);
            exit(1);
        }
    }

    PySys_SetArgv(argc, wchar_argv);

    FILE * fp = fopen(PYTHON_FILE_PATH, "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to open file\n");
        exit(6);
    }

    PyRun_SimpleFile(fp, PYTHON_FILE_PATH);
    fclose(fp);
    
    if (Py_FinalizeEx() < 0) {
        exit(120);
    }
    PyMem_RawFree(program);
    for (int i = 0; i < argc; ++i) {
        PyMem_RawFree(wchar_argv[i]);
    }
    return 0;
}
