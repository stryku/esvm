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
        bool is_current_one_char_token() const;
        bool is_current_identifier_token() const;
        bool is_current_number_token() const;

        bool is_identifier_char(char c) const;

        char current() const;
        const char& current_cref() const;

        token get_next_token();
        token get_one_char_token();
        token get_identifier_token();
        token get_number_token();

        template <typename Pred>
        token get_and_eat_token_for_predicate(token_type type, Pred&& pred);

        void eat(unsigned n = 1u);
        void eat_whitespaces();

    private:
        std::string::const_iterator m_char;
        std::string::const_iterator m_end;
    };
}

