#ifndef COMMAND_COPY_HPP
#define COMMAND_COPY_HPP
#include <utility>

#include "command.hpp"
#include "clipboard.hpp"
#include "interval.hpp"

class Copy: public Command{
private:
    Interval interval;

public:
    explicit Copy(const Interval &interval);

    void redo(TextProcessor &processor) override;

    void undo(TextProcessor &processor) override;
};


#endif //COMMAND_COPY_HPP
