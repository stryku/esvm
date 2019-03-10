#include "lexer.hpp"

#include <assert.h>
#include <algorithm>

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
            eat_whitespaces();
            if(is_at_end())
            {
                break;
            }

            const auto tok = get_next_token();
            tokens.emplace_back(tok);
        }

        return tokens;
    }

    bool lexer::is_at_end() const
    {
        return m_char == m_end;
    }

    void lexer::eat(unsigned n)
    {
        std::advance(m_char, n);
    }

    void lexer::eat_whitespaces()
    {
        const auto begin = m_char;
        const auto pred = [](const char c)
        {
            return !std::isspace(c);
        };
        const auto found = std::find_if(begin, m_end, pred);
        const auto whitespaces_count = std::distance(begin, found);
        if(whitespaces_count > 0)
        {
            eat(whitespaces_count);
        }
    }

    token lexer::get_next_token()
    {
        if(is_current_one_char_token())
        {
            return get_one_char_token();
        }
        if(is_current_identifier_token())
        {
            return get_identifier_token();
        }
        if(is_current_number_token())
        {
            return get_number_token();
        }
    }

    token lexer::get_one_char_token()
    {
        const auto type = [c = current()]
        {
            switch (c)
            {
                case ',': return token_type::comma;
                case '[': return token_type::open_square;
                case ']': return token_type::close_square;
                case ':': return token_type::colon;

                default:
                    assert(false && "Unexpected one char token");
            }
        }();

        const auto str = std::string_view{&current_cref(), 1};
        eat();

        return { type, str };
    }

    bool lexer::is_current_one_char_token() const
    {
        const auto chars = { ',', '[',']', ':' };
        return !is_at_end()
            && std::any_of(std::cbegin(chars), std::cend(chars),
                [current = current()](const char c) { return current == c; });
    }

    bool lexer::is_current_identifier_token() const
    {
        return !is_at_end() && is_identifier_char(current());
    }

    char lexer::current() const
    {
        return *m_char;
    }

    const char &lexer::current_cref() const
    {
        return *m_char;
    }

    token lexer::get_identifier_token()
    {
        const auto pred = [this](const char c)
        {
            return !is_identifier_char(c) && !std::isdigit(c);
        };
        return get_and_eat_token_for_predicate(token_type::identifier, pred);
    }

    bool lexer::is_current_number_token() const
    {
        return !is_at_end() && std::isdigit(current());
    }

    token lexer::get_number_token()
    {
        const auto pred = [this](const char c)
        {
            return !std::isdigit(c);
        };
        return get_and_eat_token_for_predicate(token_type::number, pred);
    }

    bool lexer::is_identifier_char(char c) const
    {
        return std::isalpha(c) || c == '_';
    }

    template<typename Pred>
    token lexer::get_and_eat_token_for_predicate(token_type type, Pred&& pred)
    {
        const auto begin = m_char;
        const auto found = std::find_if(begin, m_end, pred);
        const auto str = std::string_view{ &current_cref(),
                                           static_cast<std::string_view::size_type>(std::distance(begin, found)) };

        eat(str.size());
        return { type, str };
    }
}
