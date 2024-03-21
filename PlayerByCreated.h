//
// Created by Gal Ishai on 3/15/24.
//

#ifndef WET_2_PLAYERBYCREATED_H
#define WET_2_PLAYERBYCREATED_H

#include "Player.h"

class PlayerByCreated : public Player
{

public:

    PlayerByCreated(int timestamp, int strength): Player(timestamp, strength)
    {
    };

    /*explicit PlayerByCreated(PlayerByCreated* other): Player(other)
    {
        m_statVersionOfPlayer = other->m_statVersionOfPlayer;
        m_playerInGeneralIDTree = other->m_playerInGeneralIDTree;
    }*/

    bool operator<(Player *other) const override
    {
        if(other == nullptr)
        {
            return false;
        }
        if (m_created < other->m_created) {
            return true;
        }
        return false;
    }
};

#endif //WET_2_PLAYERBYCREATED_H
