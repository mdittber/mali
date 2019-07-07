#include<iostream>
#include<eigen3/Eigen/Dense>
using Eigen::MatrixXd;

int main() {
    MatrixXd m(2,2);
    m(0,0) = 3;
    m(1,0) = 2.5;
    m(0,1) = -1;
    m(1,1) = m(1,0) + m(0,1);

    MatrixXd n(2,2);
    n(0,0) = 4;
    n(1,0) = 9.5;
    n(0,1) = -8;
    n(1,1) = n(1,0) + n(0,1);

    std::cout << m << std::endl << std::endl
              << n << std::endl << std::endl
              << m+n << std::endl << std::endl
              << m*n << std::endl << std::endl;

    return(0);
}
