#ifndef DIGITS_HPP
#define DIGITS_HPP

#include <cmath>

namespace mali
{
namespace v1
{

    int numDigits(int number) {
        int digits = 1;
        if(number != 0) {
            if(number < 0 || number == 1) digits++;
            number = abs(number);
            digits += floor( log10(number) );
        }
        return(digits);
    }

}   // namespace mali
}   // namespace v1

#endif