#include "lexer.hpp"

#include <gmock/gmock.h>

namespace esvm::cc::test
{
    using ::testing::Eq;
    using ::testing::IsEmpty;

    TEST(LexerTest, EmptySource_GetEmptyTokens)
    {
        const auto source = "";
        const auto result_tokens = lexer{source}.lex();
        EXPECT_THAT(result_tokens, IsEmpty());
    }

    struct LexerTestState
    {
        std::string source;
        std::vector<token> expected_tokens;
    };

    namespace one_char_token
    {
        struct Lex_OneCharSource : public testing::Test, testing::WithParamInterface<LexerTestState>
        {};

        TEST_P(Lex_OneCharSource, GetOneCharToken)
        {
            const auto source = GetParam().source;
            const auto& expected_tokens = GetParam().expected_tokens;

            const auto tokens = lexer{source}.lex();

            EXPECT_THAT(tokens, Eq(expected_tokens));
        }

        const auto values = testing::Values(
                LexerTestState{",", { token{ token_type::comma, "," } } },
                LexerTestState{":", { token{ token_type::colon, ":" } } },
                LexerTestState{ "[", { token{ token_type::open_square, "[" } } },
                LexerTestState{ "]", { token{ token_type::close_square, "]" } } } );
        INSTANTIATE_TEST_CASE_P(Lexer, Lex_OneCharSource, values);
    }

    namespace multiple_char_token
    {
        struct Lex_MultipleCharSource : public testing::Test, testing::WithParamInterface<LexerTestState>
        {};

        TEST_P(Lex_MultipleCharSource, GetExpectedToken)
        {
            const auto source = GetParam().source;
            const auto expected_tokens = GetParam().expected_tokens;

            const auto tokens = lexer{source}.lex();

            EXPECT_THAT(tokens, Eq(expected_tokens));
        }

        const auto values = testing::Values(
                LexerTestState{"_", { token{ token_type::identifier, "_" } } },
                LexerTestState{"foo", { token{ token_type::identifier, "foo" } } },
                LexerTestState{ "foo123", { token{ token_type::identifier, "foo123" } } },

                LexerTestState{ "1", { token{ token_type::number, "1" } } },
                LexerTestState{ "01234567890", { token{ token_type::number, "0123456789" } } } );
        INSTANTIATE_TEST_CASE_P(Lexer, Lex_MultipleCharSource, values);
    }

    TEST(Lexer, Lex_MultipleTokensSource_SkipesWhitespaces)
    {
        const auto source = "  mov, [\tr10\n\n   ] :   231";
        const auto expected_tokens = std::vector<token>{
                token{token_type::identifier, "mov" },
                token{token_type::comma, "," },
                token{token_type::open_square, "[" },
                token{token_type::identifier, "r10" },
                token{token_type::close_square, "]" },
                token{token_type::colon, ":" },
                token{token_type::number, "231" }
        };

        const auto tokens = lexer{source}.lex();

        EXPECT_THAT(tokens, Eq(expected_tokens));
    }
}
