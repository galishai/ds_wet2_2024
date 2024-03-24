//
// Created by Gal Ishai on 3/16/24.
//

#ifndef WET_2_TEAMBYPOWER_H
#define WET_2_TEAMBYPOWER_H

#include "Team.h"

class TeamByPower: public Team
{
public:
    explicit TeamByPower(int teamID, int wins = 0, int power = 0): Team(teamID, wins, power)
    {
    };

    ~TeamByPower() override
    {
        delete m_playersByCreated;
        delete m_playersByStrength;
    }

    bool operator==(Team* other) const override
    {
        if(other == nullptr)
        {
            return false;
        }
        if(m_teamID == other->m_teamID)
        {
            return true;
        }
        return false;
    }

    bool operator<(Team* other) const override
    {
        if(other == nullptr)
        {
            return false;
        }
        if(m_power < other->m_power)
        {
            return true;
        }
        else if(m_power == other->m_power)
        {
            if(m_teamID > other->m_teamID)
            {
                return true;
            }
        }
        return false;
    }
};

#endif //WET_2_TEAMBYPOWER_H
