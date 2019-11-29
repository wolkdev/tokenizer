
#include "tokenizer.hpp"
#include <iostream>

int main(int argc, char const *argv[])
{
    const char* str =
        "class my_class\n"
        "{\n"
        "    private:\n"
        "    int* iptr = nullptr;\n"
        "    std::string str = \"\";\n"
        "\n"
        "    my_class(std::string&& _str);\n"
        "}";

    // tokenizer initialization

    tokenizer tok;

    tok.set_dropped_delimiters(" \t\r\n");

    tok.add_kept_delimiter("=");
    tok.add_kept_delimiter("*");
    tok.add_kept_delimiter("{");
    tok.add_kept_delimiter("}");
    tok.add_kept_delimiter("(");
    tok.add_kept_delimiter(")");
    tok.add_kept_delimiter(";");
    tok.add_kept_delimiter("&");
    tok.add_kept_delimiter("&&");
    tok.add_kept_delimiter(":");
    tok.add_kept_delimiter("::");
    tok.add_kept_delimiter("\"");

    // tokenize

    tok.start(str);

    while (!tok.finished())
    {
        const std::string& token = tok.next();

        std::cout << token << "\n";
    }

    return 0;
}
