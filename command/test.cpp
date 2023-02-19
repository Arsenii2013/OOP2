#include "gtest/gtest.h"
#include "command.hpp"
#include "command_dto.hpp"
#include "text_processor.hpp"
#include "clipboard.hpp"
#include "insert.hpp"
#include "delete.hpp"
#include "copy.hpp"
#include "paste.hpp"
#include "parser.hpp"
#include "command_names.hpp"
#include "factory.hpp"
#include "service_command_factory.hpp"

//завести тип интервала

TEST(Clipboard, Clipboard){
    EXPECT_EQ("", Clipboard::get_instance().get());
    Clipboard::get_instance().set("aboba");
    EXPECT_EQ("aboba", Clipboard::get_instance().get());
    Clipboard::get_instance().clear();
    EXPECT_EQ("", Clipboard::get_instance().get());
}

TEST(TextProcessor, TextProcessor){
    {
        TextProcessor tp("");

        EXPECT_EQ("", tp.get());
        EXPECT_ANY_THROW(tp.get(0, 11));
        EXPECT_ANY_THROW(tp.erase(0, 11));
        EXPECT_ANY_THROW(tp.set(1, "sample text"));

        EXPECT_NO_THROW(tp.set(0, "sample text"));
        EXPECT_EQ("sample text", tp.get());
        EXPECT_EQ("sample text", tp.get(0, 11));
        EXPECT_ANY_THROW(tp.get(0, 12));
        EXPECT_ANY_THROW(tp.erase(0, 12));

        EXPECT_NO_THROW(tp.erase(0, 11));
        EXPECT_EQ("", tp.get());
        EXPECT_ANY_THROW(tp.get(0, 11));
        EXPECT_ANY_THROW(tp.erase(0, 11));
    }
    {
        const TextProcessor tp("sample text");
        EXPECT_EQ("sample text", tp.get());
        EXPECT_EQ("sample text", tp.get(0, 11));
        EXPECT_ANY_THROW(tp.get(0, 12));
    }
}

TEST(Command, Command){
    TextProcessor tp("sample text");
    {
        const Command cmd{};
        EXPECT_EQ("", cmd.get_name());
    }
    {
        Command cmd("sample command");
        EXPECT_EQ("sample command", cmd.get_name());
        EXPECT_NO_THROW(cmd.undo(tp));
        EXPECT_NO_THROW(cmd.redo(tp));
    }
}

TEST(Command, Insert){
    TextProcessor tp("sample text");
    {
        const Insert cmd{ 0, "sample text"};
        EXPECT_EQ(CommandNames::InsertName, cmd.get_name());
    }
    {
        Insert cmd{ 0, "sample text "};
        EXPECT_NO_THROW(cmd.redo(tp));
        EXPECT_EQ("sample text sample text", tp.get());
        EXPECT_NO_THROW(cmd.undo(tp));
        EXPECT_EQ("sample text", tp.get());
    }
}

TEST(Command, Delete){
    TextProcessor tp("sample text sample text");
    {
        const Delete cmd{ {0, 11}};
        EXPECT_EQ(CommandNames::DeleteName, cmd.get_name());
    }
    {
        Delete cmd{ {0, 12}};
        EXPECT_NO_THROW(cmd.redo(tp));
        EXPECT_EQ("sample text", tp.get());
        EXPECT_NO_THROW(cmd.undo(tp));
        EXPECT_EQ("sample text sample text", tp.get());
    }
}


TEST(Command, Copy){
    TextProcessor tp("sample text");
    {
        const Copy cmd{{ 0, 11}};
        EXPECT_EQ(CommandNames::CopyName, cmd.get_name());
    }
    {
        Copy cmd{ {0, 11}};
        EXPECT_NO_THROW(cmd.redo(tp));
        EXPECT_EQ("sample text", Clipboard::get_instance().get());
        EXPECT_NO_THROW(cmd.undo(tp));
        EXPECT_EQ("sample text", Clipboard::get_instance().get());
    }
}

TEST(Command, Paste){
    TextProcessor tp("sample text");
    {
        const Paste cmd{ 0};
        EXPECT_EQ(CommandNames::PasteName, cmd.get_name());
    }
    {
        Clipboard::get_instance().set(" sample text");
        Paste cmd{11};
        EXPECT_NO_THROW(cmd.redo(tp));
        EXPECT_EQ("sample text sample text", tp.get());
        EXPECT_NO_THROW(cmd.undo(tp));
        EXPECT_EQ("sample text", tp.get());
    }
}

TEST(Parser, CanParse){
    std::istringstream iss;
    Parser p(iss);
    (void) p.parse();
    EXPECT_FALSE(p.can_parse());
}

TEST(Parser, Insert){
    std::string str{"insert 1 hello"};
    std::istringstream iss{str};
    Parser p(iss);
    EXPECT_TRUE(p.can_parse());
    auto dto = p.parse();

    EXPECT_EQ(CommandNames::InsertName, dto.get_name());
    EXPECT_EQ(1, dto.get_pos());
    EXPECT_EQ("hello", dto.get_str());

    EXPECT_FALSE(p.can_parse());
}

TEST(Parser, Delete){
    std::istringstream iss{"delete 1 3"};
    Parser p(iss);
    EXPECT_TRUE(p.can_parse());
    auto dto = p.parse();

    EXPECT_EQ(CommandNames::DeleteName, dto.get_name());
    EXPECT_EQ(1, dto.get_start());
    EXPECT_EQ(3, dto.get_stop());

    EXPECT_FALSE(p.can_parse());
}

