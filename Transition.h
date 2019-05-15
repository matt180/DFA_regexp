#ifndef TRANSITION_H_INCLUDED
#define TRANSITION_H_INCLUDED
#include "State.h"

namespace dfa_regexp {

class Transition {

protected:

    std::shared_ptr<State> _target;
    char _transit;

public:

    Transition(std::shared_ptr<State> target, char transit = 0) : _target{target}, _transit{transit} { }

    virtual std::shared_ptr<State> fire(std::string::iterator& it, std::string::iterator&& end) {
		if (it == end)
			return nullptr;
        if (_transit == *it) {
            ++it;
            return _target;
        }
        return nullptr;
    }

    std::shared_ptr<State> getTarget() {
        return  _target;
    }

    virtual ~Transition() = default;
};

class PermeableTransition : public Transition {

public:

    using Transition::Transition;

    virtual std::shared_ptr<State> fire(std::string::iterator&, std::string::iterator&&) override {
        return _target;
    }

};

}
#endif // TRANSITION_H_INCLUDED
