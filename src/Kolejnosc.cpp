#include "Kolejnosc.h"
#include "ZarzadcaZadan.hpp"
#include "EvolFunctions.hpp"
#include "Maszyna.h"
#include "debug.h"

#include <queue>
#include <list>
#include <algorithm>
#include <cassert>
#include <map>

Kolejnosc::Kolejnosc()
{
    int zadan = ZarzadcaZadan::getInstance().getIloscZadan();
    for(int i=0; i<zadan; ++i)
    {
        kolejnosc_.push_back(i);
    }
    std::random_shuffle(kolejnosc_.begin(), kolejnosc_.end());
}

Kolejnosc::Kolejnosc(const Kolejnosc& toCpy) : kolejnosc_(toCpy.kolejnosc_)
{}

evol::ChromosomePtr Kolejnosc::crossWith(evol::ChromosomePtr toCross) const
{
    std::map<int,int> notUsed;
    for( int i = 0; i < kolejnosc_.size(); ++i )
        notUsed[i]=i;

    Kolejnosc *newKolejnosc = new Kolejnosc();
    std::vector<int>& k = newKolejnosc->kolejnosc_;
    
    int toAdd;
    double random_value = evol::EvolFunctions::random();
    int max_first = random_value*kolejnosc_.size();
    int i = 0;


    for(; i < max_first; ++i)
    {
        toAdd = kolejnosc_[i];
        k[i] = toAdd;
        notUsed.erase(toAdd);                                           
    }
    int j = 0;
    for(; i < kolejnosc_.size(); ++i,++j)
    {
        std::vector<int>& toCpy = 
            evol::EvolFunctions::ptr_cast<evol::ChromosomePtr, Kolejnosc>(toCross)->kolejnosc_;
        for(; j<toCpy.size(); ++j)
        {
            if(notUsed.find(toCpy[j]) != notUsed.end())
                break;                
        }
        toAdd = toCpy[j];
        k[i] = toAdd;
        notUsed.erase(toAdd);
    }
    return evol::ChromosomePtr(newKolejnosc);

}

void Kolejnosc::mutate()
{
    unsigned int i = kolejnosc_.size()-1;
    for(;i>0;--i)
    {
        if(evol::EvolFunctions::random()<0.1)
        {
            std::swap(kolejnosc_[i],kolejnosc_[evol::EvolFunctions::random(0,kolejnosc_.size()-1)]);
        }
    }
    timeTotal.reset();
}

unsigned int Kolejnosc::getTimeTotal()
{
    if( !timeTotal )
    {
        unsigned int timeTotalV = 0;
        std::queue<int, std::list<int>> queue;

        for( auto& i : kolejnosc_ )
            queue.push(i);

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
                timeTotalV += toRoll;
            }
            
        }while( min );
        timeTotal = timeTotalV;
        M("Koncze liczenie");
    }
    return boost::get<unsigned int>(timeTotal);
}

evol::ChromosomePtr Kolejnosc::clone() const
{
    return evol::ChromosomePtr(new Kolejnosc(*this));
}

const std::vector<int>& Kolejnosc::operator*() const 
{
    return kolejnosc_;
}

