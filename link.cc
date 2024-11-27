#include "link.h";
std::string Link::getName() const {
  if (isVirus) {
    return "V" + strength;
  } else {
    return "D" + strength;
  }
}
