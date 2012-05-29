#include "PodgladPostepu.hpp"
#include "EvolFunctions.hpp"
#include "Subject.hpp"
#include "CzasWykonania.h"
#include "Plan.h"
#include <ctime>


PodgladPostepu::PodgladPostepu( std::size_t timeLimit ) : populationCounter(0), timeLimit(timeLimit), startTime(time(NULL))
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
        lastBetter = populationCounter;
        std::cout << "Poprawil sie wynik najlepszego osobnika."<< std::endl;
        std::cout << "Obecny wynik (pokolenie nr. " << populationCounter << ") to: " << std::endl;
        best->print();
        std::cout << std::endl;
    }
    else if( populationCounter%100 == 0 )
    {
        std::cout << "Pokolenie nr. "<< populationCounter << std::endl << std::endl; 
    }

    if( timeLimit != 0 )
    {
        if( (time(NULL) - startTime) > timeLimit )
            population.stopLoop();
    }
}

std::size_t PodgladPostepu::getTimeTaken()
{
    return (time(NULL) - startTime);
}

std::size_t PodgladPostepu::getGenerationNumber()
{
    return populationCounter;
}

std::size_t PodgladPostepu::getLastBetter()
{
    return lastBetter;
}
