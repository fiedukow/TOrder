#include "Maszyna.h"
#include "ZarzadcaZadan.hpp"
#include <cassert>
#include <boost/optional.hpp>

Maszyna::Maszyna(int id_) : id(id_), zadanie(-1), timeLeft(0)
{}

void Maszyna::addZadanie(int zadanie)
{
    bufor.push(zadanie);
}

boost::optional<int> Maszyna::rollTime(int time)
{
    if( zadanie != -1 )
    {
        timeLeft -= time;
        assert( timeLeft >= 0 && "Wybrano nienajkrotsze zadanie");
        if(timeLeft == 0)
        {
            int completed = zadanie;
            if( !bufor.empty() )
            {
                zadanie = bufor.front();
                bufor.pop();
                timeLeft = ZarzadcaZadan::getInstance().czasObrobki(id,zadanie);
            }
            return completed;
        }
    }
    return boost::optional<int>();
}

int Maszyna::getTimeLeft()
{
    return timeLeft;
}

bool Maszyna::hasZadanie()
{
    return (zadanie>=0 || !bufor.empty());
}
