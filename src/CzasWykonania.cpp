#pragma once
#include "Population.hpp"
#include "ZarzadcaZadan.hpp"
#include "Plan.h"

bool operator > ( const FItnessFunction& toCompare ) const
{
    return timeTotal > toComare.timeTotal;
}

bool operator == ( const FitnessFunction& toCompare ) const
{
    return timeTotal == toCompare.timeTotal;
}

void calculate( const Subject& toCalculate )
{
    const Plan* plan = *toCalculate; 
    timeTotal = 0;
    std::list<int,std::list<int>> queue = plan->getKolejnosc();
    std::vector<MPtr> maszyny;
    for(int i = 0; i < ZarzadcaZadan::getInstance().getIloscMaszyn(); ++i)
        maszyny.push_back(MPtr(new Maszyna(i)));
    
    for(int i = 0; i < ZarzadcaZadan::getInstance().getIloscZadan(); ++i)
    {
        int biezaceZadanie = queue.front();
        queue.pop();
        maszyny[0]->addZadanie(biezaceZadanie);
    }

    do
    {
        boost::optional<int> min;
        for(int i = 0; i < ZarzadcaZadan::getInstance().getIloscMaszyn(); ++i)        
        {
            if(maszyny[i]->hasTask
                && (maszyny[i]->getTimeLeft() < min) || !min )               
            {
                    min = maszyny[i]->getTimeLeft();                                       
            }
        }

        if( min )
        {
            for(int i = 0; i < ZarzadcaZadan::getInstance().getIloscMaszyn(); ++i)
            {
                boost::optional<int> toAdd = maszyny[i]->rollTime(min);
                if(toAdd && ((i+1) < ZarzadcaZadan::getInstance().getIloscMaszyn()))
                {
                    maszyny[i]->addZadanie(toAdd);
                }
            }
            timeTotal+=min;
        }
    
    }while( min );
}
