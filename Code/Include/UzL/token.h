#pragma once

#include "common.h"
#include <string>

namespace uzl
{

	struct SourceLocation
	{
		std::shared_ptr<std::string> file_name;
		u64 line{ 0 };
		u64 column{ 0 };
	};

	enum TokenKind
	{
		TK_Error,
		TK_Number,
		TK_Identifier,
		TK_String,

		TK_LT,		  ///< <
		TK_LTE,		  ///< <=
		TK_GT,		  ///< \>
		TK_GTE,		  ///< >=
		TK_Assign,	  ///< =
		TK_Equals,	  ///< ==
		TK_NotEquals, ///< !=
		TK_Invert,	  ///< !

		TK_BinLS,	  ///< <<
		TK_BinRS,	  ///< \>>
		TK_Ampersand, ///< &
		TK_Pipe,	  ///< |
		TK_BinXor,	  ///< ^
		TK_BinInv,	  ///< ~
		TK_BinLSA,	  ///< <<=
		TK_BinRSA,	  ///< \>>=
		TK_BinAndA,	  ///< &=
		TK_BinOrA,	  ///< |=
		TK_BinXorA,	  ///< ^=
		TK_BinInvA,	  ///< ~=

		TK_And, ///< &&
		TK_Or,	///< ||

		TK_Add,		 ///< \+
		TK_Sub,		 ///< \-
		TK_Asterisk, ///< star
		TK_Div,		 ///< /
		TK_Percent,	 ///< %
		TK_AddA,	 ///< +=
		TK_SubA,	 ///< -=
		TK_MulA,	 ///< *=
		TK_DivA,	 ///< /=
		TK_PercentA, ///< %=

		TK_LBracket, ///< (
		TK_RBracket, ///< )
		TK_LBrace,	 ///< {
		TK_RBrace,	 ///< }
		TK_LSquare,	 ///< [
		TK_RSquare,	 ///< ]

		TK_Period,	  ///< .
		TK_Colon,	  ///< :
		TK_SemiColon, ///< ;
		TK_Comma,	  ///< ,
		TK_Arrow,	  ///< ->
		TK_ScopeRes,  ///< ::

		TK_SQuote, ///< '
		TK_DQuote, ///< "

		TK_DoubleInc, ///< ++
		TK_DoubleDec, ///< --

		TK_KwFunc,
		TK_KwConst,
		TK_KwTrue,
		TK_KwFalse,
		TK_KwFor,
		TK_KwWhile,
		TK_KwLoop,
		TK_KwContinue,
		TK_KwSwitch,
		TK_KwCase,
		TK_KwFallthrough,
		TK_KwDefault,
		TK_KwVar,

		TK_Eof
	};

	struct Token
	{
		TokenKind	   kind;
		std::string	   lexeme;
		SourceLocation location;

		bool operator==(TokenKind kind) const { return this->kind == kind; }
		bool operator!=(TokenKind kind) const { return !(this->kind == kind); }

		bool				  isOperator() const { return isUnaryOperator() || isBinaryOperator(); }
		bool				  isUnaryOperator() const;
		bool				  unaryOperatorIsLeftAssoc() const;
		bool				  unaryOperatorIsRightAssoc() const;

		bool				  isBinaryOperator() const;
	};

}