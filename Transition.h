#ifndef TRANSITION_H_INCLUDED
#define TRANSITION_H_INCLUDED
#include "State.h"

namespace dfa_regexp {

class Transition {

protected:

    std::shared_ptr<State> target_;
    char transit_;

public:

    Transition(std::shared_ptr<State> target, char transit = 0) : target_{target}, transit_{transit} { }

    virtual std::shared_ptr<State> fire(std::string::iterator& it) {
        if (transit_ == *it) {
            ++it;
            return target_;
        }
        return nullptr;
    }

    std::shared_ptr<State> getTarget() {
        return  target_;
    }

    virtual ~Transition() = default;
};

class PermeableTransition : public Transition {

public:

    using Transition::Transition;

    virtual std::shared_ptr<State> fire(std::string::iterator&) override {
        return target_;
    }

};

}
#endif // TRANSITION_H_INCLUDED
