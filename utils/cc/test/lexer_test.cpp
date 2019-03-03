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
}
