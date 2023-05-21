#include <cstring>

#include "Lexer.hpp"


Lexer::Lexer(std::string expression)
{
	std::string baseExpression = expression;
	expression = "";
	for (size_t i = 0; i < baseExpression.size(); i++)
	{
		expression += tolower(baseExpression[i]);
	}

	for (size_t i = 0; i < expression.size(); i++)
	{
		switch (expression[i])
		{
		case '+':
			this->tokens.push_back(std::pair<Token, std::string>(Token::PLUS, "+"));
			break;

		case '-':
			this->tokens.push_back(std::pair<Token, std::string>(Token::MINUS, "-"));
			break;

		case '*':
			this->tokens.push_back(std::pair<Token, std::string>(Token::STAR, "*"));
			break;

		case '/':
			this->tokens.push_back(std::pair<Token, std::string>(Token::SLASH, "/"));
			break;

		case '^':
			this->tokens.push_back(std::pair<Token, std::string>(Token::CARET, "^"));
			break;

		case '(':
			this->tokens.push_back(std::pair<Token, std::string>(Token::LEFT_PATENTHESIS, "("));
			break;

		case ')':
			this->tokens.push_back(std::pair<Token, std::string>(Token::RIGHT_PATENTHESIS, ")"));
			break;

		default:
			if (expression[i] == 'x' || expression[i] == 'y')
			{
				std::string variable;
				variable += expression[i];
				this->tokens.push_back(std::pair<Token, std::string>(Token::VARIABLE, variable));
				continue;
			}

			if (this->isLetter((expression[i])))
			{
				std::string litteral;
				while (this->isLetter((expression[i])))
				{
					litteral += expression[i];
					i++;
				}
				i--;
				this->tokens.push_back(std::pair<Token, std::string>(Token::STRING, litteral));
			}

			if (this->isNumber((expression[i])))
			{
				std::string number;
				while (this->isNumber((expression[i])) || expression[i] == '.')
				{
					number += expression[i];
					i++;
				}
				i--;
				this->tokens.push_back(std::pair<Token, std::string>(Token::NUMBER, number));
			}
			break;
		}
	}

	this->tokens.push_back(std::pair<Token, std::string>(Token::END, "end"));
}

bool Lexer::isLetter(char input)
{
	return input >= 'a' && input <= 'z';
}

bool Lexer::isNumber(char input)
{
	return input >= '0' && input <= '9';
}