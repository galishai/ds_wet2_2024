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

    virtual ~TeamByID();

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
