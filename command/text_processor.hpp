//
// Created by sescer on 23.11.22.
//

#ifndef COMMAND_TEXT_PROCESSOR_HPP
#define COMMAND_TEXT_PROCESSOR_HPP

#include <string>
#include <utility>
#include <stdexcept>

class TextProcessor{
private:
    std::string str;
public:
    explicit TextProcessor(std::string str) : str(std::move(str)) {}

    [[nodiscard]] constexpr const std::string& get() const;

    [[nodiscard]] constexpr std::string get(std::size_t start, std::size_t stop) const;

    constexpr void set(std::size_t pos, const std::string& _str);

    constexpr void erase(std::size_t start, std::size_t stop);
};

constexpr const std::string &TextProcessor::get() const {
    return str;
}

constexpr std::string TextProcessor::get(std::size_t start, std::size_t stop) const {
    if(start > stop || start > str.size() || stop > str.size()){
        throw std::runtime_error("trying to operate char over str");
    }
    return str.substr(start, stop - start);
}

constexpr void TextProcessor::set(std::size_t pos, const std::string &_str) {
    if(pos > str.size()){
        throw std::runtime_error("trying to operate char over str");
    }
    str.insert(pos, _str);
}

constexpr void TextProcessor::erase(std::size_t start, std::size_t stop) {
    if(start > stop || start > str.size() || stop > str.size()){
        throw std::runtime_error("trying to operate char over str");
    }
    str.erase(start, stop - start);
}


/*
 * 1. Хранить ссылки TextProcessor& processor; опасно. Нет гарантии существования объекта на момент использования.
 */
#endif //COMMAND_TEXT_PROCESSOR_HPP
