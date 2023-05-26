#include <cmath>

#include "Interpreter.hpp"
#include "Lexer.hpp"

Interpreter::Interpreter(std::vector<std::pair<Token, std::string>>& tokens)
{
	m_tokens = tokens;

	m_tokenIndex = 0;
	m_currentToken = m_tokens[m_tokenIndex];
	m_variables["e"] = std::exp(1.0);
}

void Interpreter::setVariable(float x, float y)
{
	m_variables["x"] = x;
	m_variables["y"] = y;
}

void Interpreter::reset()
{
	m_tokenIndex = 0;
	m_currentToken = m_tokens[m_tokenIndex];
}

void Interpreter::advanceToken()
{
	m_currentToken = m_tokens[++m_tokenIndex];
}

const std::pair<Token, std::string>& Interpreter::peek()
{
	return m_tokens[m_tokenIndex + 1];
}

float Interpreter::interpretAST()
{
	float result = this->multiplyDivide();
	while (m_currentToken.first == Token::Plus || m_currentToken.first == Token::Minus)
	{
		if (m_currentToken.first == Token::Plus)
		{
			this->advanceToken();
			result += this->multiplyDivide();
		}

		if (m_currentToken.first == Token::Minus)
		{
			this->advanceToken();
			result -= this->multiplyDivide();
		}
	}

	return result;
}

float Interpreter::multiplyDivide()
{
	float result = this->power();
	while (m_currentToken.first == Token::Star || m_currentToken.first == Token::Slash)
	{
		if (m_currentToken.first == Token::Star)
		{
			this->advanceToken();
			result *= this->power();
		}

		if (m_currentToken.first == Token::Slash)
		{
			this->advanceToken();
			result /= this->power();
		}
	}

	return result;
}

float Interpreter::power()
{
	float result = this->value();
	while (m_currentToken.first == Token::Caret)
	{
		this->advanceToken();
		result = pow(result, this->value());
	}

	return result;
}

float Interpreter::value()
{
	float value = 0;
	switch (m_currentToken.first)
	{
	case Token::Plus :
		this->advanceToken();
		value = this->value();
		return value;
		break;

	case Token::Minus :
		this->advanceToken();
		value = this->value();
		return -value;
		break;

	case Token::Number:
		value = std::stof(m_currentToken.second);
		this->advanceToken();
		return value;
		break;

	case Token::Variable:
		value = m_variables[m_currentToken.second];
		this->advanceToken();
		return value;
		break;

	case Token::Left_parenthesis :
		this->advanceToken();
		value = this->interpretAST();
		this->advanceToken();
		return value;
		break;

	case Token::String :
		if (m_currentToken.second == "cos")
		{
			this->advanceToken();
			float input = this->value();
			return cos(input);
		}
		else if (m_currentToken.second == "sin")
		{
			this->advanceToken();
			float input = this->value();
			return sin(input);
		}
		else if (m_currentToken.second == "tan")
		{
			this->advanceToken();
			float input = this->value();
			return tan(input);
		}
		else if (m_currentToken.second == "acos")
		{
			this->advanceToken();
			float input = this->value();
			return acos(input);
		}
		else if (m_currentToken.second == "asin")
		{
			this->advanceToken();
			float input = this->value();
			return asin(input);
		}
		else if (m_currentToken.second == "atan")
		{
			this->advanceToken();
			float input = this->value();
			return atan(input);
		}
		else if (m_currentToken.second == "sqrt")
		{
			this->advanceToken();
			float input = this->value();
			return sqrt(input);
		}
		else if (m_currentToken.second == "log")
		{
			this->advanceToken();
			float input = this->value();
			return log10(input);
		}
		else if (m_currentToken.second == "ln")
		{
			this->advanceToken();
			float input = this->value();
			return log(input);
		}
		else if (m_currentToken.second == "abs")
		{
			this->advanceToken();
			float input = this->value();
			return abs(input);
		}	
		else
		{
			this->errors.push_back("[ERROR] Function unknowm " + m_currentToken.second + '\n');
			return 0;
		}
		break;

	default :
		this->errors.push_back("[ERROR] Token type unknowm " + std::to_string((int)m_currentToken.first) + '\n');
		return 0;
		break;
	}
}