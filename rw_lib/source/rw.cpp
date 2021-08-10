//
// Created by timas on 10.08.2021.
//

#include <iostream>
#include <random>
#include <thread>

#include "rw.hpp"

namespace rw {

    int readersCount = 0;  // if readersCount == -1, then writer write now
    int data = 0;  // data for reading/writing

    std::mutex mtx;
    std::condition_variable readersCv;
    std::condition_variable writersCv;

    void read() {
        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::uniform_int_distribution<std::mt19937::result_type> dist(0, 20);
        std::this_thread::sleep_for(std::chrono::milliseconds(dist(rng)));

        std::unique_lock<std::mutex> locker(mtx, std::defer_lock);
        locker.lock();
        if (readersCount == -1) {
            readersCv.wait(locker, []() { return readersCount != -1; });
        }

        readersCount++;
        locker.unlock();
        std::cout << std::this_thread::get_id() << " reading data: " << data << std::endl;
        locker.lock();
        readersCount--;
        if (readersCount == 0) {
            writersCv.notify_all();
        }
        locker.unlock();
    }

    void write() {
        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::uniform_int_distribution<std::mt19937::result_type> dist(0, 20);
        std::this_thread::sleep_for(std::chrono::milliseconds(dist(rng)));

        std::unique_lock<std::mutex> locker(mtx, std::defer_lock);
        locker.lock();
        if (readersCount > 0) {
            writersCv.wait(locker, []() { return readersCount == 0; });
        }

        readersCount = -1;
        locker.unlock();
        data++;
        std::cout << std::this_thread::get_id() << " writhing data: " << data << std::endl;
        locker.lock();
        readersCount = 0;
        readersCv.notify_all();
        writersCv.notify_all();
        locker.unlock();
    }
}