TEST(Parser, Paste){
    std::istringstream iss{"paste 1"};
    Parser p(iss);
    EXPECT_TRUE(p.can_parse());
    auto dto = p.parse();

    EXPECT_EQ(CommandNames::PasteName, dto.get_name());
    EXPECT_EQ(1, dto.get_pos());

    EXPECT_FALSE(p.can_parse());
}

TEST(Parser, Copy){
    std::istringstream iss{"copy 1 3"};
    Parser p(iss);
    EXPECT_TRUE(p.can_parse());
    auto dto = p.parse();

    EXPECT_EQ(CommandNames::CopyName, dto.get_name());
    EXPECT_EQ(1, dto.get_start());
    EXPECT_EQ(3, dto.get_stop());

    EXPECT_FALSE(p.can_parse());
}

TEST(Parser, Undo){
    std::istringstream iss{"undo"};
    Parser p(iss);
    EXPECT_TRUE(p.can_parse());
    auto dto = p.parse();

    EXPECT_EQ(CommandNames::UndoName, dto.get_name());

    EXPECT_FALSE(p.can_parse());
}

TEST(Parser, Redo){
    std::istringstream iss{"redo"};
    Parser p(iss);
    EXPECT_TRUE(p.can_parse());
    auto dto = p.parse();

    EXPECT_EQ(CommandNames::RedoName, dto.get_name());

    EXPECT_FALSE(p.can_parse());
}

TEST(TextCommandFactory, Insert){
    TextProcessor tp{{"test"}};
    const CommandDTO dto{std::string{CommandNames::InsertName}, 1, "hello"};
    TextCommandFactory factory;
    auto insert_ptr = factory.create(dto);
    //auto insert_ptr = std::dynamic_pointer_cast<Insert>(std::move(command_ptr));

    EXPECT_EQ(CommandNames::InsertName, insert_ptr->get_name());

    EXPECT_NO_THROW(insert_ptr->redo(tp));
    EXPECT_NO_THROW(insert_ptr->undo(tp));
}


TEST(TextCommandFactory, Delete){
    TextProcessor tp{{"test"}};
    const CommandDTO dto{std::string{CommandNames::DeleteName}, {0, 3}};
    TextCommandFactory factory;
    auto delete_ptr = factory.create(dto);
    //auto delete_ptr = std::dynamic_pointer_cast<Delete>(command_ptr);

    EXPECT_EQ(CommandNames::DeleteName, delete_ptr->get_name());

    EXPECT_NO_THROW(delete_ptr->redo(tp));
    EXPECT_NO_THROW(delete_ptr->undo(tp));
}

TEST(TextCommandFactory, Copy){
    TextProcessor tp{{"test"}};
    const CommandDTO dto{std::string{CommandNames::CopyName}, {0, 3}};
    TextCommandFactory factory;
    auto copy_ptr = factory.create(dto);
    //auto copy_ptr = std::dynamic_pointer_cast<Copy>(command_ptr);

    EXPECT_EQ(CommandNames::CopyName, copy_ptr->get_name());

    EXPECT_NO_THROW(copy_ptr->redo(tp));
    EXPECT_NO_THROW(copy_ptr->undo(tp));
}

TEST(TextCommandFactory, Paste){
    Clipboard::get_instance().set("test");
    TextProcessor tp{{"test"}};

    const CommandDTO dto{CommandNames::PasteName, 0};
    TextCommandFactory factory;
    auto paste_ptr = factory.create(dto);
    //auto paste_ptr = std::dynamic_pointer_cast<Paste>(command_ptr);

    EXPECT_EQ(CommandNames::PasteName, paste_ptr->get_name());

    EXPECT_NO_THROW(paste_ptr->redo(tp));
    EXPECT_NO_THROW(paste_ptr->undo(tp));
}

namespace{
    bool undoed = false;
    bool redoed = false;
    class TestCommand : public Command {
    public:
        void redo(TextProcessor &) override {
            redoed = true;
            undoed = false;
        };

        void undo(TextProcessor &) override {
            redoed = false;
            undoed = true;
        };
    };

    TEST(CommandStack, CommandStack) {
        std::shared_ptr<TextProcessor> tp{new TextProcessor{"test"}};
        CommandStack stack{tp};

        auto test_ptr = std::make_unique<TestCommand>();
        stack.add_and_execute(std::move(test_ptr));
        EXPECT_TRUE(redoed);
        stack.undo();
        EXPECT_TRUE(undoed);
        stack.redo();
        EXPECT_TRUE(redoed);
    }
}

TEST(ServiceCommandFactory, Undo){
    TextProcessor tp{{"test"}};
    const CommandDTO dto{std::string{CommandNames::UndoName}};
    ServiceCommandFactory factory;
    auto undo_ptr = factory.create(dto);
    //auto undo_ptr = std::dynamic_pointer_cast<Undo>(command_ptr);

    EXPECT_EQ(CommandNames::UndoName, undo_ptr->get_name());
}

TEST(ServiceCommandFactory, Redo){
    TextProcessor tp{{"test"}};
    const CommandDTO dto{std::string{CommandNames::RedoName}};
    ServiceCommandFactory factory;
    auto redo_ptr = factory.create(dto);
    //auto redo_ptr = std::dynamic_pointer_cast<Redo>(command_ptr);

    EXPECT_EQ(CommandNames::RedoName, redo_ptr->get_name());
}
