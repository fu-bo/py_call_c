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
    PyObject* addMulMatrix(PyObject *matrixObj, int factor);
};

PyCallCFun::PyCallCFun(/* args */) {
}

PyCallCFun::~PyCallCFun() {
}

PyObject* PyCallCFun::addMulMatrix(PyObject *matrixObj, int factor) {
    std::cout << "c++: factor = " << factor << "\n";
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
    std::cout << "c++: matrixRows = " << matrixRows << "\n";
    std::cout << "c++: matrixCols = " << matrixCols << "\n";
    for (int iRow = 0; iRow < matrixRows; iRow++) {
        for (int iCol = 0; iCol < matrixCols; iCol++) {
            int temp = intmatrixPtr[iRow * matrixCols + iCol];
            std::cout << temp << "\t";
        }
        std::cout << "\n";
    }

    // Py_Initialize();
    import_array();

    npy_intp inputSize[2];
    inputSize[0] = 2;
    inputSize[1] = 3;
    double inputData[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    PyObject* input = PyArray_SimpleNewFromData(2, inputSize, PyArray_FLOAT64, inputData);

    // Construct outputs
    int outputNumel = matrixRows * matrixCols;
    int* addMat = new int[outputNumel]; // int32_t
    int* mulMat = new int[outputNumel]; // int32_t
    for (int i = 0; i < outputNumel; i++) {
        addMat[i] = intmatrixPtr[i] + factor;
        mulMat[i] = intmatrixPtr[i] * factor;
    }
    std::cout << "outputNumel = " << outputNumel <<"\n";
    std::cout << "matrixSize[0] = " << matrixSize[0] <<"\n";
    std::cout << "matrixSize[1] = " << matrixSize[1] <<"\n";

    PyObject* addMatArray = PyArray_SimpleNewFromData(2, matrixSize, PyArray_INT32, addMat);
    PyObject* mulMatArray = PyArray_SimpleNewFromData(2, matrixSize, PyArray_INT32, mulMat);
    PyObject* outputTuple = PyTuple_New(2);
    int flagSuccess = 0;
    flagSuccess = PyTuple_SetItem(outputTuple, 0, addMatArray);
    flagSuccess = PyTuple_SetItem(outputTuple, 1, mulMatArray);

    // Should not do the follwing
    // delete[] addMat;
    // delete[] mulMat;
    return outputTuple;
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
