#pragma once

#include <string_view>

namespace esvm::cc
{
    enum class token_type
    {
        undef,
        comma,
        semicolon,
        open_square,
        close_square,
        identifier,
        number
    };

    struct token
    {
        token_type type;
        std::string_view str;
    };
}
