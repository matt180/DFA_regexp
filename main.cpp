#include <iostream>
#include "Parser.h"
#include "StandardRegexHandler.h"

using namespace dfa_regexp;

int main()
{
	while (true) {
		try {
			std::cout << "Adja meg a regularis kifejezest!" << std::endl;
			std::string regex;
			std::cin >> regex;
			Parser parser(new StandardRegexHandler());
			auto sm = parser.parse(regex);
			std::cout << "Adja meg a kierekelendo szot!" << std::endl;
			std::string test;
			std::cin >> test;
			if (sm.validate(test)) {
				std::cout << "Illeszkedik" << std::endl;
			}
			else {
				std::cout << "Nem illeszkedik" << std::endl;
			}
		}
		catch (std::logic_error &e) {
			std::cout << e.what() << std::endl;
		}
	}
	return 0;
}
