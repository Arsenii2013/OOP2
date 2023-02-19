#include "creator_by_file.hpp"

Command CreatorByFile::get(const std::filesystem::path &filename) {
    std::ifstream is(filename);
    std::string str;
    getline(is, str);

    Parser p{str};
    return p.get();
}
