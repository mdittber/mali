#ifndef PROGRESS_BAR_HPP
#define PROGRESS_BAR_HPP

#include <iostream>
#include <chrono>
#include <cmath>

class ProgressBar {
    public:
        ProgressBar(unsigned int N, unsigned int width = 80): mN(N), mWidth(width) {
            std::cout << "ProgressBar initialized." << std::endl;
            mNonContributing = 2;
            std::cout << "|" << std::flush;
        }

        void update(unsigned int i = 1) {
            mCounter += i;
            mNewIndex = round( double(mCounter)/double(mN)*(mWidth-mNonContributing) );
            if(mNewIndex != mIndex) {
                for(int i=mIndex; i<mNewIndex; i++) {
                    std::cout << "." << std::flush;
                }
                mIndex = mNewIndex;
            }

            if(mCounter == mN) {
                std::cout << "|" << std::endl;
            }
        }

    private:
        unsigned int mN, mWidth, mNonContributing, mCounter = 0;
        double mIndex    = 0;
        double mNewIndex = 0;
};

#endif