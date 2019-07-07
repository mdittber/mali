#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <chrono>
#include <condition_variable>
#include <mutex>

class ThreadPool {
    public:
        ThreadPool(int threadNum) {
            if(threadNum < 1) {
                mThreadNum = 2;
            } else {
                mThreadNum = threadNum;
            }
            for(int i=0; i<mThreadNum; i++) {
                mThreads.emplace_back([=](){
                    std::unique_lock<std::mutex> lock(mEventMutex);
                    std::cout << "Thread " << i << " starting" << std::endl;
                    mEvent.wait_for(lock, std::chrono::seconds(10)); // , []{ return(false); });
                    int value;
                    if(!mTasks.empty()) {
                        value = mTasks.front();
                        mTasks.pop();
                    }
                    mTask(value);
                    std::cout << "Thread " << i << " exitting" << std::endl;
                });
            }
        }
        ~ThreadPool() {
            stop();
        }
        void start();
        void stop() {
            mEvent.notify_all();
            for(auto &t: mThreads) {
                t.join();
            }
        }
        void emplace(int task) {
            std::lock_guard<std::mutex> lock(mEventMutex);
            mTasks.push(task);
            mEvent.notify_one();
        }

    private:
        int mThreadNum;
        std::vector<std::thread> mThreads;
        std::queue<int> mTasks;
        std::mutex mEventMutex;
        std::condition_variable mEvent;
        void mTask(int value) {
            std::cout << "Running task " << value << " done." << std::endl;
        }

};

int main() {
    ThreadPool pool(4);

    std::this_thread::sleep_for(std::chrono::seconds(3));
    pool.emplace(88);

    return(0);
}