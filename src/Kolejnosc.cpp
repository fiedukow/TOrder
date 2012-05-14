#include "Kolejnosc.h"

evol::ChromosomePtr Kolejnosc::crossWith(evol::ChromosomePtr toCross) const
{
    // FIXME implement this
}

void Kolejnosc::mutate()
{
    // FIXME implement this
}

evol::ChromosomePtr Kolejnosc::clone()
{
    //FIXME implement this
}

const std::list<int>& Kolejnosc::operator*() const 
{
    return kolejnosc_;
}

