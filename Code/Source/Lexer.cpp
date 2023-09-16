#include "uzl/lexer.h"
#include "log.h"
#include <string>
#include <algorithm>

namespace uzl
{
	std::vector<Token> Lexer::tokenize(std::string_view source, std::string_view file_name)
	{
		m_tokens.clear();
		m_source = source;
		m_file_name = std::make_shared<std::string>(file_name.data());
		m_index = 0;

		while (nextToken());

		m_tokens.push_back(newToken(TK_Eof, "End Of File"));

		return m_tokens;
	}

	bool Lexer::nextToken()
	{
		while (m_index < m_source.length())
		{
			char c = peek();

			while (isWhiteSpace(c))
			{
				nextChar();

				if (c == '\n') {
					m_line++;
					m_column = 1;
				}

				if (m_index >= m_source.length()) return false;
				c = peek();
			}

			if (c == '/' && peek(1) == '/')
			{
				while (m_index < m_source.length() && peek() != '\n')
					m_index++;

				m_line++;
				m_column = 1;
				m_index++;
				continue;
			}

			if (isNumber(c)) return parseNumber(), true;
			if (isIdentifierChar(c)) return parseIdentifier(), true;
			if (c == '"') return parseString(), true;

			switch (c)
			{
			case ';':
				return advanceWith(TK_SemiColon, ";");
			case ',':
				return advanceWith(TK_Comma, ",");
			case '.':
				return advanceWith(TK_Period, ".");
			case ':':
				return peek(1) == ':' ? advanceWith(TK_ScopeRes, "::")
					: advanceWith(TK_Colon, ":");

			case '<':
				if (peek(1) == '<')
				{
					if (peek(2) == '=') return advanceWith(TK_BinLSA, "<<=");
					return advanceWith(TK_BinLS, "<<");
				}
				if (peek(1) == '=')
					return advanceWith(TK_LTE, "<=");
				return advanceWith(TK_LT, "<");

			case '>':
				if (peek(1) == '>')
				{
					if (peek(2) == '=') return advanceWith(TK_BinRSA, ">>=");
					return advanceWith(TK_BinRS, ">>");
				}
				if (peek(1) == '=')
					return advanceWith(TK_GTE, ">=");
				return advanceWith(TK_GT, ">");

			case '=':
				return peek(1) == '=' ? advanceWith(TK_Equals, "==")
					: advanceWith(TK_Assign, "=");

			case '!':
				return peek(1) == '=' ? advanceWith(TK_NotEquals, "!=")
					: advanceWith(TK_Invert, "!");

			case '&':
				return peek(1) == '&' ? advanceWith(TK_And, "&&")
					: peek(1) == '=' ? advanceWith(TK_BinAndA, "&=")
					: advanceWith(TK_Ampersand, "&");

			case '|':
				return peek(1) == '|' ? advanceWith(TK_Or, "||")
					: peek(1) == '=' ? advanceWith(TK_BinOrA, "|=")
					: advanceWith(TK_Pipe, "|");

			case '^':
				return peek(1) == '=' ? advanceWith(TK_BinXorA, "^=")
					: advanceWith(TK_BinXor, "^");

			case '~':
				return peek(1) == '=' ? advanceWith(TK_BinInvA, "~=")
					: advanceWith(TK_BinInv, "~");

			case '%':
				return peek(1) == '=' ? advanceWith(TK_PercentA, "%=")
					: advanceWith(TK_Percent, "%");

			case '+':
				return peek(1) == '=' ? advanceWith(TK_AddA, "+=")
					: peek(1) == '+' ? advanceWith(TK_DoubleInc, "++")
					: advanceWith(TK_Add, "+");
			case '-':
				return peek(1) == '=' ? advanceWith(TK_SubA, "-=")
					: peek(1) == '>' ? advanceWith(TK_Arrow, "->")
					: peek(1) == '-' ? advanceWith(TK_DoubleDec, "--")
					: advanceWith(TK_Sub, "-");
			case '*':
				return peek(1) == '=' ? advanceWith(TK_MulA, "*=")
					: advanceWith(TK_Asterisk, "*");
			case '/':
				return peek(1) == '=' ? advanceWith(TK_DivA, "/=") : advanceWith(TK_Div, "/");

			case '(':
				return advanceWith(TK_LBracket, "(");
			case ')':
				return advanceWith(TK_RBracket, ")");
			case '{':
				return advanceWith(TK_LBrace, "{");
			case '}':
				return advanceWith(TK_RBrace, "}");
			case '[':
				return advanceWith(TK_LSquare, "[");
			case ']':
				return advanceWith(TK_RSquare, "]");
			default:
				break;
			}

			logError("[Lexer] Unknown character: `{}` at index {}", c, m_index++);

		}

		return false;
	}

