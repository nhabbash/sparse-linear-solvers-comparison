import sys
import os
import time
import platform
from datetime import datetime

import numpy as np
import scipy as sp
import scipy.io as io
from sksparse.cholmod import cholesky

mat_path = sys.argv[1]
if (not mat_path):
    sys.exit(0)

res_path = "../res/matrices/"
_, mat_name = os.path.split(mat_path)

mat = io.mmread(mat_path)

A = sp.sparse.csc_matrix(mat)
n = A.shape

xe = np.ones(n[0])
b = A.dot(xe)

# Cholesky factorization
factorization_time = time.process_time()
factor = cholesky(A)
factorization_time = time.process_time() - factorization_time

resolution_time = time.process_time()
x = factor.solve_A(b)
resolution_time = time.process_time() - resolution_time

rel_error = np.linalg.norm(x-xe)/np.linalg.norm(xe)

# Writing logfile

data_file = "data/data.csv"
date = datetime.now().strftime('%d-%m-%Y %H:%M:%S')
platform = platform.system()
name, _ = os.path.splitext(mat_name)


#["date", "platform", "name", "library", "factorization time", "resolution time", "relative error", "physical memory", "virtual memory"]

with open(data_file, "a") as logfile:
        logfile.write(
                    date + ", " + 
                    platform + ", " + 
                    name + ", " + 
                    "scikit-sparse, " + 
                    str(factorization_time)  + ", " + 
                    str(resolution_time) + ", " +
                    str(rel_error) + ", ")

