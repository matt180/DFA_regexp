#ifndef HANDLER_H_INCLUDED
#define HANDLER_H_INCLUDED
#include <map>
#include <functional>

class Handler {

protected:

    std::map<char, std::function<void(char)>>& handling_funcs;

public:

    Handler() = default;

    void start_parenthesis() {
    }

    void end_parenthesis() {
    }

    virtual ~Handler() = default;
};

#endif // HANDLER_H_INCLUDED
