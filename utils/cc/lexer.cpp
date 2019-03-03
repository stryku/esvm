#include "lexer.hpp"

namespace esvm::cc
{
    lexer::lexer(const std::string &source)
        : m_char{ source.begin() }
    {}

    std::vector<std::string_view> lexer::lex()
    {
        return {};
    }
}

