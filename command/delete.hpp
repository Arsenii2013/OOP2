#ifndef COMMAND_DELETE_HPP
#define COMMAND_DELETE_HPP
#include <utility>

#include "command.hpp"
#include "interval.hpp"

class Delete: public Command{
private:
    Interval interval;
    std::string saved_str;

public:
    explicit Delete(const Interval &interval);

    void redo(TextProcessor &processor) override;

    void undo(TextProcessor &processor) override;
};

#endif //COMMAND_DELETE_HPP
