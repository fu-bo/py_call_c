import numpy as np
import sys
sys.path.insert(1, './build/')
from py_call_c_fun import py_call_c_fun, fcn_add_mul_matrix, fcn_print_string

mat = np.arange(6).reshape(2,3).astype(np.int32)

print('\n\nCall class:')
factor = 5
temp_var = py_call_c_fun()
add_mat, mul_mat = temp_var.add_mul_matrix(mat, factor)
print('py: add_mat = ', add_mat, add_mat.dtype)
print('py: mul_mat = ', mul_mat, mul_mat.dtype)

print('\n\nCall function:')
factor = 10
add_mat, mul_mat = fcn_add_mul_matrix(mat, factor)
print('py: add_mat = ', add_mat, add_mat.dtype)
print('py: mul_mat = ', mul_mat, mul_mat.dtype)

print('\n\nPrint a string in cpp:')
temp_str = 'Good!'
print('py: string -', temp_str)
flag_string = fcn_print_string(temp_str)
print('py: flag_string = ', flag_string)

