#include "c-ini.h"
#include "test_fixed_str.h"

#include "gmock/gmock.h"

#define NAME fixed_str

SECTION("fixed")
struct fixed
{
    char fixed_str[16];
};

struct NAME : testing::Test
{
    void SetUp() override { fixed_init(&s); }
    void TearDown() override { fixed_deinit(&s); }

    struct fixed s;
};

using namespace testing;

TEST_F(NAME, simple)
{
    const char* ini = "[fixed]\nfixed_str = \"Hello\"\n";
    ASSERT_THAT(fixed_parse(&s, "<stdin>", ini, strlen(ini)), Eq(0));
    EXPECT_THAT(s.fixed_str, StrEq("Hello"));
}

TEST_F(NAME, str_empty)
{
    const char* ini = "[fixed]\nfixed_str = \"\"\n";
    ASSERT_THAT(fixed_parse(&s, "<stdin>", ini, strlen(ini)), Eq(0));
    EXPECT_THAT(s.fixed_str, StrEq(""));
}

TEST_F(NAME, str_too_long)
{
    const char* ini = "[fixed]\nfixed_str = \"This string is too long\"\n";
    ASSERT_THAT(fixed_parse(&s, "<stdin>", ini, strlen(ini)), Eq(-1));
    EXPECT_THAT(s.fixed_str[0], Eq('\0')); // Should not have changed
}

TEST_F(NAME, missing_string)
{
    const char* ini = "[fixed]\n";
    ASSERT_THAT(fixed_parse(&s, "<stdin>", ini, strlen(ini)), Eq(0));
    EXPECT_THAT(s.fixed_str[0], Eq('\0')); // Should not have changed
}

TEST_F(NAME, invalid)
{
    const char* ini = "[fixed]\nfixed_str = \"Invalid string\n";
    ASSERT_THAT(fixed_parse(&s, "<stdin>", ini, strlen(ini)), Eq(-1));
    EXPECT_THAT(s.fixed_str[0], Eq('\0')); // Should not have changed
}

TEST_F(NAME, set_str_twice)
{
    const char* ini = "[fixed]\nfixed_str = \"First\"\n";
    ASSERT_THAT(fixed_parse(&s, "<stdin>", ini, strlen(ini)), Eq(0));
    EXPECT_THAT(s.fixed_str, StrEq("First"));

    ini = "[fixed]\nfixed_str = \"Second\"\n";
    ASSERT_THAT(fixed_parse(&s, "<stdin>", ini, strlen(ini)), Eq(0));
    EXPECT_THAT(s.fixed_str, StrEq("Second"));
}
