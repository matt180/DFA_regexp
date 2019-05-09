#ifndef STANDARDREGEXHANDLER_H_INCLUDED
#define STANDARDREGEXHANDLER_H_INCLUDED
#include "Handler.h"
#include "StateMachine.h"

namespace dfa_regexp {

class StandardRegexHandler : public Handler {

    StateMachine sm_;

    enum class state {

    };

public:

    void build() override {

    }

private:
    void handle_defaults(char c) {

    }

};

}

#endif // STANDARDREGEXHANDLER_H_INCLUDED
