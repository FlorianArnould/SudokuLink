#ifndef CASE_H
#define CASE_H

#include <set>

class Case
{
public:
    enum State {ORIGINAL=0, POSSIBLE, MULTIPLE_POSSIBLE, ERROR, NOTHING};
    Case(std::set<int> possibilities, State state);
    Case(int value, State state);
    State getState();
    std::set<int> & getPossibilities();
    int getValue();
private:
    std::set<int> possibilities;
    int value;
    State state;
};

#endif // CASE_H
