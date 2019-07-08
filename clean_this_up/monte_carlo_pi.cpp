#include<iostream>
#include<iomanip>
#include<fstream>
#include<random>
#include<thread>
#include<vector>
#include<future>
#include<mutex>

std::mutex m_cout;

struct Random {
    Random(double lower_x = 0, double lower_y = 0, double upper_x = 1, double upper_y = 1):
         lower_x(lower_x), lower_y(lower_y),  upper_x(upper_x),  upper_y(upper_y) {
        x_dist = std::uniform_real_distribution<double>(lower_x, upper_x);
        y_dist = std::uniform_real_distribution<double>(lower_y, upper_y);
        // rd = std::random_device();
        mt = std::mt19937(rd());
    }
    std::pair<double, double> get() {
        x = x_dist(mt);
        y = y_dist(mt);
        return( std::make_pair(x,y) );
    }

    private:
        double x, y;
        double lower_x;
        double lower_y;
        double upper_x;
        double upper_y;
        std::uniform_real_distribution<double> x_dist;
        std::uniform_real_distribution<double> y_dist;
        std::mt19937 mt;
        std::random_device rd;
};

// double approximate_pi(unsigned int N = 10000, bool write_to_file = false) {
std::pair<unsigned long long, unsigned long long> approximate_pi(unsigned int N = 10000, bool write_to_file = false, int id = 0) {

    std::unique_lock<std::mutex> ul(m_cout);
    std::cout << "Started worker " << id << std::endl;
    ul.unlock();

    std::ofstream fout;
    if(write_to_file) {
        fout.open("points.csv");
        fout << "x,y" << std::endl;
    }

    double pi;
    
    double r = 1000;
    Random rand(-r,-r,r,r);

    std::pair<double,double> p;

    unsigned long long N_circle = 0;
    unsigned long long N_square = 0;
    double radius;
    for(unsigned int i=0; i<N; i++) {
        p = rand.get();
        if(write_to_file) {
            fout << p.first << "," << p.second << std::endl;
        }
        radius = sqrt( pow(p.first,2) + pow(p.second,2) );
        if(radius <= r) {
            N_circle++;
        }
        N_square++;
    }
    if(write_to_file) {
        fout.close();
    }
    std::cout << "N_circle = " << N_circle << std::endl;
    std::cout << "N_square = " << N_square << std::endl;

    std::pair<unsigned long long, unsigned long long> result;
    result = std::make_pair(N_circle, N_square);
    return(result);

    // pi = 4*double(N_circle) / double(N_square);
    /*
    unsigned int iter = 0;
    unsigned int N_iter = 1000;
    double err = 0;
    double tol = 1;
    while(iter < N_iter && err < tol) {
        1+1;
    }
    */
    // return(pi);
}

int main(int argc, char **argv) {
    
    double r = 1000;
    Random rand(-r,-r,r,r);
    auto point = rand.get();

    std::cout << "(x,y) = (" << point.first << "," << point.second << ")" << std::endl;
    
    double pi = 3.0;
    unsigned int N = 10000;
    if(argc == 2) {
        N = atoi(argv[1]);
    }
    // pi = approximate_pi(N);

    unsigned long long N_circle = 0;
    unsigned long long N_square = 0;
    int N_THREADS =  std::thread::hardware_concurrency()-1;
    std::vector< std::future< std::pair<unsigned long long, unsigned long long> > > futures;
    std::pair<unsigned long long, unsigned long long> p;
    for(int i=0; i<N_THREADS; i++) {
        futures.push_back(std::async(approximate_pi, N, false, i+1));
    }
    for(auto &f: futures) {
        p = f.get();
        N_circle += p.first;
        N_square += p.second;
    }
    pi = 4*double(N_circle) / double(N_square);
    std::cout << "Pi ~ " << std::setprecision(10) << pi << std::endl;

    return(0);
}