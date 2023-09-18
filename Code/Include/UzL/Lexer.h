#pragma once

#include "uzl/token.h"
#include <unordered_map>

namespace uzl
{

	const std::unordered_map<std::string, TokenKind> keywords =
	{
		{ "func", TK_KwFunc }, { "const", TK_KwConst }, { "true", TK_KwTrue }, { "false", TK_KwFalse },
		{ "for", TK_KwFor }, { "while", TK_KwWhile }, { "loop", TK_KwLoop }, { "continue", TK_KwContinue },
		{ "switch", TK_KwSwitch }, { "case", TK_KwCase }, { "fallthrough", TK_KwFallthrough },
		{ "default", TK_KwDefault }, { "let", TK_KwVar }, { "type", TK_KwType }
	};

	class Lexer
	{
	public:

		Lexer() = default;

		std::vector<Token> tokenize(std::string_view source, std::string_view file_name);

	private:

		std::string_view m_source{};
		std::shared_ptr<std::string> m_file_name { nullptr };

		u64 m_line{ 0 };
		u64 m_column{ 0 };
		u64 m_index{ 0 };

		std::vector<Token> m_tokens;

		void nextChar()
		{
			m_column++;
			m_index++;
		}

		SourceLocation currentSourceLocation() const
		{
			return { m_file_name, m_line, m_column };
		}

		Token newToken(TokenKind kind, const std::string& lexeme) const
		{
			return { kind, lexeme, currentSourceLocation() };
		}

		static Token newToken(TokenKind kind, const std::string& lexeme, const SourceLocation& location)
		{
			return { kind, lexeme, location };
		}

		bool nextToken();

		char peek() const { return m_source.length() <= m_index ? '\0' : m_source[m_index]; }
		char peek(i64 offset) const;
		static bool isWhiteSpace(char c);
		bool isNumber(char c) const;
		static bool isIdentifierChar(char c);

		void parseNumber();
		void parseIdentifier();
		void parseString();

		bool advanceWith(TokenKind kind, const std::string& lexeme);
	};

}