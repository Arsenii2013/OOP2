#include "clipboard.hpp"


Clipboard &Clipboard::get_instance() {
    static Clipboard cl;
    return cl;
}

const std::string &Clipboard::get() const noexcept {
    return str;
}

void Clipboard::set(const std::string &_str) {
    str = _str;
}

void Clipboard::clear() noexcept {
    str.clear();
}
