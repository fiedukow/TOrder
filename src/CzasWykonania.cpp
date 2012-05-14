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
    M("Zaczynam liczenie ");

    const Plan& plan = (Plan&)toCalculate; 
    timeTotal = 0;
    std::queue<int, std::list<int>> queue(plan.getKolejnosc());
    std::vector<MPtr> maszyny;

    M("Tworze maszyny...");

    for(int i = 0; i < ZarzadcaZadan::getInstance().getIloscMaszyn(); ++i)
        maszyny.push_back(MPtr(new Maszyna(i)));
    
    M("Dodaje maszyny do pierwszego bufora...");

    for(int i = 0; i < ZarzadcaZadan::getInstance().getIloscZadan(); ++i)
    {
        int biezaceZadanie = queue.front();
        queue.pop();
        maszyny[0]->addZadanie(biezaceZadanie);
    }

    boost::optional<int> min;
    do
    {
        min.reset();

        M("Szukam minimum...");

        for(int i = 0; i < ZarzadcaZadan::getInstance().getIloscMaszyn(); ++i)        
        {
            if( (maszyny[i]->hasZadanie())
                && (!min || (maszyny[i]->getTimeLeft() < min)))               
            {
                    M("Znalazłem minimum");
                    min = maszyny[i]->getTimeLeft();                                       
                    V("Maszyna: ",i);
                    V("Czas: ", boost::get<int>(min));
            }
        }

        if( min )
        {
            int toRoll = boost::get<int>(min);
            V("Przesuwam czas o ", toRoll);
            for(int i = 0; i < ZarzadcaZadan::getInstance().getIloscMaszyn(); ++i)
            {
                assert(i<maszyny.size());
                boost::optional<int> toAdd = maszyny[i]->rollTime(toRoll);
                if(toAdd && ((i+1) < ZarzadcaZadan::getInstance().getIloscMaszyn()))
                {
                    V("Przesuwam zadanie do maszyny nr. ", (i+1));
                    maszyny[i+1]->addZadanie(boost::get<int>(toAdd));
                }
            }
            timeTotal += toRoll;
        }
    
    }while( min );

    M("Koncze liczenie");
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
