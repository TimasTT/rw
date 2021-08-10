//
// Created by timas on 10.08.2021.
//

#include <iostream>
#include <thread>
#include <vector>

#include <rw.hpp>

int main() {
    int treadsAmount = static_cast<int>(std::thread::hardware_concurrency());

    std::vector<std::thread> threads;
    threads.reserve(treadsAmount);
    for (int i = 0; i < treadsAmount / 2; i++) {
        threads.emplace_back(std::thread(rw::read));
        threads.emplace_back(std::thread(rw::write));
    }

    for (std::thread& thread : threads) {
        thread.join();
    }

    return 0;
}

