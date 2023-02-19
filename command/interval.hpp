#ifndef COMMAND_INTERVAL_HPP
#define COMMAND_INTERVAL_HPP

#include <stdexcept>

class Interval{
    std::size_t start{0U};
    std::size_t stop{0U};

public:
    Interval() = default;

    Interval(const std::size_t &start, const std::size_t &stop);

    [[nodiscard]] size_t get_start() const;

    [[nodiscard]] size_t get_stop() const;

    void set_start(size_t _start);

    void set_stop(size_t _stop);
};
#endif //COMMAND_INTERVAL_HPP
