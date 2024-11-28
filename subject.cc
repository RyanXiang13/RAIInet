#include "subject.h"
#include "observer.h"

void Subject::attach(std::unique_ptr<Observer> o) {
  observers.emplace_back(std::move(o));
}

void Subject::detach(std::unique_ptr<Observer> o) {
  for (auto it = observers.begin(); it != observers.end(); ++it) {
    if (*it == o) {
      observers.erase(it);
      break;
    }
  }
}

void Subject::notifyObservers(Subject* game) {
  for (const auto& ob : observers) {
    ob->notify(*game);
  }
}
