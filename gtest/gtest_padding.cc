#include "gtest_padding.h"

#include <memory>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
using ::testing::AtLeast;

// Cache line size on most processors (in bytes)
constexpr int CACHE_LINE_SIZE = 64;

// Structure with false sharing problems
struct SharedData {
    int counter1;
    int counter2;
};

// Structure with padding to avoid false sharing
struct PaddedData {
    int counter1;
    char padding[CACHE_LINE_SIZE - sizeof(int)]; // Padding to fill a cache line
    int counter2;
};

void benchmark_false_sharing() {
    SharedData shared;
    shared.counter1 = 0;
    shared.counter2 = 0;

    const int iterations = 100000000;

    auto start = std::chrono::high_resolution_clock::now();

    std::thread t1([&shared, iterations]() {
        for (int i = 0; i < iterations; i++) {
            shared.counter1++;
        }
        });

    std::thread t2([&shared, iterations]() {
        for (int i = 0; i < iterations; i++) {
            shared.counter2++;
        }
        });

    t1.join();
    t2.join();

    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "False sharing: "
        << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
        << "ms" << std::endl;
}

void benchmark_padded() {
    PaddedData padded;
    padded.counter1 = 0;
    padded.counter2 = 0;

    const int iterations = 100000000;

    auto start = std::chrono::high_resolution_clock::now();

    std::thread t1([&padded, iterations]() {
        for (int i = 0; i < iterations; i++) {
            padded.counter1++;
        }
        });

    std::thread t2([&padded, iterations]() {
        for (int i = 0; i < iterations; i++) {
            padded.counter2++;
        }
        });

    t1.join();
    t2.join();

    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "With padding: "
        << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
        << "ms" << std::endl;
}

namespace gtest_padding
{
	TEST_F(GTest_padding, test_padding_1)
	{
        benchmark_false_sharing();
        benchmark_padded();
	}

} // namespace gtest_padding
