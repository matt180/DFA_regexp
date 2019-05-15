#ifndef HANDLER_H_INCLUDED
#define HANDLER_H_INCLUDED
#include <map>
#include <functional>
#include "StateMachine.h"

namespace dfa_regexp {

class Handler {

public:

    virtual void start_parenthesis() = 0;

    virtual void end_parenthesis() = 0;

    virtual void handle_default(char c) = 0;

    virtual void handle_star() = 0;

	virtual void handle_plus() = 0;

    virtual void handle_vertical_line() = 0;

    virtual void handle_question_mark() = 0;

    virtual StateMachine getStateMachine() = 0;

	virtual void end_expression() = 0;

    virtual ~Handler() = default;
};

}

#endif // HANDLER_H_INCLUDED
