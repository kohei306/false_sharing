#include <iostream>
#include <chrono>
#include <thread>
#include <new>
using namespace std;

const int NUM_THREADS = 1;
const int NUM_ELEMENTS = 1000000;

// Define a global array of integers
int data[NUM_ELEMENTS];

// Define a function that increments the elements of the array
void increment(int start, int end)
{
    for (int i = start; i < end; ++i) {
        data[i]++;
    }
}

// Define a function that measures the time it takes to execute a function
template <typename F, typename... Args>
auto time_it(F&& f, Args&&... args) {
    auto start_time = chrono::high_resolution_clock::now();
    f(std::forward<Args>(args)...);
    auto end_time = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
}

int main()
{
    // Spawn multiple threads to increment the elements of the array
    thread threads[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; ++i) {
        threads[i] = thread(increment, i * NUM_ELEMENTS / NUM_THREADS, (i + 1) * NUM_ELEMENTS / NUM_THREADS);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; ++i) {
        threads[i].join();
    }

    // Measure the time it took to execute the function
    auto elapsed_time = time_it(increment, 0, NUM_ELEMENTS);

    // Print the elapsed time
    cout << "Elapsed time: " << elapsed_time << " microseconds" << endl;

    return 0;
}

