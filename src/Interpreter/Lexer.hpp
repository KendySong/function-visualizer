#pragma once
#include <vector>
#include <string>

#include "Token.hpp"

class Lexer
{
public :
	Lexer(std::string expression);
	std::vector<std::pair<Token, std::string>> tokens;

private :
	bool isLetter(char input);
	bool isNumber(char input);
};