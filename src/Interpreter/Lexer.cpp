#include <cstring>

#include "Lexer.hpp"

Lexer::Lexer(std::string expression)
{
	tokens = new std::vector<std::pair<Token, std::string>>();
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
			this->tokens->push_back(std::pair<Token, std::string>(Token::Plus, "+"));
			break;

		case '-':
			this->tokens->push_back(std::pair<Token, std::string>(Token::Minus, "-"));
			break;

		case '*':
			this->tokens->push_back(std::pair<Token, std::string>(Token::Star, "*"));
			break;

		case '/':
			this->tokens->push_back(std::pair<Token, std::string>(Token::Slash, "/"));
			break;

		case '^':
			this->tokens->push_back(std::pair<Token, std::string>(Token::Caret, "^"));
			break;

		case '(':
			this->tokens->push_back(std::pair<Token, std::string>(Token::Left_parenthesis, "("));
			break;

		case ')':
			this->tokens->push_back(std::pair<Token, std::string>(Token::Right_parenthesis, ")"));
			break;

		default:
			if (expression[i] == 'x' || expression[i] == 'y')
			{
				std::string variable;
				variable += expression[i];
				this->tokens->push_back(std::pair<Token, std::string>(Token::Variable, variable));
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
				this->tokens->push_back(std::pair<Token, std::string>(Token::String, litteral));
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
				this->tokens->push_back(std::pair<Token, std::string>(Token::Number, number));
			}
			break;
		}
	}

	this->tokens->push_back(std::pair<Token, std::string>(Token::End, "end"));
}

Lexer::~Lexer()
{
	delete tokens;
}

bool Lexer::isLetter(char input)
{
	return input >= 'a' && input <= 'z';
}

bool Lexer::isNumber(char input)
{
	return input >= '0' && input <= '9';
}