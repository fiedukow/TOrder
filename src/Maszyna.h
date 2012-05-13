#pragma once
#include <queue>
#include <boost/optional.hpp>
#include <memory>

class Maszyna
{
    int id;
    int zadanie;
    int timeLeft;
    std::queue<int> bufor;

    public:
    typedef std::shared_ptr<Maszyna> MPtr; 
    Maszyna(int id_);
    void addZadanie(int zadanie);
    boost::optional<int> rollTime(int time);
    int getTimeLeft();
    bool hasZadanie();
};
