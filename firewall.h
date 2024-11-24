#ifndef FIREWALL_H
#define FIREWALL_H
#include "ability.h"
#include "cell.h"
#include <memory>
#include <vector>

class Firewall : public Ability
{
private:
    Firewall(int playerID = -1, bool isActive = false, bool isUsed = false);
    char symbol;

public:
    static std::unique_ptr<Firewall> create(int playerID = -1, bool isActive = false, bool isUsed = false);
    char getSymbol() const;
    char setSymbol(char s) const;
    void use(std::unique_ptr<Link> l, std::unique_ptr<Cell> c, const std::vector<std::unique_ptr<Player>> &players) override;
    void activateuse(std::unique_ptr<Link> l, std::unique_ptr<Cell> c, const std::vector<std::unique_ptr<Player>> &players);
};

#endif
