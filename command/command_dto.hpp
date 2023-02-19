#ifndef COMMAND_COMMAND_DTO_HPP
#define COMMAND_COMMAND_DTO_HPP
#include <iostream>
#include <memory>
#include <utility>

#include "interval.hpp"

class CommandDTO final{
    std::string name;
    std::size_t pos{};
    Interval interval;
    std::string str;
public:
    CommandDTO() = default;

    explicit CommandDTO(std::string name) : name(std::move(name)) {}

    CommandDTO(std::string name, const size_t pos) : name(std::move(name)), pos(pos) {}

    CommandDTO(std::string name, const Interval interval) : name(std::move(name)), interval(interval) {}

    CommandDTO(std::string name, const size_t pos, std::string str) : name(std::move(name)), pos(pos), str(std::move(str)) {}

    [[nodiscard]] const std::string &get_name() const {
        return name;
    }

    [[nodiscard]] size_t get_start() const {
        return interval.get_start();
    }

    [[nodiscard]] size_t get_stop() const {
        return interval.get_stop();
    }

    [[nodiscard]] const Interval &get_interval() const {
        return interval;
    }

    [[nodiscard]] std::size_t get_pos() const {
        return pos;
    }

    [[nodiscard]] const std::string &get_str() const {
        return str;
    }
};

#endif //COMMAND_COMMAND_DTO_HPP
