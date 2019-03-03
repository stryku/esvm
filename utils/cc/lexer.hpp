#pragma once

#include <vector>
#include <string>
#include <string_view>

namespace esvm::cc
{
    class lexer
    {
    public:
        explicit lexer(const std::string& source);

        std::vector<std::string_view> lex();

    private:
        std::string::const_iterator m_char;
    };
}

