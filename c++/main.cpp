#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <filesystem>
#include <Eigen/Sparse>
#include <Eigen/unsupported/SparseExtra>

using namespace Eigen;

std::string get_platform()
{
    #ifdef _WIN64 || _WIN32
    return "Windows";
    #elif __unix || __unix__ || __linux__
    return "Linux";
    #elif __APPLE__ || __MACH__
    return "MacOSX";
    #else
    return "Other";
    #endif
} 

int main(int argc, char *argv[])
{
    //if(argc < 2) return -1;

    std::string mat_path = argv[1];
    std::string mat_name = std::filesystem::path(mat_path).filename();

    typedef SparseMatrix<double, ColMajor, int64_t> SpMat;
    SpMat A;
    loadMarket(A, mat_path);

    int n = A.cols();
    VectorXd xe = VectorXd::Constant(n, 1);
    MatrixXd b = A.selfadjointView<Lower>() * xe;
    //MatrixXd b = A * xe;

    // Cholesky Factorization:
    auto start = std::chrono::high_resolution_clock::now();
    SimplicialCholesky<SpMat> chol(A.selfadjointView<Lower>());
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration<double>(end - start);
    std::string factorization_time(std::to_string(elapsed.count()));

    start = std::chrono::high_resolution_clock::now();
    VectorXd x = chol.solve(b);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration<double>(end - start);
    std::string resolution_time(std::to_string(elapsed.count()));

    VectorXd tmp = x - xe;
    double rel_error = tmp.norm()/xe.norm();

    // Writing logfile
    time_t curr_time;
	tm * curr_tm;
	char date_string[100];
    char timestamp[100];
	
	time(&curr_time);
	curr_tm = localtime(&curr_time);
	strftime(timestamp, 50, "%d%m%Y-%H:%M:%S", curr_tm);
	strftime(date_string, 50, "%d-%m-%Y %H:%M:%S", curr_tm);

    // log_path directory must exist in the path where the executable is launched
    std::string log_path = "log/";
    std::string platform = get_platform();
    std::fstream logfile;
    std::string filename = mat_name + "-" + "cpp-" + platform + "-" + timestamp + ".log";
    logfile.open(log_path + filename, std::fstream::app);

    if (logfile.is_open())
    {
        logfile << "Date, " << date_string << "\n";
        logfile << "Factorization time, " << factorization_time << "\n";
        logfile << "Resolution time, " << resolution_time << "\n";
        logfile << "Relative error, " << rel_error << "\n\n";
    }

    logfile.close();

    //std::cout << filename << std::endl;

    return 0;
}