	char Lexer::peek(i64 offset) const
	{
		return m_index + offset < m_source.length() ? m_source[m_index + offset] : '\0';
	}

	bool Lexer::isWhiteSpace(char c)
	{
		return c == ' ' || c == '\n' || c == '\r' || c == '\t';
	}

	auto Lexer::isNumber(char c) const -> bool
	{
		return (c >= '0' && c <= '9') || (peek() == '.' && peek(1) >= '0' && peek(1) <= '9');
	}

	bool Lexer::isIdentifierChar(char c)
	{
		return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') ||
			c == '_' || static_cast<unsigned char>(c) >= 0x80;
	}

	void Lexer::parseNumber()
	{
		std::string num;
		const auto		location = currentSourceLocation();

		if (peek() == '0')
		{
			char type = peek(1);
			type += type <= 90 ? 97 - 65 : 0;

			const std::vector number_bases = { 'x', 'o', 'b' };

			if (std::find(number_bases.begin(), number_bases.end(), type) != number_bases.end())
			{
				num += type;
				nextChar();
				nextChar();

				switch (type)
				{
				case 'x':
					while ((peek() >= '0' && peek() <= '9') ||
						(peek() >= 'a' && peek() <= 'f') ||
						(peek() >= 'A' && peek() <= 'F'))
					{
						num += peek();
						nextChar();
					}
					break;

				case 'o':
					while (peek() >= '0' && peek() <= '7')
					{
						num += peek();
						nextChar();
					}
					break;

				case 'b':
				default:
					while (peek() == '0' || peek() == '1')
					{
						num += peek();
						nextChar();
					}
				}
			}
			else
			{
				while (isNumber(peek()))
				{
					num += peek();
					nextChar();
				}
			}
		}
		else
		{
			while (isNumber(peek()))
			{
				num += peek();
				nextChar();
			}
		}

		m_tokens.push_back(newToken(TK_Number, num, location));
	}

	void Lexer::parseIdentifier()
	{
		std::string ident;
		const auto		location = currentSourceLocation();

		while (isIdentifierChar(peek()))
		{
			ident += peek();
			nextChar();
		}

		auto kind = TK_Identifier;
		const auto it = keywords.find(ident.data());

		if (it != keywords.end()) kind = it->second;

		m_tokens.push_back(newToken(kind, ident, location));
	}

	void Lexer::parseString()
	{
		std::string str;
		const auto		location = currentSourceLocation();

		nextChar();

		while (m_index < m_source.length())
		{
			if (peek() != '\\' && peek(1) == '"')
			{
				str += peek();
				nextChar();
				break;
			}

			str += peek();
			nextChar();
		}

		if (m_index >= m_source.length())
		{
			logError(
				"Excepted `\"` to end the string. Instead got `EOF` at `{}`:{}:{}",
				*m_file_name,
				m_line,
				m_column);
			return;
		}

		nextChar();

		m_tokens.push_back(newToken(TK_String, str, location));
	}

	bool Lexer::advanceWith(TokenKind kind, const std::string& lexeme)
	{
		m_tokens.push_back(newToken(kind, lexeme));
		m_index += lexeme.length();
		return true;
	}

} // namespace ucc