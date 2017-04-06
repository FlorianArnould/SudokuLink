#include "include/case.h"

Case::Case(std::set<int> possibilities, State state) : possibilities(possibilities), value(0), state(state)
{

}

Case::Case(int value, State state) : value(value), state(state)
{

}

Case::State Case::getState()
{
    return state;
}

std::set<int> & Case::getPossibilities()
{
    return possibilities;
}

int Case::getValue()
{
    return value;
}
