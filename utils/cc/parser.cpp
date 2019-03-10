#include "parser.hpp"
#include "instruction_opcode.hpp"
#include "register_opcode.hpp"

#include <algorithm>
#include <charconv>
#include <iostream>
#include <optional>

namespace esvm::cc
{
    const std::unordered_map<std::string_view, register_opcode> parser::m_registers = {
        { "r0", register_opcode::r0 },
        { "r1", register_opcode::r1 },
        { "r2", register_opcode::r2 },
        { "r3", register_opcode::r3 },
        { "r4", register_opcode::r4 },
        { "r5", register_opcode::r5 },
        { "r6", register_opcode::r6 },
        { "r7", register_opcode::r7 },
        { "r8", register_opcode::r8 },
        { "r9", register_opcode::r9 },
        { "r10", register_opcode::r10 },
        { "r11", register_opcode::r11 },
        { "r12", register_opcode::r12 },
        { "r13", register_opcode::r13 },
        { "r14", register_opcode::r14 },
        { "r15", register_opcode::r15 }
    };


    parser::parser(const std::vector<token> &tokens)
        : m_current{ std::cbegin(tokens) }
        , m_end{ std::cend(tokens) }
    {}

    std::vector<uint64_t> parser::parse() const
    {
        std::vector<uint64_t> result;

        while(!is_at_end())
        {
            const auto opcodes = get_next_opcodes();
        }

        return result;
    }

    bool parser::is_at_end() const
    {
        return m_current == m_end;
    }

    parser::opcodes_t parser::get_next_opcodes()
    {
        const auto curr = current();
        if(curr.str == "mov")
        {
            eat();
            if(is_current_register())
            {
                const auto reg = current();
                const auto reg_opcode = str_to_reg(reg.str);
                if(!reg_opcode)
                {
                    raise_error("Used unknown register: " + std::string{ reg.str });
                    return {};
                }

                eat(); // register
                eat(); // comma

                if(is_current_register())
                {
                    const auto reg2 = current();
                    const auto reg2_opcode = str_to_reg(reg.str);
                    if(!reg2_opcode)
                    {
                        raise_error("Used unknown register: " + std::string{ reg2.str });
                        return {};
                    }

                    eat(); // register

                    return make_opcodes(instruction_opcode::mov_reg_reg, reg_opcode, reg2_opcode);
                }
                else
                {
                    eat(); // [

                    const auto mem_ptr_tok = current();
                    const auto mem_ptr_str = mem_ptr_tok.str;
                    eat(); // ptr

                    uint64_t mem_ptr;
                    const auto [p, ec] = std::from_chars(mem_ptr_str.data(),
                                                         std::next(mem_ptr_str.data(), mem_ptr_str.size()),
                                                         mem_ptr);

                    if(ec != std::errc{})
                    {
                        raise_error("Malformed number: " + std::string{ mem_ptr_str });
                        return {};
                    }

                    eat(); // ]

                    return make_opcodes(instruction_opcode::mov_reg_mem, reg_opcode, mem_ptr);
                }
            }
        }
    }

    token parser::current() const
    {
        return *m_current;
    }

    void parser::eat()
    {
        std::advance(m_current, 1u);
    }

    bool parser::is_current_register() const
    {
        return m_registers.find(current().str) != std::cend(m_registers);
    }

    std::optional<register_opcode> parser::str_to_reg(std::string_view str) const
    {
        const auto found = m_registers.find(str);
        if(found == std::cend(m_registers))
        {
            return std::nullopt;
        }

        return found->second;
    }

    void parser::raise_error(const std::string &msg)
    {
        std::cout << msg << '\n';
    }

    template<typename... Opcodes>
    parser::opcodes_t parser::make_opcodes(Opcodes... opcodes) const
    {
        return opcodes_t{static_cast<uint64_t>(opcodes)... };
    }
}