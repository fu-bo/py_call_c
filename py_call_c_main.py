import numpy as np
import sys
sys.path.insert(1, './build/')
from py_call_c_fun import py_call_c_fun

mat = np.arange(6).reshape(2,3).astype(np.int32)
factor = 5
temp_var = py_call_c_fun()
new_mat = temp_var.add_mul_matrix(mat, factor)
print('new_mat = ', new_mat)
