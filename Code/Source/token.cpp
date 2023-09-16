#include "uzl/token.h"
#include <vector>
#include <algorithm>

namespace uzl
{

	bool Token::isUnaryOperator() const {
		static constexpr auto unary_operators = { TK_DoubleInc, TK_DoubleDec, TK_Ampersand, TK_Asterisk,
											  TK_Invert,	TK_BinInv,	  TK_Add,		TK_Sub };

		return std::find(unary_operators.begin(), unary_operators.end(), kind) !=
			unary_operators.end();
	}

	bool Token::unaryOperatorIsLeftAssoc() const {
		static constexpr auto left_assoc_operators = { TK_DoubleInc, TK_DoubleDec, TK_Ampersand,
												   TK_Asterisk,	 TK_Invert,	   TK_BinInv,
												   TK_Add,		 TK_Sub };

		return std::find(left_assoc_operators.begin(), left_assoc_operators.end(), kind) !=
			left_assoc_operators.end();
	}

	bool Token::unaryOperatorIsRightAssoc() const {
		static constexpr auto right_assoc_operators = { TK_DoubleInc, TK_DoubleDec };

		return std::find(right_assoc_operators.begin(), right_assoc_operators.end(), kind) !=
			right_assoc_operators.end();
	}

	bool Token::isBinaryOperator() const {
		static constexpr auto binary_operators = {
			TK_Add,		TK_Sub,		TK_Asterisk,  TK_Div,	TK_Assign, TK_AddA,	  TK_SubA,
			TK_MulA,	TK_DivA,	TK_Ampersand, TK_Pipe,	TK_And,	   TK_Or,	  TK_BinXor,
			TK_BinInv,	TK_BinXorA, TK_BinInvA,	  TK_BinLS, TK_BinRS,  TK_BinLSA, TK_BinRSA,
			TK_BinAndA, TK_BinOrA,	TK_GT,		  TK_LT,	TK_GTE,	   TK_LTE
		};

		return std::find(binary_operators.begin(), binary_operators.end(), kind) != binary_operators.end();
	}

}