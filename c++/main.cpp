#include <iostream>
#include <Eigen/Sparse>
#include <Eigen/unsupported/SparseExtra>

using namespace Eigen;

typedef SparseMatrix<double> SpMat;

int main()
{
    SpMat A;
    loadMarket(A, "../res/matrices/ex15.mtx");

    int n = A.cols();
    VectorXd xe = VectorXd::Constant(n, 1);
    MatrixXd b = A.selfadjointView<Upper>() * xe;
    //MatrixXd b = A * xe;

    // Cholesky Factorization:
    SimplicialCholesky<SpMat> chol(A);
    VectorXd x = chol.solve(b);

    VectorXd tmp = x - xe;
    double rel_error = tmp.norm()/xe.norm();

    std::cout << "Relative error: " << rel_error << std::endl;

}
