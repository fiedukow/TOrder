#pragma once
#include "Population.hpp"

class CzasWykonania : public FitnessFunction
{
    int timeTotal;

    public:
    virtual bool operator > ( const FItnessFunction& toCompare ) const;
    virtual bool operator == ( const FitnessFunction& toCompare ) const;

    virtual void calculate( const Subject& toCalculate );

    virtual void print();
};
