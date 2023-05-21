#include <cmath>

#include "Interpreter.hpp"

Interpreter::Interpreter(const std::vector<std::pair<Token, std::string>>& tokens, float x, float y)
{
	m_tokens = tokens;
	m_tokenIndex = 0;
	m_currentToken = m_tokens[m_tokenIndex];
	m_variables["x"] = x;
	m_variables["y"] = y;
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
	while (m_currentToken.first == Token::PLUS || m_currentToken.first == Token::MINUS)
	{
		if (m_currentToken.first == Token::PLUS)
		{
			this->advanceToken();
			result += this->multiplyDivide();
		}

		if (m_currentToken.first == Token::MINUS)
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
	while (m_currentToken.first == Token::STAR || m_currentToken.first == Token::SLASH)
	{
		if (m_currentToken.first == Token::STAR)
		{
			this->advanceToken();
			result *= this->power();
		}

		if (m_currentToken.first == Token::SLASH)
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
	while (m_currentToken.first == Token::CARET)
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
	case Token::NUMBER:
		value = std::stof(m_currentToken.second);
		this->advanceToken();
		return value;
		break;

	case Token::VARIABLE:
		value = m_variables[m_currentToken.second];
		this->advanceToken();
		return value;
		break;

	case Token::LEFT_PATENTHESIS :
		this->advanceToken();
		value = this->interpretAST();
		this->advanceToken();
		return value;
		break;

	default :
		m_errors.push_back("[ERROR] Token type unknowm " + std::to_string((int)m_currentToken.first));
		break;
	}

	return 0;
}