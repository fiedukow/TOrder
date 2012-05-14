#ifndef PLAN_H
#define PLAN_H

#include <list>

#include "Subject.hpp"

#include "Kolejnosc.h"

class Plan : public evol::Subject
{
public:
    std::list<int> getKolejnosc() const;
    void setInitialValue();
    evol::SubjectPtr clone() const;
    void print() const;
};

#endif
