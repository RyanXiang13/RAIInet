#ifndef SCAN_H
#define SCAN_H
#include "ability.h"
#include <memory>
#include "link.h"
#include <vector>

class Scan : public Ability
{
private:
    Scan(int playerID = -1, bool isActive = false, bool isUsed = false);

public:
    static std::unique_ptr<Scan> create(int playerID = -1, bool isActive = false, bool isUsed = false);
    void use(std::unique_ptr<Link> l, std::unique_ptr<Cell> c, const std::vector<std::unique_ptr<Player>> &players) override;
};

#endif
