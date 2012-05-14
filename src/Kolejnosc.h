#ifndef KOLEJNOSC_H
#define KOLEJNOSC_H

#include "Chromosome.hpp"
#include <vector>

class Kolejnosc;

typedef std::shared_ptr<Kolejnosc> KolejnoscPtr;

class Kolejnosc : public evol::Chromosome
{
public:
    Kolejnosc();
    Kolejnosc(const Kolejnosc&);
    evol::ChromosomePtr crossWith(evol::ChromosomePtr) const;
    void mutate();
    const std::vector<int>& operator*() const;
    evol::ChromosomePtr clone() const;
private:
    std::vector<int> kolejnosc_;
};

#endif
