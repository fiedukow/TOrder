#include "PodgladPostepu.hpp"
#include "EvolFunctions.hpp"
#include "Subject.hpp"
#include "CzasWykonania.h"
#include "Plan.h"


PodgladPostepu::PodgladPostepu() : populationCounter(0)
{}

void PodgladPostepu::update( evol::Population& population )
{
    Plan* best = evol::EvolFunctions::ptr_cast<evol::SubjectPtr, Plan>(
            population.getSubjects().at( population.getBestId() )
    );
    ++populationCounter;
    CzasWykonania czas;
    czas.calculate(*best);
    unsigned int current = czas.getTimeTotal();

    if( !bestTime || current < bestTime )
    {
        bestTime = current;
        std::cout << "Poprawil sie wynik najlepszego osobnika."<< std::endl;
        std::cout << "Obecny wynik (pokolenie nr. " << populationCounter << ") to: " << std::endl;
        best->print();
        std::cout << std::endl;
    }
    else if( populationCounter%10 == 0 )
    {
        std::cout << "Pokolenie nr. "<< populationCounter << std::endl << std::endl; 
    }
}
