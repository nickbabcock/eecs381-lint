#include "gtest/gtest.h"
#include <stdlib.h>
#include <string>
#include <iostream>

const char * veraFilePath = "vera/build/src/vera++";

int unsignedTest(const char*);
int floatTest(const char*);
int disallowedFunctions(const char*);
int meBeforeYou(const char*);
int nullComparison(const char*);
int noTrueFalse(const char*);
int capitalizeMacros(const char*);
int constNames(const char*);
int upperCaseDefinitions(const char*);
int enumName(const char*);
int typedefName(const char*);
int enumValueName(const char*);
int leadingUnderscore(const char*);
int initializeStringLiteral(const char*);
int enumDefaultValues(const char*);
int test(const char*, const char*);

TEST(unsigned, fails)
{
    const char * code = R"( int main() { return (unsigned int)0; } )";
    EXPECT_EQ(1, unsignedTest(code));
}

TEST(unsigned, works)
{
    const char * code = R"(int main() { return 0; } )";
    EXPECT_EQ(0, unsignedTest(code));
}

TEST(float, fails)
{
    const char * code = R"(int main() { return (float)0; })";
    EXPECT_EQ(1, floatTest(code));
}

TEST(float, works)
{
    const char * code = R"(int main() { return (double)0; })";
    EXPECT_EQ(0, floatTest(code));
}

TEST(disallowedFunctions, fails)
{
    const char * code = R"(
        int main() {
            calloc(10, 10);
        })";
    EXPECT_EQ(1, disallowedFunctions(code));
}

TEST(disallowedFunctions, works)
{
    const char * code = R"(
        int main() {
            // calloc(10, 10);
        })";
    EXPECT_EQ(0, disallowedFunctions(code));
}

TEST(meBeforeYou, works)
{
    const char * code = R"(
        #include "me.h"
        #include "you.h"
        #include <std>
        #include <foo>
        )";
    EXPECT_EQ(0, meBeforeYou(code));
}

TEST(meBeforeYou, fails)
{
    const char * code = R"(
        #include "me.h"
        #include <std>
        #include "you.h"
        )";
    EXPECT_EQ(1, meBeforeYou(code));
}

TEST(meBeforeYou, fieldTest)
{
    const char* code = R"(#include "problem1.h")";
    EXPECT_EQ(0, meBeforeYou(code));
}

TEST(nullComparison, works)
{
    const char * code = R"( if (!f) { })";
    EXPECT_EQ(0, nullComparison(code));
}

TEST(nullComparison, failsWithZero)
{
    const char * code = R"( if (f == 0) { })";
    EXPECT_EQ(1, nullComparison(code));
}

TEST(nullComparison, failsWithNull)
{
    const char * code = R"( if (f == NULL) { })";
    EXPECT_EQ(1, nullComparison(code));
}

TEST(noTrueFalse, failTrue)
{
    const char * code = R"(#define TRUE 1)";
    EXPECT_EQ(1, noTrueFalse(code));
}

TEST(noTrueFalse, failFalse)
{
    const char* code = R"(#define FALSE 0)";
    EXPECT_EQ(1, noTrueFalse(code));
}

TEST(capitalizeMacros, works)
{
    const char* code = R"(#define TRUE 1)";
    EXPECT_EQ(0, capitalizeMacros(code));
}

TEST(capitalizeMacros, fails)
{
    const char* code = R"(#define abc 1)";
    EXPECT_EQ(1, capitalizeMacros(code));
}

TEST(constNames, leadingK)
{
    const char* code = R"(const int kScreen_h_size = 1024;)";
    EXPECT_EQ(0, constNames(code));
}

TEST(constNames, customType)
{
	const char* code = R"(const MyType_t yup_c = 10;)";
	EXPECT_EQ(0, constNames(code));
}

TEST(constNames, trailingE)
{
    const char* code = R"(const int screen_h_size_c = 1024;)";
    EXPECT_EQ(0, constNames(code));
}

TEST(constNames, fails)
{
    const char* code = R"(const int whatever = 10;)";
    EXPECT_EQ(1, constNames(code));
}

TEST(upperCaseDefinitions, works)
{
    const char* code = R"(struct Thing)";
    EXPECT_EQ(0, upperCaseDefinitions(code));
}

TEST(upperCaseDefinitions, fails) 
{
    const char* code = R"(struct thing)";
    EXPECT_EQ(1, upperCaseDefinitions(code));
}

TEST(enumName, works)
{
    const char* code = R"(enum Fruits_e)";
    EXPECT_EQ(0, enumName(code));
}

