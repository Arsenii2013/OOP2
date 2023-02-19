#include "insert.hpp"
#include "command_names.hpp"

void Insert::redo(TextProcessor &processor) {
    processor.set(pos, str);
}

void Insert::undo(TextProcessor &processor) {
    processor.erase(pos, pos + str.size());
}

Insert::Insert(size_t pos, std::string str) :
        pos(pos), str(std::move(str)), Command( CommandNames::InsertName) {}
