#ifndef STATEMACHINE_H_INCLUDED
#define STATEMACHINE_H_INCLUDED
#include "Transition.h"
#include <memory>
#include <vector>

namespace dfa_regexp {

class StateMachine {

    using transit_ptr = std::shared_ptr<Transition>;

    using state_ptr = std::shared_ptr<State>;

    state_ptr start_, end_;

    std::map<std::shared_ptr<State>, std::vector<transit_ptr>> transitions_;

public:

    StateMachine() : start_{std::make_shared<State>()}, end_{start_}, transitions_{} { }

    StateMachine(state_ptr start) : start_{start}, end_{start}, transitions_{} { }

    void concatenate(StateMachine& sm, std::shared_ptr<State> start, std::shared_ptr<State> end) {
        auto new_transitions = sm.getTransitions();
        addTransition(end_, std::make_shared<PermeableTransition>(start));
        for (auto t : new_transitions) {
            transitions_.insert(t);
        }
        end_ = end;
    }

    void addTransition(state_ptr start, state_ptr target, char transit) {
        auto transition = std::make_shared<Transition>(target, transit);
        addTransition(start, transition);
    }

    void addTransition(state_ptr state, transit_ptr transit) {
        auto elem = transitions_.find(state);
        if (elem != transitions_.end()) {
            elem->second.push_back(transit);
        } else {
            transitions_[state] = std::vector<transit_ptr>();
            transitions_[state].push_back(transit);
            end_ = transit->getTarget();
        }

    }

    std::map<state_ptr, std::vector<transit_ptr>> getTransitions() {
        return transitions_;
    }

    bool validate(std::string in) {
        auto pos = in.begin();
        bool terminate = false;
        state_ptr act = start_;
        while (!terminate) {
            auto transits = transitions_[act];
            terminate = true;
            for (auto&& t : transits) {
                act = t->fire(pos);
                if (pos == in.end()) {
                    terminate = true;
                }
                if (act) {
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
