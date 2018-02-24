#ifndef CREATURE_MANAGER_H
#define CREATURE_MANAGER_H

#include "globals.hpp"
#include "util/sigletion.hpp"
#include <map>

BEGIN_MEATBALL_NAMESPC

class Player;
class Monster;

class CreatureManager : public Singleton<CreatureManager>
{
public:
    CreatureManager();
    virtual ~CreatureManager();

    virtual int32_t Update();

private:
    std::map<uint64_t, Player*>     mPlayerMap;
    std::map<uint64_t, Monster*>    mMonsterMap;
};

END_MEATBALL_NAMESPC

#endif
