#pragma once
#include <list>

class Maszyna
{
    int zadanie;
    int id;
    unsigned int time_left;
    std::quque<int> bufor;
    addZadanie(int zadanie);
    rollTime(int time);
    getTimeLeft();
}
