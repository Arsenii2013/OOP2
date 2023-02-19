#ifndef COMMAND_PASTE_HPP
#define COMMAND_PASTE_HPP
#include <utility>

#include "command.hpp"

class Paste: public Command{
private:
    std::size_t pos;
    std::string from_clipboard;
    bool value_getted{false};

public:
    explicit Paste(size_t pos);

    void redo(TextProcessor &processor) override;

    void undo(TextProcessor &processor) override;
};


#endif //COMMAND_PASTE_HPP
