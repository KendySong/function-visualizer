//#include "App/Application.hpp"
#include "Interpreter/Lexer.hpp"
#include "Interpreter/Interpreter.hpp"
#include <iostream>

int main()
{
	//log(x + y) + sin(x^2 + y^2)
    Lexer lexer("-(+5)");
	for (size_t i = 0; i < lexer.tokens.size(); i++)
	{
		std::cout << (int)lexer.tokens[i].first << '|' << lexer.tokens[i].second << '\n';
	}

	Interpreter interpreter(lexer.tokens, 3, 2);
	printf("Result : %f", interpreter.interpretAST());

    //return Application::instance()->run();
}