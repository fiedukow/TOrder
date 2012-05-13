#pragma once
#include <boost/optional.hpp>
#include "Population.hpp"
#include "Subject.hpp"
#include <memory>

class CzasWykonania : public evol::FitnessFunction
{
    int timeTotal;

    public:
    CzasWykonania( int timeTotal_ );
    virtual bool operator > ( const evol::FitnessFunction& toCompare ) const;
    virtual bool operator == ( const evol::FitnessFunction& toCompare ) const;

    virtual void calculate( const evol::Subject& toCalculate );

    int getTimeTotal();
    
    std::unique_ptr<evol::FitnessFunction> clone() const ;

    virtual void print();
};
