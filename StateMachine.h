#ifndef STATEMACHINE_H_INCLUDED
#define STATEMACHINE_H_INCLUDED
#include "Transition.h"
#include <memory>
#include <vector>

namespace dfa_regexp {

class StateMachine {

    using transit_ptr = std::shared_ptr<Transition>;

    using state_ptr = std::shared_ptr<State>;

    state_ptr _start, _end;

    std::map<std::shared_ptr<State>, std::vector<transit_ptr>> _transitions;

public:

    StateMachine() : _start{std::make_shared<State>()}, _end{_start}, _transitions{} { }

    StateMachine(state_ptr start) : _start{start}, _end{start}, _transitions{} { }

    void concatenate(StateMachine& sm) {
        auto new_transitions = sm.getTransitions();
        addTransition(_end, std::make_shared<PermeableTransition>(sm.getStart()));
        for (auto t : new_transitions) {
            _transitions.insert(t);
        }
        _end = sm.getEnd();
    }

    void addTransition(state_ptr start, state_ptr target, char transit) {
        auto transition = std::make_shared<Transition>(target, transit);
        addTransition(start, transition);
    }

    void addTransition(state_ptr state, transit_ptr transit) {
        auto elem = _transitions.find(state);
        if (elem != _transitions.end()) {
            elem->second.push_back(transit);
        } else {
            _transitions[state] = std::vector<transit_ptr>();
            _transitions[state].push_back(transit);
        }
		_end = transit->getTarget();
    }

    void makeLastAcceptor() {
        _end->acceptor = true;
    }

    std::map<state_ptr, std::vector<transit_ptr>> getTransitions() {
        return _transitions;
    }

	state_ptr getStart() {
		return _start;
	}

    state_ptr getEnd() {
        return _end;
    }

    bool validate(std::string in) {
        auto pos = in.begin();
        bool terminate = false;
        state_ptr act = _start;
        while (!terminate) {
            auto transits = _transitions[act];
            terminate = true;
            for (auto&& t : transits) {
                auto target = t->fire(pos, in.end());
                if (pos == in.end()) {
                    terminate = true;
                }
                if (target) {
					act = target;
                    terminate = false;
                    break;
                }
            }
        }
        if (!act)
            return false;
        return act->acceptor && pos == in.end();
    }
};

}

#endif // STATEMACHINE_H_INCLUDED
