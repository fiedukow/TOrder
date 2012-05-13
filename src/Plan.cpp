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
    evol::SubjectPtr newPlan = evol::SubjectPtr(new Plan()); 
    newPlan->addChromosome( evol::EvolFunctions::ptr_cast<evol::ChromosomePtr,Kolejnosc>(this->chromosomes[0])->clone()  );
    return newPlan;
}

void Plan::print() const
{
    // FIXME implement this
}
