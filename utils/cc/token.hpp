#pragma once

#include <string_view>

namespace esvm::cc
{
    enum class token_type
    {
        undef,
        comma,
        colon,
        open_square,
        close_square,
        identifier,
        number
    };

    struct token
    {
        token_type type;
        std::string_view str;

        bool operator==(const token& rhs) const
        {
            return type == rhs.type && str == rhs.str;
        }

        bool operator!=(const token& rhs) const
        {
            return !(*this == rhs);
        }
    };
}
