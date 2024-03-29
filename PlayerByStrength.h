//
// Created by Gal Ishai on 3/16/24.
//

#ifndef WET_2_PLAYERBYSTRENGTH_H
#define WET_2_PLAYERBYSTRENGTH_H

#include "Player.h"

class PlayerByStrength : public Player
{

public:

    PlayerByStrength(int timestamp, int strength): Player(timestamp, strength)
    {
    };

    explicit PlayerByStrength(PlayerByStrength* other): Player(other)
    {}

    bool operator<(Player *other) const override
    {
        if(other == nullptr)
        {
            return false;
        }
        if (m_strength < other->m_strength || (m_strength == other->m_strength && m_created < other->m_created)) {
            return true;
        }
        return false;
    }
};

#endif //WET_2_PLAYERBYSTRENGTH_H
