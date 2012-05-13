#ifndef KOLEJNOSC_H
#define KOLEJNOSC_H

#include "Chromosome.hpp"
#include <list>

class Kolejnosc;

typedef std::shared_ptr<Kolejnosc> KolejnoscPtr;

class Kolejnosc : public evol::Chromosome
{
public:
    evol::ChromosomePtr crossWith(evol::ChromosomePtr) const;
    void mutate();
    std::list<int>& operator*() const;
private:
    std::list<int> kolejnosc_;
};

#endif
