#include "interval.hpp"

Interval::Interval(const size_t &start, const size_t &stop) : start(start), stop(stop) {
    if(start > stop){
        throw std::runtime_error("start > stop");
    }
}

size_t Interval::get_start() const {
    return start;
}

size_t Interval::get_stop() const {
    return stop;
}

void Interval::set_start(size_t _start) {
    Interval::start = _start;
    if(start > stop){
        throw std::runtime_error("start > stop");
    }
}

void Interval::set_stop(size_t _stop) {
    Interval::stop = _stop;
    if(start > stop){
        throw std::runtime_error("start > stop");
    }
}
