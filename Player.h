//
// Created by Gal Ishai on 3/15/24.
//

#ifndef WET_2_PLAYER_H
#define WET_2_PLAYER_H

class Player
{
public:
    int m_created;
    int m_strength;


    Player(int timestamp, int strength)
    {
        m_created = timestamp;
        m_strength = strength;
    }

    virtual bool operator<(Player* other) const = 0;
    bool operator==(Player* other) const
    {
        if(other == nullptr)
        {
            return false;
        }
        if(m_created == other->m_created)
        {
            return true;
        }
        return false;
    }
};

#endif //WET_2_PLAYER_H
