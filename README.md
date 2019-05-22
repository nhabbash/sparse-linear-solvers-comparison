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

## Installation

```sh
$ git clone https://github.com/Dodicin/slss-comparison-test
$ cd slss-comparison-test
```

### For Python
```sh
$ virtualenv .venv
$ source .venv/bin/activate
$ pip install numpy
$ pip install scipy
$ pip install scikit-sparse
$ python python/main.py res/matrices/ex15.mtx
```

### For C++
```sh
$ cd c++
$ g++ -Ilib -std=gnu++17 main.cpp -lstdc++fs -o main.exe
$ cd ..
$ ./c++/main.exe res/matrices/ex15.mtx
```

### For MATLAB
```sh
$ matlab -nojvm -nodisplay -nosplash -nodesktop -r "try;cd matlab;main('../res/matrices/ex15.mat');catch;end;quit;"
```

## Metrics

Metrics are saved under `./log`, in the following format:

* Logfile: [Matrix name]-[Program]-[Platform].log, for example: `ex15.mtx-cpp-Linux.log`.
* The logfiles are readable as `csv` files.
* The logfile metrics follow this format:
    * Date
    * Factorization time
    * Resolution time
    * Relative error
    * Physical memory
    * Virtual memory


## Batch execution

The project provides a batch script to run the three implementations and retrieve the metrics for each matrix. To run it:

```sh
$ python batch.py > /dev/null
```

The redirection of the output can be omitted if you don't mind seeing MATLAB crash over and over again (it crashes after the execution of the script).

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