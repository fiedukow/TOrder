#pragma once
#include <queue>
#include <boost/optional.hpp>
#include <memory>

class Maszyna
{
    typedef std::shared_ptr<Maszyna> MPtr; 
    int id;
    int zadanie;
    int timeLeft;
    std::queue<int> bufor;

    public:
    Maszyna(int id_);
    void addZadanie(int zadanie);
    boost::optional<int> rollTime(int time);
    int getTimeLeft();
    bool hasZadanie();
};
