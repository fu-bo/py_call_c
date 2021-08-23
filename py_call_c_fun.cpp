#ifndef PY_SSIZE_T_CLEAN
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#endif

#include <iostream>
#include <numpy/arrayobject.h>
#include <boost/python.hpp>

class PyCallCFun
{
private:
    /* data */
public:
    PyCallCFun(/* args */);
    ~PyCallCFun();
    PyObject* addMulMatrix(PyObject *matrixObj, PyObject *factor);
};

PyCallCFun::PyCallCFun(/* args */) {
}

PyCallCFun::~PyCallCFun() {
}

PyObject* PyCallCFun::addMulMatrix(PyObject *matrixObj, PyObject *factor) {
    PyArrayObject * matrixArray = reinterpret_cast<PyArrayObject *>(matrixObj);
    int matrixNDim = PyArray_NDIM(matrixArray);
    if (matrixNDim != 2) {
      throw std::runtime_error(
        "expecting a 2D array but got " + std::to_string(matrixNDim));
    }
    npy_intp* matrixSize = PyArray_DIMS(matrixArray);
    npy_intp matrixRows = matrixSize[0], matrixCols = matrixSize[1];
    void* matrixPtr = PyArray_DATA(matrixArray);
    int* intmatrixPtr = static_cast<int *>(matrixPtr);
    std::cout << "matrixRows = " << matrixRows << "\n";
    std::cout << "matrixCols = " << matrixCols << "\n";
    for (int iRow = 0; iRow < matrixRows; iRow++) {
        for (int iCol = 0; iCol < matrixCols; iCol++) {
            int temp = intmatrixPtr[iRow * matrixCols + iCol];
            std::cout << temp << "\t";
        }
        std::cout << "\n";
    }
    return matrixObj;
}


using namespace boost::python;
BOOST_PYTHON_MODULE(py_call_c_fun)
{
    class_ <PyCallCFun> (
    "py_call_c_fun").def(
    // "py_call_c_fun", init<std::string>()).def(
        "add_mul_matrix", &PyCallCFun::addMulMatrix
    );
}
