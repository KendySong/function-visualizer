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
	float result = this->plusMinus();
	return result;
}

float Interpreter::plusMinus()
{
	float result = this->value();
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
	float result = this->value();
	while (m_currentToken.first == Token::STAR || m_currentToken.first == Token::SLASH)
	{
		if (m_currentToken.first == Token::STAR)
		{
			this->advanceToken();
			result *= this->value();
		}

		if (m_currentToken.first == Token::SLASH)
		{
			this->advanceToken();
			result /= this->value();
		}
	}

	return result;
}

float Interpreter::value()
{
	if (m_currentToken.first == Token::NUMBER)
	{
		float value = std::stof(m_currentToken.second);
		this->advanceToken();
		return value;
	}

	if (m_currentToken.first == Token::VARIABLE)
	{
		float variableValue = m_variables[m_currentToken.second];	
		this->advanceToken();
		return variableValue;
	}	

	m_errors.push_back("[ERROR] Token type unknowm " + std::to_string((int)m_currentToken.first));
	return 0;
}