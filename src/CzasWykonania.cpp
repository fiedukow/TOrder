#include "CzasWykonania.h"
#include "Population.hpp"
#include "ZarzadcaZadan.hpp"
#include "Plan.h"
#include "Maszyna.h"

CzasWykonania::CzasWykonania( int timeTotal_ ) : timeTotal(timeTotal_)
{}

CzasWykonania::CzasWykonania() : timeTotal(0)
{}

bool CzasWykonania::operator > ( const evol::FitnessFunction& toCompare ) const
{
    return timeTotal > ((CzasWykonania&)toCompare).timeTotal;
}

bool CzasWykonania::operator == ( const evol::FitnessFunction& toCompare ) const
{
    return timeTotal == ((CzasWykonania&)toCompare).timeTotal;
}

void CzasWykonania::calculate( const evol::Subject& toCalculate )
{
    const Plan& plan = (Plan&)toCalculate; 
    timeTotal = 0;
    std::queue<int, std::list<int>> queue(plan.getKolejnosc());
    std::vector<Maszyna*> maszyny;
    for(int i = 0; i < ZarzadcaZadan::getInstance().getIloscMaszyn(); ++i)
        maszyny.push_back(new Maszyna(i));
    
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
        for(int i = 0; i < ZarzadcaZadan::getInstance().getIloscMaszyn(); ++i)        
        {
            if( (maszyny[i]->hasZadanie())
                && ((maszyny[i]->getTimeLeft() < min) || !min))               
            {
                    min = maszyny[i]->getTimeLeft();                                       
            }
        }

        if( min )
        {
            int toRoll = boost::get<int>(min);
            for(int i = 0; i < ZarzadcaZadan::getInstance().getIloscMaszyn(); ++i)
            {
                boost::optional<int> toAdd = maszyny[i]->rollTime(toRoll);
                if(toAdd && ((i+1) < ZarzadcaZadan::getInstance().getIloscMaszyn()))
                {
                    maszyny[i]->addZadanie(boost::get<int>(toAdd));
                }
            }
            timeTotal += toRoll;
        }
    
    }while( min );
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
