//
// Created by timas on 10.08.2021.
//

#include "rw.hpp"

namespace rw {
    void read() {
        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::uniform_int_distribution<std::mt19937::result_type> dist(0, 20);
        std::this_thread::sleep_for(std::chrono::milliseconds(dist(rng)));

        std::unique_lock<std::mutex> lk(m, std::defer_lock);
        lk.lock();
        if (readers_count == -1) {
            reader_cond.wait(lk, []() { return readers_count != -1; });
        }
        readers_count++;
        std::cout << "read value: " << counter << ", number of readers: " << readers_count << std::endl;
        readers_count--;
        if (readers_count == 0) {
            writer_cond.notify_all();
        }
        lk.unlock();
    }

    void write() {
        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::uniform_int_distribution<std::mt19937::result_type> dist(0, 20);
        std::this_thread::sleep_for(std::chrono::milliseconds(dist(rng)));

        std::unique_lock<std::mutex> lk(m, std::defer_lock);
        lk.lock();
        if (readers_count > 0) {
            writer_cond.wait(lk, []() { return readers_count == 0; });
        }
        readers_count = -1;
        counter++;
        std::cout << "written value: " << counter << ", number of readers: " << readers_count << std::endl;
        readers_count = 0;
        reader_cond.notify_all();
        writer_cond.notify_all();
        lk.unlock();

    }
}
