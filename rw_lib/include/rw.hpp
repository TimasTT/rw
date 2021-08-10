//
// Created by timas on 10.08.2021.
//

#ifndef RW_RW_HPP
#define RW_RW_HPP

#include <condition_variable>
#include <mutex>

namespace rw {

    int readersCount = 0;
    int data = 0;  // data for reading/writing

    std::mutex mtx;
    std::condition_variable readersCv;
    std::condition_variable writersCv;

    void read();

    void write();

}

#endif //RW_RW_HPP
