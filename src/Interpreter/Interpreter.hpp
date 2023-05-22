#pragma once
#include <map>
#include <vector>
#include <string>

#include "Token.hpp"

class Interpreter
{
public :
	Interpreter(std::vector<std::pair<Token, std::string>>& tokens);
	void setVariable(float x, float y);
	void reset();
	float interpretAST();

	std::vector<std::string> errors;

private :
	void advanceToken();
	const std::pair<Token, std::string>& peek();
	float multiplyDivide();
	float power();
	float value();

private:
	
	std::map<std::string, float> m_variables;
	std::uint32_t m_tokenIndex;
	std::pair<Token, std::string> m_currentToken;
	std::vector<std::pair<Token, std::string>> m_tokens;
};