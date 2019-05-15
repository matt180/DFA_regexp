#ifndef STANDARDREGEXHANDLER_H_INCLUDED
#define STANDARDREGEXHANDLER_H_INCLUDED
#include "Handler.h"
#include "StateMachine.h"

namespace dfa_regexp {

class StandardRegexHandler : public Handler {

    std::stack<std::unique_ptr<StateMachine>> _stack{};

    std::shared_ptr<State> act_state{}, behind_state{};

	std::stack<std::shared_ptr<State>> ph_starts{};

	std::vector<std::shared_ptr<State>> _tails{};

	bool _meet = false;

public:



	StandardRegexHandler() {
		pushStateMachine();
    }

	void handle_default(char c) override {
		behind_state = act_state;
		act_state = std::make_shared<State>();
		_stack.top()->addTransition(behind_state, act_state, c);
		if (_meet && !_tails.empty()) {
			for (auto t : _tails) {
				_stack.top()->addTransition(t, act_state, c);
			}
			_tails.clear();
			_meet = false;
		}
    }

    void start_parenthesis() override {
		_meet = false;
		pushStateMachine();
    }

    void end_parenthesis() override {
		_meet = true;
		auto tmp = *_stack.top();
		//link_tails();
		behind_state = ph_starts.top();
		ph_starts.pop();
		act_state = tmp.getEnd();
		_stack.pop();
		_stack.top()->concatenate(tmp);
    }

    void handle_star() override {
		if (_meet) {
			link_tails();
			_meet = false;
		}
        _stack.top()->addTransition(act_state, std::make_shared<PermeableTransition>(behind_state));
		act_state = behind_state;
    }

    void handle_vertical_line() override {
		_meet = false;
		_tails.push_back(act_state);
		act_state = ph_starts.top();
    }

    void handle_question_mark() override {
		_meet = true;
		_tails.push_back(behind_state);
    }

	void handle_plus() override {
	}

	void end_expression() override {
		if (!_tails.empty()) {
			for (auto t : _tails) {
				t->acceptor = true;
			}
		}
		act_state->acceptor = true;
	}

    StateMachine getStateMachine() override {
        return *_stack.top();
    }

private:

	void link_tails() {
		if (!_tails.empty()) {
			auto target = std::make_shared<State>();
			_stack.top()->addTransition(act_state, std::make_shared<PermeableTransition>(target));
			for (auto t : _tails) {
				_stack.top()->addTransition(t, std::make_shared<PermeableTransition>(target));
			}
			act_state = target;
			_tails.clear();
		}
	}

	void pushStateMachine() {
		_stack.push(std::make_unique<StateMachine>());
		act_state = _stack.top()->getStart();
		ph_starts.push(act_state);
	}

};

}

#endif // STANDARDREGEXHANDLER_H_INCLUDED
