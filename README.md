# Python Call C++
An example of calling a C++ function from Python

## Build
```bash
mkdir build
cd build
cmake ..
make
```

## Run
To call a C++ funtion from Python, run the following from the main folder.
```bash
python py_call_c_main.py
```
## References
[A Simple Boost-python CMakeLists.txt](https://gist.github.com/ndevenish/ff771feb6817f7debfa728386110f567#file-readme-md)

[Call C++ from Python using the cdll library](https://www.geeksforgeeks.org/how-to-call-c-c-from-python/)

[Boost-python Tuple Objects](https://docs.python.org/3/c-api/tuple.html)
