# Sparse Linear Systems Solvers Comparison Tests
> Comparison tests for the Cholesky method for the resolution of sparse linear systems of equations between MATLAB, Python's Scikit library, on Linux and Windows

Project 1 for the *Methods of Scientific Computing* course for the MSc in Computer Science at University of Milano-Bicocca.

![](header.png)

## Brief

To make tests easier to replicate -> containers\
Linux/Windows container must have same specs\
Monitoring to check stats\
Run MATLAB/X script in both container, extract stats, compare

## Prerequisites

Prerequisites for Python
* NumPy
* SciPy
* SuiteSparse (CHOLMOD) (scikit-sparse)

Prerequisites for MATLAB


## Installation

### For Python
```sh
git clone https://github.com/Dodicin/slss-comparison-test
cd slss-comparison-test
cd python
virtualenv .venv
source .venv/bin/activate
pip install numpy
pip install scikit-sparse
```

## Usage example

Start Windows container
Run
Somehow get metrics

Start Linux container
Run
Somehow get metrics


## Author

* **Marco Ferri** (807130) -
* **Nassim Habbash** (808292) - [dodicin](https://github.com/dodicin)

<!-- Markdown link & img dfn's -->
[npm-image]: https://img.shields.io/npm/v/datadog-metrics.svg?style=flat-square
[npm-url]: https://npmjs.org/package/datadog-metrics
[npm-downloads]: https://img.shields.io/npm/dm/datadog-metrics.svg?style=flat-square
[travis-image]: https://img.shields.io/travis/dbader/node-datadog-metrics/master.svg?style=flat-square
[travis-url]: https://travis-ci.org/dbader/node-datadog-metrics
[wiki]: https://github.com/yourname/yourproject/wiki
