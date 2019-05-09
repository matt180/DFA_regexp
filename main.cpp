#include <iostream>
#include "Parser.h"

using namespace dfa_regexp;

int main()
{
    auto s0 = std::make_shared<State>();
    auto s1 = std::make_shared<State>();
    auto s2 = std::make_shared<State>();
    auto s3 = std::make_shared<State>();
    auto s4 = std::make_shared<State>();
    auto s5 = std::make_shared<State>();
    auto s6 = std::make_shared<State>();
    s6->acceptor = true;
    StateMachine sm(s0);
    sm.addTransition(s0, s1, 'a');
    sm.addTransition(s1, s2, 'b');
    sm.addTransition(s2, s3, 'c');
    sm.addTransition(s2, s4, 'd');
    sm.addTransition(s1, s0, 'f');
    sm.addTransition(s4, std::make_shared<PermeableTransition>(s5));
    sm.addTransition(s3, std::make_shared<PermeableTransition>(s5));
    sm.addTransition(s5, std::make_shared<PermeableTransition>(s6));
    std::cout << sm.validate("abfd");
    return 0;
}
