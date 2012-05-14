#include "Kolejnosc.h"
#include "ZarzadcaZadan.hpp"

Kolejnosc::Kolejnosc()
{
    int zadan = ZarzadcaZadan::getInstance().getIloscZadan();
    for(int i=0; i<zadan; ++i)
    {
        kolejnosc_.push_back(i);
    }
}

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

