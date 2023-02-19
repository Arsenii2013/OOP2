#include "copy.hpp"
#include "command_names.hpp"

void Copy::redo(TextProcessor &processor) {
    Clipboard::get_instance().set(processor.get(interval.get_start(), interval.get_stop()));
}

void Copy::undo(TextProcessor &processor) {
}

Copy::Copy( const Interval &interval) : Command(CommandNames::CopyName), interval(interval) {}
