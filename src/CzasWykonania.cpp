#include "CzasWykonania.h"
#include "Population.hpp"
#include "ZarzadcaZadan.hpp"
#include "Plan.h"
#include "Maszyna.h"
#include "debug.h"
#include <iostream>

CzasWykonania::CzasWykonania( int timeTotal_ ) : timeTotal(timeTotal_)
{}

CzasWykonania::CzasWykonania() : timeTotal(0)
{}

bool CzasWykonania::operator > ( const evol::FitnessFunction& toCompare ) const
{
    return timeTotal < ((CzasWykonania&)toCompare).timeTotal;
}

bool CzasWykonania::operator == ( const evol::FitnessFunction& toCompare ) const
{
    return timeTotal == ((CzasWykonania&)toCompare).timeTotal;
}

void CzasWykonania::calculate( const evol::Subject& toCalculate )
{
    timeTotal = ((const Plan&)toCalculate).getTimeTotal();
}

int CzasWykonania::getTimeTotal()
{
    return timeTotal;
}

std::unique_ptr<evol::FitnessFunction> CzasWykonania::clone() const
{
    return std::unique_ptr<evol::FitnessFunction>(new CzasWykonania(timeTotal));
}

void CzasWykonania::print()
{}

int CzasWykonania::getCzasWykonania()
{
    return timeTotal; //TODO should throw exception if timeTotal wasnt initialized yet.
}
