#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <experimental/filesystem>
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
    if(argc < 2) {
        std::cout << "Missing matrix path" << std::endl;
        return -1;
    }
    std::string mat_path = argv[1];
    std::string mat_name = std::experimental::filesystem::path(mat_path).string();

    typedef SparseMatrix<double, ColMajor, long long> SpMat;
    SpMat A;
    loadMarket(A, mat_path);

    int n = A.cols();
    VectorXd xe = VectorXd::Constant(n, 1);
    MatrixXd b = A.selfadjointView<Lower>() * xe;

    // Cholesky Factorization:
    auto start = std::chrono::high_resolution_clock::now();
    SimplicialLDLT<SpMat> chol(A.selfadjointView<Lower>());
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

	time(&curr_time);
	curr_tm = localtime(&curr_time);
	strftime(date_string, 50, "%d-%m-%Y %H:%M:%S", curr_tm);

    std::string platform = get_platform();

    size_t lastindex;
    if(platform == "Linux") {lastindex = mat_name.find_last_of("/");}
    else {lastindex = mat_name.find_last_of("\\");}

    std::string name = mat_name.substr(lastindex+1, mat_name.length());
    lastindex = name.find_last_of("."); 
    name = name.substr(0, lastindex);

    std::string data_file = "data/data.csv";
    std::fstream logfile;
    logfile.open(data_file, std::fstream::app);

    if (logfile.is_open())
    {
        //["date", "platform", "name", "library", "factorization time", "resolution time", "relative error", "physical memory", "virtual memory"]
        
        logfile << date_string << ", ";
        logfile <<  platform << ", ";
        logfile << name << ", ";
        logfile << "eigen" << ", ";
        logfile <<  factorization_time << ", ";
        logfile <<  resolution_time << ", ";
        logfile <<  rel_error << ", ";
        
    }

    logfile.close();

    return 0;
}
