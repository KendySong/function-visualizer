#pragma once
#include <map>
#include <vector>
#include <string>

#include "Token.hpp"

class Interpreter
{
public :
	Interpreter(const std::vector<std::pair<Token, std::string>>& tokens, float x, float y);
	float interpretAST();

private :
	void advanceToken();
	const std::pair<Token, std::string>& peek();

	float plusMinus();
	float multiplyDivide();
	float value();

private:
	std::vector<std::string> m_errors;
	std::map<std::string, float> m_variables;
	std::uint32_t m_tokenIndex;
	std::pair<Token, std::string> m_currentToken;
	std::vector<std::pair<Token, std::string>> m_tokens;
};