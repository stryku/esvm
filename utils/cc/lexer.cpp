#include "lexer.hpp"

namespace esvm::cc
{
    lexer::lexer(const std::string &source)
        : m_char{ source.cbegin() }
        , m_end{ source.cend() }
    {}

    std::vector<token> lexer::lex()
    {
        std::vector<token> tokens;

        while(!is_at_end())
        {
            const auto tok = get_next_token();
        }

        return tokens;
    }

    bool lexer::is_at_end() const
    {
        return m_char == m_end;
    }

    void lexer::eat()
    {
        std::advance(m_char, 1u);
    }

    token lexer::get_next_token()
    {
        switch (*m_char)
        {
            case ',':
            case '[':
            case ']':
            case ':':
                return get_one_char_token(*m_char);




        }
    }

    token lexer::get_one_char_token(char c)
    {
        const auto type = [c]
        {
            switch (c)
            {
                case ',': return token_type::comma;
                case '[': return token_type::open_square;
                case ']': return token_type::close_square;
                case ':': return token_type::semicolon;
            }
        }();

        const auto str = std::string_view{&(*m_char), 1};
        eat();

        return {type, str};
    }
}