TEST(enumName, fails)
{
    const char* code = R"(enum Fruits)";
    EXPECT_EQ(1, enumName(code));
}

TEST(enumName, fails2)
{
    const char* code = R"(enum fruits_e)";
    EXPECT_EQ(1, enumName(code));
}

TEST(typedefName, works)
{
    const char* code = R"(typedef struct Thing * Thing_ptr_t;)";
    EXPECT_EQ(0, typedefName(code));
}

TEST(typedefName, reassignInt)
{
    const char* code = R"(typedef unsigned int Integral_base_t;)";
    EXPECT_EQ(0, typedefName(code));
}

TEST(typedefName, fails)
{
    const char* code = R"(typedef struct Thing * Thing_ptr)";
    EXPECT_EQ(1, typedefName(code));
}

TEST(enumValueName, fails) 
{
    const char* code = R"(enum boom { BOOM, Boom2 })";
    EXPECT_EQ(1, enumValueName(code));
}

TEST(enumValueName, works)
{
    const char* code = R"(enum Fruit { APPLE, ORANGE })";
    EXPECT_EQ(0, enumValueName(code));
}

TEST(leadingUnderscore, intVariablefail)
{
    const char* code = R"(int _a = 5;)";
    EXPECT_EQ(1, leadingUnderscore(code));
}

TEST(leadingUnderscore, floatFunctionFails)
{
    const char* code = R"-(float _calculate();)-";
    EXPECT_EQ(1, leadingUnderscore(code));
}

TEST(leadingUnderscore, defineFails)
{
    const char* code = R"(#define _waa 1)";
    EXPECT_EQ(1, leadingUnderscore(code));
}

TEST(leadingUnderscore, works)
{
    const char* code = R"(int i = 0;)";
    EXPECT_EQ(0, leadingUnderscore(code));
}

TEST(stringLiterals, fails)
{
    const char* code = R"(const char message[] = "Goodbye, cruel world!";)";
    EXPECT_EQ(1, initializeStringLiteral(code));
}

TEST(stringLiterals, works)
{
    const char* code = R"(const char * const message = "Goodbye, cruel world!";)";
    EXPECT_EQ(0, initializeStringLiteral(code));
}

TEST(enumDefaultValues, fails)
{
    const char* code = R"(enum Fruit_e {APPLE = 0, ORANGE, PEAR, BANANA};)";
    EXPECT_EQ(1, enumDefaultValues(code));
}

TEST(enumDefaultValues, fails2)
{
    const char* code = R"(enum Fruit_e {APPLE = 3, ORANGE, PEAR, BANANA};)";
    EXPECT_EQ(1, enumDefaultValues(code));
}

TEST(enumDefaultValues, works)
{
    const char* code = R"(enum Fruit_e {APPLE, ORANGE, PEAR, BANANA};)";
    EXPECT_EQ(0, enumDefaultValues(code));
}

int unsignedTest(const char* code)
{
    return test("unsigned", code);
}

int floatTest(const char* code)
{
    return test("float", code);
}

int disallowedFunctions(const char* code)
{
    return test("disallowedFunctions", code);
}

int meBeforeYou(const char* code)
{
    return test("meBeforeYou", code);
}

int nullComparison(const char* code)
{
    return test("nullComparison", code);
}

int noTrueFalse(const char* code)
{
    return test("noTrueFalse", code);
}

int capitalizeMacros(const char* code)
{
    return test("capitalizeMacros", code);
}

int constNames(const char* code)
{
    return test("constNames", code);
}

int upperCaseDefinitions(const char* code)
{
    return test("upperCaseDefinitions", code);
}

int enumName(const char* code)
{
    return test("enumName", code);
}

int typedefName(const char* code)
{
    return test("typedefName", code);
}

int enumValueName(const char* code)
{
    return test("enumValueName", code);
}

int leadingUnderscore(const char* code)
{
    return test("leadingUnderscore", code);
}

int initializeStringLiteral(const char* code)
{
    return test("stringLiterals", code);
}

int enumDefaultValues(const char* code)
{
    return test("enumDefaultValues", code);
}

int test(const char* rule, const char* code)
{
    std::string str;
    str += veraFilePath;
    str += " --root . --quiet ";
    str += " --rule ";
    str += rule;
    str += " --error - ";

    FILE* pipe = popen(str.c_str(), "w");

    code = (std::string(code) + '\n').c_str();
    fputs(code, pipe);
    return pclose(pipe) >> 8;
}
