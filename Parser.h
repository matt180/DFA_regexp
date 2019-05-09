#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED
#include <memory>
#include "Handler.h"
#include "StateMachine.h"

namespace dfa_regexp {

class Parser {

private:

    std::unique_ptr<Handler>& handler;

public:

    Parser(std::unique_ptr<Handler>& h) : handler{h} {}

    StateMachine parse(std::string regexp) {
        for (char c : regexp) {
            switch(c) {

            }
        }
    }

};

}

#endif // PARSER_H_INCLUDED
