#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED
#include <iostream>
#include <algorithm>
#include <string>
#include <memory>
#include <stack>
#include "Handler.h"
#include "StateMachine.h"

namespace dfa_regexp {

class Parser {

private:

    std::unique_ptr<Handler> handler;

    enum class ParseState {
        none,
        in_parenthesis,
        exp
    };

    std::stack<ParseState> _stack{};

    bool escape = false;
    bool error = false;

public:

    Parser(Handler* h) : handler{h} {
		_stack.push(ParseState::none);
    }

    StateMachine parse(const std::string& regexp) {
		auto str = eliminate_plus(regexp);
		for (auto c : str) {
            if (escape) {
                handler->handle_default(c);
				if (_stack.top() != ParseState::exp)
					_stack.push(ParseState::exp);
                escape = false;
            } else {
                switch(c) {
                    case '(': {
                           handler->start_parenthesis();
                           _stack.push(ParseState::in_parenthesis);
                    } break;

                    case ')': {
                        if (_stack.top() == ParseState::exp)
                            _stack.pop();
                        if (_stack.top() != ParseState::in_parenthesis)
                            throw std::logic_error("rossz zarojelezes");
						_stack.pop();
						_stack.push(ParseState::exp);
                        handler->end_parenthesis();
                    } break;

                    case '*': {
                            handler->handle_star();
                            _stack.pop();
                    } break;

                    case '?': {
                            handler->handle_question_mark();
                            _stack.pop();
                    } break;

                    case '|': {
                            handler->handle_vertical_line();
                            _stack.pop();
                    } break;

                    case '\\': escape = true; break;

                    default: {
                        handler->handle_default(c);
                        if (_stack.top() != ParseState::exp)
                            _stack.push(ParseState::exp);
                    } break;
                }
            }

        }
		if (_stack.top() == ParseState::in_parenthesis)
			throw std::logic_error("rossz zarojelezes");
		while (_stack.top() != ParseState::none) {
			_stack.pop();
		}
		handler->end_expression();
        return handler->getStateMachine();;
    }


private:

	std::string eliminate_plus(const std::string& str) {
		auto regexp = str;
		std::reverse(regexp.begin(), regexp.end());
		for (auto pos = regexp.find_first_of('+'); pos != std::string::npos; pos = regexp.find_first_of('+', pos + 1)) {
			if (regexp[pos + 1] != '\\') {
				regexp[pos] = '*';
				if (regexp[pos + 1] == ')') {
					if (!isEscaped(regexp, pos + 1)) {
						auto sub = substring_ph(regexp, pos + 1);
						regexp.insert(pos + sub.length() + 1, sub);
					}
					else {
						regexp.insert(pos + 1, ")\\");
					}
				}
				else {
					char c = regexp[pos + 1];
					regexp.insert(pos + 1, 1, c);
				}
			}
		}
		std::reverse(regexp.begin(), regexp.end());
		return regexp;
	}

	std::string substring_ph(std::string regexp, int pos) {
		int count = 0;
		for (size_t i = pos; i < regexp.length(); ++i) {
			if (regexp[i] == ')') {
				if (!isEscaped(regexp, i)) {
					++count;
				}
			}
			else if (regexp[i] == '(') {
				if (!isEscaped(regexp, i)) {
					--count;
				}
				if (count == 0) {
					return regexp.substr(pos, i - pos + 1);
				}
			}
		}
		throw std::logic_error("rossz zarojelezes");
	}

	bool isEscaped(std::string regexp, size_t pos) {
		if (pos < regexp.length() - 1) {
			if (regexp[pos + 1] == '\\') {
				if (pos < regexp.length() - 2) {
					if (regexp[pos + 1] == '\\' && regexp[pos + 2] == '\\') {
						return false;
					}
				}
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
		return true;
	}

};

}

#endif // PARSER_H_INCLUDED
