#pragma once
#include <boost/optional.hpp>
#include "Observer.hpp"
#include "Population.hpp"
#include <iostream>

class PodgladPostepu : public evol::NewGenerationObserver
{
    private:
    boost::optional<unsigned int> bestTime;
    unsigned int populationCounter;
    std::size_t timeLimit;
    std::size_t startTime;
    std::size_t lastBetter;
    public:
    PodgladPostepu( std::size_t timeLimit = 0 );
    void update( evol::Population& population );
    std::size_t getTimeTaken();
    std::size_t getGenerationNumber();
    std::size_t getLastBetter();
}; 

