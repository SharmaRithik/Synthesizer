#include <iostream>
#include <atomic>
#include <thread>

std::atomic<int> counter(0);

void incrementCounter() {
    int localCounter = counter.load(std::memory_order_relaxed);
    localCounter++;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    counter.store(localCounter, std::memory_order_relaxed);
}

int main() {
    std::thread t1(incrementCounter);
    std::thread t2(incrementCounter);

    t1.join();
    t2.join();

    std::cout << "Final counter value: " << counter << std::endl;

    return 0;
}
