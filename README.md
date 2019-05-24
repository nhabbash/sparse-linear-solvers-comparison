# Sparse Linear Systems Solvers Comparison Tests
> Comparison tests for the Cholesky method for the resolution of sparse linear systems of equations between MATLAB, Sci-Kit, and Eigen's libraries on Linux and Windows

Project for the *Methods of Scientific Computing* course for the MSc in Computer Science at University of Milano-Bicocca.

## Brief

The project aims to compare the performance of MATLAB against Eigen and Sci-Kit's Cholesky factorization and sparse linear system solvers.

## Prerequisites

The following sparse matrices from `https://sparse.tamu.edu/` have to be downloaded inside `res/matrices`, in the `mtx` and `mat` formats. Only the `ex15` matrix is provided with the project. 

* Flan 1565
* StocF-1465
* cfd2
* cfd1
* G3 circuit
* parabolic fem
* apache2
* shallow water1
* ex15

### Prerequisites for Python
* NumPy
* SciPy
* SciKit-Sparse (SuiteSparse, CHOLMOD)

### Prerequisites for C++
* Eigen
* Eigen unsupported modules (SparseExtra)
Both Eigen and its unsupported modules are already included in the project under `c++/lib`

#
## Installation

### Linux

```sh
$ git clone https://github.com/Dodicin/slss-comparison-test
$ cd slss-comparison-test

# Setting up Python VirtualEnv
$ virtualenv .venv
$ source .venv/bin/activate
$ pip install numpy
$ pip install scipy
$ pip install scikit-sparse

# Compiling C++
$ cd c++
$ g++ -Ilib -std=gnu++17 main.cpp -lstdc++fs -o main.exe
$ cd ..

# Executing batch file
$ python batch.py

```

### Windows

```sh
#TODO
```

## Metrics

Metrics are saved under `./data/data.csv`, in the following format:

* Date
* Platform: Windows/Linux
* Matrix name
* Library: Scikit-Sparse/Eigen/MATLAB
* Factorization time (fractional seconds)
* Resolution time (fractional seconds)
* Relative error
* Physical memory (bytes)
* Virtual memory (bytes)

## Authors

* **Marco Ferri** (807130)
* **Nassim Habbash** (808292) - [dodicin](https://github.com/dodicin)

<!-- Markdown link & img dfn's -->
[npm-image]: https://img.shields.io/npm/v/datadog-metrics.svg?style=flat-square
[npm-url]: https://npmjs.org/package/datadog-metrics
[npm-downloads]: https://img.shields.io/npm/dm/datadog-metrics.svg?style=flat-square
[travis-image]: https://img.shields.io/travis/dbader/node-datadog-metrics/master.svg?style=flat-square
[travis-url]: https://travis-ci.org/dbader/node-datadog-metrics
[wiki]: https://github.com/yourname/yourproject/wiki