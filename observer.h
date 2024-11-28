#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include "subject.h"

class Subject;
class Observer
{
public:
    virtual void notify(Subject &subject) = 0;
    virtual ~Observer() = default;
};

#endif
