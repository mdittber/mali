#include<iostream>
#include<random>
#include<chrono>

std::mt19937 mt_global;
std::uniform_real_distribution<double> dist_global(0,1);

double get_random(double lower = 0, double upper = 1) {
    /*
    std::mt19937 mt;
    std::uniform_real_distribution<double> dist(lower, upper);
    double x = dist(mt);
    return( x );
    */
   return( dist_global(mt_global) );
}

struct Random {
    Random(double lower = 0, double upper = 1):
         lower(lower), upper(upper) {
        // mt(rd());
        dist = std::uniform_real_distribution<double>(lower, upper);
    }
    double get() {
        /*
        x = dist(mt);
        return( x );
        */
       return( dist(mt) );
    }

    private:
        double x;
        double lower, upper;
        std::uniform_real_distribution<double> dist;
        // std::random_device rd;
        std::mt19937 mt;
};

int main(int argc, char **argv) {
    Random rand;
    constexpr unsigned int N_numbers = 1000000;

    std::cout << "Print " << N_numbers << " random numbers." << std::endl;
    for(auto i=0; i<10; i++) {
        std::cout << "#" << i+1 << " = " << rand.get() << std::endl;
    }

    std::cout << "Generate " << N_numbers << " random numbers using a class." << std::endl;
    auto start = std::chrono::steady_clock::now();
    double number1;
    for(auto i=0; i<N_numbers; i++) {
        number1 = rand.get();
    }
    auto stop = std::chrono::steady_clock::now();
    std::cout << "Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count() << " milliseconds." << std::endl;


    std::cout << "Generate " << N_numbers << " random numbers using a plain function." << std::endl;
    start = std::chrono::steady_clock::now();
    double number2;
    for(auto i=0; i<N_numbers; i++) {
        number2 = get_random();
    }
    stop = std::chrono::steady_clock::now();
    std::cout << "Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count() << " milliseconds." << std::endl;

    return(0);
}