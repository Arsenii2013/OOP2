#include "delete.hpp"
#include "command_names.hpp"

void Delete::redo(TextProcessor &processor) {
    saved_str = processor.get(interval.get_start(), interval.get_stop());
    processor.erase(interval.get_start(), interval.get_stop());
}

void Delete::undo(TextProcessor &processor) {
    processor.set(interval.get_start(), saved_str);
}

Delete::Delete(const Interval &interval) : interval(interval), Command(CommandNames::DeleteName) {}
