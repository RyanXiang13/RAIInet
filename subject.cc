#include "subject.h"
#include "observer.h"

void Subject::attach(std::unique_ptr<Observer> o) {
  observers.emplace_back(o); // add observer to subject
}

void Subject::detach(std::unique_ptr<Observer> o) {
  for (auto it = observers.begin(); it != observers.end(); ++it) {
    if (*it == o) {
      observers.erase(it); // Remove the observer from subject
      break;
    }
  }
}
