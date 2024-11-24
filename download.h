#ifndef DOWNLOAD_H
#define DOWNLOAD_H
#include "ability.h"
#include <memory>
#include "link.h"
#include <vector>

class Download : public Ability
{
private:
    Download(int playerID = -1, bool isActive = false, bool isUsed = false);

public:
    static std::unique_ptr<Download> create(int playerID = -1, bool isActive = false, bool isUsed = false);
    void use(std::unique_ptr<Link> l, std::unique_ptr<Cell> c, const std::vector<std::unique_ptr<Player>> &players) override;
};

#endif
