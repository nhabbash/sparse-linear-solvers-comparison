import numpy as np
import scipy.io as io
from sksparse.cholmod import cholesky

mat = io.loadmat("../res/matrices/ex15.mat")

A = mat["Problem"]["A"][0][0]
n = A.shape

xe = np.ones(n[0])
b = A.dot(xe)

# Cholesky factorization
factor = cholesky(A)

x = factor.solve_A(b)

rel_error = np.linalg.norm(x-xe)/np.linalg.norm(xe)

print(rel_error)