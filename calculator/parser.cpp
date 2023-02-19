#include "parser.hpp"

static std::map<std::string, std::function<double (double, double)>> commands{
        {"add", [](double a , double b){return a + b; }},
        {"mult", [](double a , double b){return a * b; }},
        {"add_sq", [](double a , double b){return a * a + b * b; }},
        {"sq_add", [](double a , double b){return (a + b) * (a + b); }},
        {"sub", [](double a , double b){return a - b; }},
        {"div", [](double a , double b){return a / b; }},
};

Command Parser::get() {
    std::istringstream iss(string_to_parse);
    try{
        std::string name;
        iss >> name;
        double arg1, arg2;
        iss >> arg1 >> arg2;
        return {commands[name], name, arg1, arg2};
    }catch(...){
        throw std::runtime_error("invalid command");
    }
}
