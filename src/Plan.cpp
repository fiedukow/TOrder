#include <iostream>
#include "CzasWykonania.h"
#include "Plan.h"
#include "EvolFunctions.hpp"

std::list<int> Plan::getKolejnosc() const
{
    Kolejnosc &kolejnosc = *evol::EvolFunctions::ptr_cast<evol::ChromosomePtr,Kolejnosc>(chromosomes[0]);
    std::list<int> toReturn;
    for(auto& elem : *kolejnosc)
    {
        toReturn.push_back(elem);
    }
    return toReturn;
}

void Plan::setInitialValue()
{
    addChromosome(evol::ChromosomePtr(new Kolejnosc()));
}

evol::SubjectPtr Plan::clone() const
{
    evol::SubjectPtr newPlan = evol::SubjectPtr(new Plan()); 
    newPlan->addChromosome( evol::EvolFunctions::ptr_cast<evol::ChromosomePtr,Kolejnosc>(this->chromosomes[0])->clone()  );
    return newPlan;
}

void Plan::print() const
{
    CzasWykonania czas;
    czas.calculate(*this);

    std::cout << "PLAN WYKONANIA: "<< std::endl;
    const std::list<int>& kol = getKolejnosc();
    for(int a : kol)
    {
        std::cout << a << " ";
    }
    std::cout << std::endl;

    std::cout << "Czas wykonania " << czas.getTimeTotal() << std::endl;
}
