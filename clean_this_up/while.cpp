#include<iostream>
#include<thread>
#include<vector>
#include<chrono>
#include<mutex>

bool run_all = true;

std::mutex m_cout;

void stopper(unsigned int secs = 5) {
    if(secs > 60) {
        secs = 60;
    }
    std::this_thread::sleep_for(std::chrono::seconds(secs));
    std::lock_guard<std::mutex> ul(m_cout);
    std::cout << "Stopping all threads ..." << std::endl;
    run_all = false;
}

void worker(int id, unsigned int N_elements) {
    long long i = 0;
    std::unique_lock<std::mutex> ul(m_cout);
    std::cout << "Started worker " << id << std::endl;
    std::cout << id << " allocates memory for " << N_elements << " integers ... ";
    ul.unlock();
    int *array = new int[N_elements];
    for(int i=0; i<N_elements; i++) {
        array[i] = id;
    }
    ul.lock();
    std::cout << "done." << std::endl;
    ul.unlock();
    while(run_all) {
        i++;
    }
    delete [] array;
    ul.lock();
    std::cout << "Worker " << id+1 << " stopped." << std::endl;
}

int main(int argc, char **argv) {
    const unsigned int N_THREADS = std::thread::hardware_concurrency();
    std::cout << N_THREADS << " threads detected." << std::endl;

    unsigned int N_elements = 6.2e10 / N_THREADS / sizeof(int);
    std::cout << "Allocate int array with " << N_elements << " elements in each thread." << std::endl;

    std::thread t_stop(stopper, 20);
    std::vector<std::thread> thread_vec;
    for(int i=0; i<N_THREADS; i++) {
        thread_vec.push_back(std::thread(worker, i+1, N_elements));
    }
    for(auto &t: thread_vec) {
        t.join();
    }
    t_stop.join();
    return(0);
}