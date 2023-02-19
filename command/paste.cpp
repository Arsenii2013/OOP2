#include "paste.hpp"
#include "command_names.hpp"

void Paste::redo(TextProcessor &processor) {
    if(!value_getted) {
        from_clipboard = Clipboard::get_instance().get();
        value_getted = true;
    }
    processor.set(pos, from_clipboard);
}

void Paste::undo(TextProcessor &processor) {
    processor.erase(pos, pos + from_clipboard.size());
}

Paste::Paste(size_t pos) : pos(pos), Command(CommandNames::PasteName){}
