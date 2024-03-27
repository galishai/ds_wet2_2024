//
// Created by Gal Ishai on 3/15/24.
//

#ifndef WET_2_TEAMBYID_H
#define WET_2_TEAMBYID_H

#include "Team.h"



class TeamByID: public Team
{
public:
    explicit TeamByID(int teamID, int wins = 0, int power = 0): Team(teamID, wins, power)
    {
    };

    ~TeamByID()
    {
        delete m_playersByCreated;
        delete m_playersByStrength;
    }

    explicit TeamByID(TeamByID *other): Team(other)
    {
        m_teamID = other->m_teamID;
        m_wins = other->m_wins;
        m_power = other->m_power;
        m_playersByCreated = nullptr;
        m_playersByStrength = nullptr;
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
        if(m_teamID < other->m_teamID)
        {
            return true;
        }
        return false;
    }
};

#endif //WET_2_TEAMBYID_H
