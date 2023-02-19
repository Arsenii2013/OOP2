#ifndef COMMAND_CLIPBOARD_HPP
#define COMMAND_CLIPBOARD_HPP
#include <string>
#include <utility>

class Clipboard{
private:
    std::string str;

    Clipboard() = default;
public:
    Clipboard(const Clipboard&) = delete;
    Clipboard operator=(const Clipboard&) = delete;

    static Clipboard& get_instance();

    [[nodiscard]] const std::string& get() const noexcept;

    void set(const std::string& _str);

    void clear() noexcept;
};



#endif //COMMAND_CLIPBOARD_HPP
