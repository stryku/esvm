#pragma once

#include "token.hpp"

#include <vector>
#include <string>
#include <string_view>

namespace esvm::cc
{
    class lexer
    {
    public:
        explicit lexer(const std::string& source);

        std::vector<token> lex();

    private:
        bool is_at_end() const;

        token get_next_token();
        token get_one_char_token(char c);

        void eat();

    private:
        std::string::const_iterator m_char;
        std::string::const_iterator m_end;
    };
}

