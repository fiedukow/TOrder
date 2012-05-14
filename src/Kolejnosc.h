#ifndef KOLEJNOSC_H
#define KOLEJNOSC_H

#include "Chromosome.hpp"
#include <list>

class Kolejnosc;

typedef std::shared_ptr<Kolejnosc> KolejnoscPtr;

class Kolejnosc : public evol::Chromosome
{
public:
    Kolejnosc();
    Kolejnosc(const Kolejnosc&);
    evol::ChromosomePtr crossWith(evol::ChromosomePtr) const;
    void mutate();
    const std::list<int>& operator*() const;
    evol::ChromosomePtr clone();
private:
    std::list<int> kolejnosc_;
};

#endif
