#include "Maszyna.h"
#include "ZarzadcaZadan.hpp"
#include "debug.h"
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
    V("Przesuwam czas o ", time);
    V("Maszyna: ", id);
 
    if(zadanie==-1)
    {
        if(!bufor.empty())
        {
            M("Wyciagam z bufora...");
            zadanie=bufor.front();
            V("Nowe zadanie", zadanie);
            bufor.pop();
            timeLeft = ZarzadcaZadan::getInstance().czasObrobki(id,zadanie);            
        }
    }
    else
    {
        timeLeft -= time;
        assert( timeLeft >= 0 && "Wybrano nienajkrotsze zadanie");
        if(timeLeft == 0)
        {
            V("Zadanie zakonczone ", zadanie);
            int completed = zadanie;           
            if( !bufor.empty() )
            {
                M("Wyciagam z bufora...");
                zadanie = bufor.front();
                bufor.pop();
                V("Nowe zadanie", zadanie);
                timeLeft = ZarzadcaZadan::getInstance().czasObrobki(id,zadanie);
            }
            else
            {
                zadanie = -1;
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
