cmake_minimum_required(VERSION 3.3)

project(py_call_c)

option(CXX "enable C++ compilation" ON)
if(CXX)
    enable_language(CXX)
endif()

set(CMAKE_CXX_STANDARD 11)

find_package(Python COMPONENTS Interpreter NumPy)
find_package(Boost REQUIRED COMPONENTS python)
include(FindPythonLibs)

include_directories(
    ${PYTHON_INCLUDE_DIRS}
  )
message("${PYTHON_INCLUDE_DIRS} and ${PYTHON_NUMPY_INCLUDE_DIRS}")

set(CMAKE_SHARED_MODULE_PREFIX "")

add_library(py_call_c_fun MODULE py_call_c_fun.cpp)
target_link_libraries(py_call_c_fun ${Boost_LIBRARIES} ${PYTHON_LIBRARIES} Python::NumPy)
target_include_directories(py_call_c_fun PRIVATE ${PYTHON_INCLUDE_DIRS})
