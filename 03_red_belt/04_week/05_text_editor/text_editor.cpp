#include <string>
#include <list>
#include "test_runner.h"
using namespace std;

class Editor {
public:
    Editor();
    void Left();   // сдвинуть курсор влево
    void Right();  // сдвинуть курсор вправо
    void Insert(char token);   // вставить символ token
    void Copy(size_t tokens);  // cкопировать
    // не более tokens символов,
    // начиная с текущей позиции курсора
    void Cut(size_t tokens);  // вырезать не более tokens символов,
    // начиная с текущей позиции курсора
    void Paste();  // вставить содержимое буфера
    // в текущую позицию курсора
    string GetText() const;  // получить текущее содержимое
    // текстового редактора

private:
    std::list<char>::iterator MoveIterator(std::list<char>::iterator it, size_t steps) const;

    std::list<char> data_;
    std::list<char> buffer_;
    std::list<char>::iterator cursor_;
};

Editor::Editor() : cursor_(data_.end()) {}

void Editor::Left() {
    if (cursor_ != data_.begin()) {
        cursor_--;
    }
}

void Editor::Right() {
    if (cursor_ != data_.end()) {
        cursor_++;
    }
}

void Editor::Insert(char token) {
    data_.insert(cursor_, token);
}

std::list<char>::iterator Editor::MoveIterator(std::list<char>::iterator it, size_t steps) const {
    while (steps > 0 && it != data_.end()) {
        ++it;
        --steps;
    }

    while (steps < 0 && it != data_.begin()) {
        --it;
        ++steps;
    }
    return it;
}

void Editor::Copy(size_t tokens) {
    auto end_pos = MoveIterator(cursor_, tokens);
    buffer_.assign(cursor_, end_pos);
}

void Editor::Cut(size_t tokens) {
    auto end_pos = MoveIterator(cursor_, tokens);
    buffer_.assign(cursor_, end_pos);
    cursor_ = data_.erase(cursor_, end_pos);
}

void Editor::Paste() {
    data_.insert(cursor_, buffer_.begin(), buffer_.end());
}

std::string Editor::GetText() const {
    return {data_.begin(), data_.end()};
}

void TypeText(Editor& editor, const string& text) {
    for(char c : text) {
        editor.Insert(c);
    }
}

void TestEditing() {
    {
        Editor editor;

        const size_t text_len = 12;
        const size_t first_part_len = 7;
        TypeText(editor, "hello, world");
        for(size_t i = 0; i < text_len; ++i) {
            editor.Left();
        }
        editor.Cut(first_part_len);
        for(size_t i = 0; i < text_len - first_part_len; ++i) {
            editor.Right();
        }

        TypeText(editor, ", ");
        editor.Paste();
        editor.Left();
        editor.Left();
        editor.Cut(3);

        ASSERT_EQUAL(editor.GetText(), "world, hello");
    }
    {
        Editor editor;

        TypeText(editor, "misprnit");
        editor.Left();
        editor.Left();
        editor.Left();
        editor.Cut(1);
        editor.Right();
        editor.Paste();

        ASSERT_EQUAL(editor.GetText(), "misprint");
    }
}

void TestReverse() {
    Editor editor;

    const string text = "esreveR";
    for(char c : text) {
        editor.Insert(c);
        editor.Left();
    }

    ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
    Editor editor;
    ASSERT_EQUAL(editor.GetText(), "");

    editor.Left();
    editor.Left();
    editor.Right();
    editor.Right();
    editor.Copy(0);
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
    Editor editor;

    editor.Paste();
    TypeText(editor, "example");
    editor.Left();
    editor.Left();
    editor.Paste();
    editor.Right();
    editor.Paste();
    editor.Copy(0);
    editor.Paste();
    editor.Left();
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestEditing);
    RUN_TEST(tr, TestReverse);
    RUN_TEST(tr, TestNoText);
    RUN_TEST(tr, TestEmptyBuffer);
    return 0;
}