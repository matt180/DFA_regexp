#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED


struct State {
	const unsigned id;
	bool acceptor = false;
	static unsigned count;
	State() : id(count++) { };
};

unsigned State::count = 0;

#endif // STATE_H_INCLUDED
