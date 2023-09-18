#include "gtest/gtest.h"
#include <uzl/lexer.h>

TEST(Lexer, EmptySource)
{
	uzl::Lexer lexer;
	const auto tokens = lexer.tokenize("", "empty.ul");

	ASSERT_TRUE(tokens.size() == 1 && tokens[0].kind == uzl::TK_Eof);
}

TEST(Lexer, Numbers)
{
	uzl::Lexer lexer;
	const auto tokens = lexer.tokenize("123 0x8 0b111", "numbers.ul");

	ASSERT_TRUE(tokens.size() == 4);
	ASSERT_TRUE(tokens[0].kind == uzl::TK_Number && tokens[0].lexeme == "123");
	ASSERT_TRUE(tokens[1].kind == uzl::TK_Number && tokens[1].lexeme == "x8");
	ASSERT_TRUE(tokens[2].kind == uzl::TK_Number && tokens[2].lexeme == "b111");
}

TEST(Lexer, Keywords)
{
	uzl::Lexer lexer;
	const auto tokens = lexer.tokenize(
		R"(func type myvar for case let bruh
const true false while loop continue switch fallthrough default)", "keywords.ul");

	ASSERT_TRUE(tokens.size() == 17);
	ASSERT_TRUE(tokens[0].kind == uzl::TK_KwFunc);
	ASSERT_TRUE(tokens[1].kind == uzl::TK_KwType);
	ASSERT_TRUE(tokens[2].kind == uzl::TK_Identifier);
	ASSERT_TRUE(tokens[3].kind == uzl::TK_KwFor);
	ASSERT_TRUE(tokens[4].kind == uzl::TK_KwCase);
	ASSERT_TRUE(tokens[5].kind == uzl::TK_KwVar);
	ASSERT_TRUE(tokens[6].kind == uzl::TK_Identifier);
	ASSERT_TRUE(tokens[7].kind == uzl::TK_KwConst);
	ASSERT_TRUE(tokens[8].kind == uzl::TK_KwTrue);
	ASSERT_TRUE(tokens[9].kind == uzl::TK_KwFalse);
	ASSERT_TRUE(tokens[10].kind == uzl::TK_KwWhile);
	ASSERT_TRUE(tokens[11].kind == uzl::TK_KwLoop);
	ASSERT_TRUE(tokens[12].kind == uzl::TK_KwContinue);
	ASSERT_TRUE(tokens[13].kind == uzl::TK_KwSwitch);
	ASSERT_TRUE(tokens[14].kind == uzl::TK_KwFallthrough);
	ASSERT_TRUE(tokens[15].kind == uzl::TK_KwDefault);
}

TEST(Lexer, SourceLocations)
{
	uzl::Lexer lexer;
	const auto file_name = "locations.ul";
	const auto tokens = lexer.tokenize("first\n    second\n third_line", file_name);

	ASSERT_TRUE(tokens.size() == 4);
	ASSERT_TRUE(tokens[0].kind == uzl::TK_Identifier
		&& tokens[0].location.line == 1 && tokens[0].location.column == 1
		&& *tokens[0].location.file_name == file_name);
	ASSERT_TRUE(tokens[1].kind == uzl::TK_Identifier
		&& tokens[1].location.line == 2 && tokens[1].location.column == 5
		&& *tokens[1].location.file_name == file_name);
	ASSERT_TRUE(tokens[2].kind == uzl::TK_Identifier
		&& tokens[2].location.line == 3 && tokens[2].location.column == 2
		&& *tokens[2].location.file_name == file_name);
}

TEST(Lexer, Strings)
{
	uzl::Lexer lexer;
	const auto tokens = lexer.tokenize("\"this is a string\" this_is_not_a_string \"I'm a string\"", "strings.ul");

	ASSERT_TRUE(tokens.size() == 4);
	ASSERT_TRUE(tokens[0].kind == uzl::TK_String && tokens[0].lexeme == "this is a string");
	ASSERT_TRUE(tokens[1].kind == uzl::TK_Identifier && tokens[1].lexeme == "this_is_not_a_string");
	ASSERT_TRUE(tokens[2].kind == uzl::TK_String && tokens[2].lexeme == "I'm a string");
}

TEST(Lexer, RealWorldExample)
{
	uzl::Lexer lexer;
	const auto source =
		R"(
func add(a, b) -> a + b;
)";

	const auto tokens = lexer.tokenize(source, "rwe.ul");

	ASSERT_TRUE(tokens.size() == 13);
	ASSERT_TRUE(tokens[0].kind == uzl::TK_KwFunc);
	ASSERT_TRUE(tokens[1].kind == uzl::TK_Identifier && tokens[1].lexeme == "add");
	ASSERT_TRUE(tokens[2].kind == uzl::TK_LBracket);
	ASSERT_TRUE(tokens[3].kind == uzl::TK_Identifier && tokens[3].lexeme == "a");
	ASSERT_TRUE(tokens[4].kind == uzl::TK_Comma);
	ASSERT_TRUE(tokens[5].kind == uzl::TK_Identifier && tokens[5].lexeme == "b");
	ASSERT_TRUE(tokens[6].kind == uzl::TK_RBracket);
	ASSERT_TRUE(tokens[7].kind == uzl::TK_RArrow);
	ASSERT_TRUE(tokens[8].kind == uzl::TK_Identifier && tokens[8].lexeme == "a");
	ASSERT_TRUE(tokens[9].kind == uzl::TK_Add);
	ASSERT_TRUE(tokens[10].kind == uzl::TK_Identifier && tokens[10].lexeme == "b");
	ASSERT_TRUE(tokens[11].kind == uzl::TK_SemiColon);
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);

	// real -> mantisa + порядок
	// real = mantisa * 10^порядок
	// десятичная константа - набор цифр, первая из которых не 0

	return RUN_ALL_TESTS();
}