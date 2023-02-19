#ifndef COMMAND_COMMAND_NAMES_HPP
#define COMMAND_COMMAND_NAMES_HPP
#include <string_view>
#include "insert.hpp"
#include "delete.hpp"
#include "copy.hpp"
#include "paste.hpp"
#include "undo.hpp"
#include "redo.hpp"


namespace CommandNames {
    const std::string InsertName{"insert"};
    const std::string DeleteName{"delete"};
    const std::string CopyName{"copy"};
    const std::string PasteName{"paste"};
    const std::string UndoName{"undo"};
    const std::string RedoName{"redo"};
}
#endif //COMMAND_COMMAND_NAMES_HPP
