#include "EvolFunctions.hpp"

#include "Plan.h"

const std::list<int>& Plan::getKolejnosc() const
{
    Kolejnosc &kolejnosc = *evol::EvolFunctions::ptr_cast<evol::ChromosomePtr,Kolejnosc>(chromosomes[0]);
    return *kolejnosc;
}

void Plan::setInitialValue()
{
    // FIXME implement this
}

evol::SubjectPtr Plan::clone() const
{
    // FIXME implement this
}

void Plan::print() const
{
    // FIXME implement this
}
