# Sparse Linear Systems Solvers Comparison Tests
> Comparison tests for the Cholesky method for the resolution of sparse linear systems of equations between MATLAB, Python's Scikit library, on Linux and Windows

Project for the *Methods of Scientific Computing* course for the MSc in Computer Science at University of Milano-Bicocca.

## Brief


## Prerequisites

The following sparse matrices from `https://sparse.tamu.edu/` have to be downloaded inside `res/matrices`, in the `mtx` format. Only the `ex15` matrix is provided with the project. 

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
$ cd python
$ virtualenv .venv
$ source .venv/bin/activate
$ pip install numpy
$ pip install scipy
$ pip install scikit-sparse
$ python main.py [matrix name, e.g. ex15.mtx]
```
### For C++
```sh
$ cd c++
$ g++ -Ilib main.cpp main.exe
$ ./main.exe [matrix name, e.g. ex15.mtx]
```

## Metrics

Metrics are saved under `./log`, in the following format:

* Logfile: [Matrix name]-[Program]-[Platform].log, for example: `ex15.mtx-cpp-Linux.log`.
* The logfiles are readable as `csv` files.
* The logfile metrics follow this format:
    * Date, 22-05-2019 10:11:33
    * Factorization time, 0.198387
    * Resolution time, 0.012410
    * Relative error, 7.26641e-07
    * Newline

## Author

* **Marco Ferri** (807130)
* **Nassim Habbash** (808292) - [dodicin](https://github.com/dodicin)

<!-- Markdown link & img dfn's -->
[npm-image]: https://img.shields.io/npm/v/datadog-metrics.svg?style=flat-square
[npm-url]: https://npmjs.org/package/datadog-metrics
[npm-downloads]: https://img.shields.io/npm/dm/datadog-metrics.svg?style=flat-square
[travis-image]: https://img.shields.io/travis/dbader/node-datadog-metrics/master.svg?style=flat-square
[travis-url]: https://travis-ci.org/dbader/node-datadog-metrics
[wiki]: https://github.com/yourname/yourproject/wiki