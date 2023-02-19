#include <iostream>
#include <fstream>

#include "text_editor.hpp"
#include "parser.hpp"

using namespace std;
int main(int argc, char **argv) {
    if(argc != 3){
        cout << "Usage: " << argv[0] << " text_file command_file" << endl;
    }
    std::ifstream text_file(argv[1]);
    std::ifstream command_file(argv[2]);
    std::string text_string;
    getline(text_file, text_string);
    text_file.close();

    Parser parser{command_file};
    TextCommandFactory text_command_creator{};
    ServiceCommandFactory service_command_creator{};

    TextEditor editor{text_string};

    while(parser.can_parse()) {
        auto cmd = parser.parse();

        if(text_command_creator.create(cmd)){
            editor.process(text_command_creator.create(cmd));
        }

        if(service_command_creator.create(cmd)){
            editor.process(service_command_creator.create(cmd));
        }
    }

    cout << editor.get() << endl;

    std::ofstream out_file(argv[1]);
    out_file << editor.get() << endl;
    return 0;
}
