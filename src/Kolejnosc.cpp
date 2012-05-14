#include "Kolejnosc.h"
#include "ZarzadcaZadan.hpp"
#include "EvolFunctions.hpp"

#include <algorithm>
#include <cassert>

Kolejnosc::Kolejnosc()
{
    int zadan = ZarzadcaZadan::getInstance().getIloscZadan();
    for(int i=0; i<zadan; ++i)
    {
        kolejnosc_.push_back(i);
    }
}

Kolejnosc::Kolejnosc(const Kolejnosc& toCpy)
{
    for( int i : toCpy.kolejnosc_ )
    {
        kolejnosc_.push_back(i);   
    }   
}

evol::ChromosomePtr Kolejnosc::crossWith(evol::ChromosomePtr toCross) const
{
    std::vector<int> sequence(kolejnosc_.size());
    std::vector<int> notUsed;
    unsigned int i = 0;
    for(auto& elem : sequence)
    {
        elem = i;
        notUsed.push_back(i);
        ++i;
    }
    std::random_shuffle(sequence.begin(),sequence.end());
    Kolejnosc *newKolejnosc = new Kolejnosc();
    assert(newKolejnosc != NULL && "Allocation failure.");
    std::vector<int>& k = newKolejnosc->kolejnosc_;
    for(auto& elem : sequence)
    {
        int parentA = evol::EvolFunctions::ptr_cast<evol::ChromosomePtr,Kolejnosc>(toCross)->kolejnosc_[elem];
        int parentB = kolejnosc_[elem];
        bool aAvailable = (std::find(k.begin(),k.end(),parentA) != k.end());
        bool bAvailable = (std::find(k.begin(),k.end(),parentB) != k.end());
        
        if(aAvailable && bAvailable)
        {
            k[elem]  = (evol::EvolFunctions::random()>0.5) ? parentA : parentB;
        }
        else if(aAvailable)
        {
            k[elem] = parentA;
        }
        else if(bAvailable)
        {
            k[elem] = parentB;
        }
        else
        {
            unsigned int position = evol::EvolFunctions::random(0,notUsed.size()-1);
            k[elem] = *(notUsed.begin()+position);
        }
        notUsed.erase(std::find(notUsed.begin(),notUsed.end(),elem));
    }
    assert(notUsed.empty() && "Each element should be taken.");
    assert(k.size() == kolejnosc_.size() && "Size of kolejnosc should be the same, after crossover.");
    return evol::ChromosomePtr(newKolejnosc);
}

void Kolejnosc::mutate()
{
    // FIXME implement this
}

evol::ChromosomePtr Kolejnosc::clone()
{
    return evol::ChromosomePtr(new Kolejnosc(*this));
}

const std::vector<int>& Kolejnosc::operator*() const 
{
    return kolejnosc_;
}

