#pragma once

#include "token.hpp"

#include <unordered_map>
#include <vector>

namespace esvm::cc
{
    enum class register_opcode : uint64_t ;

    class parser
    {
    public:
        using opcodes_t = std::vector<uint64_t>;

        explicit parser(const std::vector<token>& tokens);

        opcodes_t parse() const;

    private:
        bool is_at_end() const;
        bool is_current_register() const;

        token current() const;

        opcodes_t get_next_opcodes();

        void eat();

        std::optional<register_opcode> str_to_reg(std::string_view str) const;

        void raise_error(const std::string& msg);

        template <typename... Opcodes>
        opcodes_t make_opcodes(Opcodes... opcodes) const;



    private:
        static const std::unordered_map<std::string_view, register_opcode> m_registers;

        std::vector<token>::const_iterator m_current;
        std::vector<token>::const_iterator m_end;
    };
}

