#include "c-ini.h"
#include "test_dynamic_str.h"

#include "gmock/gmock.h"

#define NAME dynamic_str

SECTION("dyn")
struct dyn
{
    char* dyn;
};

struct NAME : testing::Test
{
    void SetUp() override { dyn_init(&s); }
    void TearDown() override { dyn_deinit(&s); }

    struct dyn s;
};

using namespace testing;

TEST_F(NAME, simple)
{
    const char* ini = "[dyn]\ndyn = \"Hello\"\n";
    ASSERT_THAT(dyn_parse(&s, "<stdin>", ini, strlen(ini)), Eq(0));
    EXPECT_THAT(s.dyn, StrEq("Hello"));
}

TEST_F(NAME, str_empty)
{
    const char* ini = "[dyn]\ndyn = \"\"\n";
    ASSERT_THAT(dyn_parse(&s, "<stdin>", ini, strlen(ini)), Eq(0));
    EXPECT_THAT(s.dyn, StrEq(""));
}

TEST_F(NAME, missing_string)
{
    const char* ini = "[dyn]\n";
    ASSERT_THAT(dyn_parse(&s, "<stdin>", ini, strlen(ini)), Eq(0));
    EXPECT_THAT(s.dyn[0], Eq('\0')); // Should not have changed
}

TEST_F(NAME, invalid)
{
    const char* ini = "[dyn]\ndyn = \"Invalid string\n";
    ASSERT_THAT(dyn_parse(&s, "<stdin>", ini, strlen(ini)), Eq(-1));
    EXPECT_THAT(s.dyn[0], Eq('\0')); // Should not have changed
}

TEST_F(NAME, set_str_twice)
{
    const char* ini = "[dyn]\ndyn = \"First\"\n";
    ASSERT_THAT(dyn_parse(&s, "<stdin>", ini, strlen(ini)), Eq(0));
    EXPECT_THAT(s.dyn, StrEq("First"));

    ini = "[dyn]\ndyn = \"Second\"\n";
    ASSERT_THAT(dyn_parse(&s, "<stdin>", ini, strlen(ini)), Eq(0));
    EXPECT_THAT(s.dyn, StrEq("Second"));
}
