#include "olympics24a2.h"
#include <iostream>

bool isValid(Node<PlayerByCreated> *node)
{
    if(node == nullptr)
    {
        return true;
    }

    isValid(node->m_left);
    //assert(node->m_info != nullptr);
    isValid(node->m_right);

}

olympics_t::olympics_t()
{
    //m_timestamp = 0;
    m_highestRank = -1;
    m_teamsHash = new DynamicHashTable();
    m_teamsByID = new AVLRankTree<TeamByID>();
    m_teamsByPower = new AVLRankTreePower();
	// TODO: Your code goes here
}

olympics_t::~olympics_t()
{
    delete m_teamsHash;
    delete m_teamsByID;
    delete m_teamsByPower;
	// TODO: Your code goes here
}


StatusType olympics_t::add_team(int teamId)
{
    /*if(teamId == 6624)
    {
        int a = 1;
    }
    TeamByID find(2983);
    if(m_teamsHash->find(2983)!= nullptr)
    {
        int hash_wins = m_teamsHash->find(2983)->m_hashwins;
    }
    Node<TeamByID>* n8 = m_teamsByID->findNode(&find);
    if(n8 != nullptr)
    {
        TeamByPower findp(2983, n8->m_info->m_wins, n8->m_info->m_power);
        Node<TeamByPower> *found = m_teamsByPower->findNode(&findp);
        if(found != nullptr)
        {
            int sum_extra = m_teamsByPower->getAddedWins(found->m_info);
            int total_wins = sum_extra + found->m_info->m_wins;
            if(total_wins != 4)
            {
                int a = 1;
            }
        }
    }*/
    if(teamId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    if(m_teamsHash->find(teamId) != nullptr)
    {
        return StatusType::FAILURE;
    }
    try
    {
        TeamByID* newTeam = new TeamByID(teamId);
        m_teamsHash->insert(teamId, newTeam);
        if(m_highestRank == -1)
        {
            m_highestRank = 0;
        }
    }catch(std::bad_alloc&)
    {
        return StatusType::ALLOCATION_ERROR;
    }
	return StatusType::SUCCESS;
}

StatusType olympics_t::remove_team(int teamId)
{
    if(teamId == 21)
    {
        int a = 1;
    }
    /*TeamByID find(2983);
    Node<TeamByID>* n8 = m_teamsByID->findNode(&find);
    if(n8 != nullptr)
    {
        TeamByPower findp(2983, n8->m_info->m_wins, n8->m_info->m_power);
        Node<TeamByPower> *found = m_teamsByPower->findNode(&findp);
        if(found != nullptr)
        {
            int sum_extra = m_teamsByPower->getAddedWins(found->m_info);
            int total_wins = sum_extra + found->m_info->m_wins;
            if(total_wins != 4)
            {
                int a = 1;
            }
        }
    }*/
	if(teamId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    if(m_teamsHash->find(teamId) == nullptr)
    {
        return StatusType::FAILURE;
    }
    if(m_teamsByID->m_treeSize > 1)
    {
        m_teamsByPower->updateMaxRec(m_teamsByPower->select(m_teamsByPower->m_root,m_teamsByPower->m_treeSize));
        m_teamsByPower->updateMaxRec(m_teamsByPower->select(m_teamsByPower->m_root,m_teamsByPower->m_treeSize - 1));
    }
    else if(m_teamsByID->m_treeSize == 1)
    {
        m_teamsByPower->updateMaxRec(m_teamsByPower->select(m_teamsByPower->m_root,m_teamsByPower->m_treeSize));
    }
    m_teamsHash->remove(teamId);
    TeamByID teamIDFinder(teamId);
    Node<TeamByID>* team = m_teamsByID->findNode(&teamIDFinder);
    if(team != nullptr)
    {
        TeamByPower teamPowerFinder(teamId, team->m_info->m_power);
        m_teamsByID->removeNode(&teamIDFinder);
        m_teamsByPower->removeNode(&teamPowerFinder);
        if(m_teamsByPower->m_treeSize >= 1)
        {
            Node<TeamByPower> *maxPower = maxNode(m_teamsByPower->m_root);
            m_teamsByPower->updateMaxRec(maxPower);
        }
    }
    if(m_teamsHash->m_occupancy == 0)
    {
        m_highestRank = -1;
    }
    else if(m_teamsByID->m_treeSize == 0)
    {
        m_highestRank = 0;
    }
    else
    {
        m_highestRank = m_teamsByPower->m_root->m_maxRank;
    }
    if(m_teamsByID->m_treeSize > 1)
    {
        m_teamsByPower->updateMaxRec(m_teamsByPower->select(m_teamsByPower->m_root,m_teamsByPower->m_treeSize));
        m_teamsByPower->updateMaxRec(m_teamsByPower->select(m_teamsByPower->m_root,m_teamsByPower->m_treeSize - 1));
    }
    else if(m_teamsByID->m_treeSize == 1)
    {
        m_teamsByPower->updateMaxRec(m_teamsByPower->select(m_teamsByPower->m_root,m_teamsByPower->m_treeSize));
    }
    if(m_teamsByPower->m_root != nullptr)
    {
        m_highestRank = m_teamsByPower->m_root->m_maxRank;
    }
	return StatusType::SUCCESS;
}

StatusType olympics_t::add_player(int teamId, int playerStrength)
{
    /*TeamByID find(2983);
    Node<TeamByID>* n8 = m_teamsByID->findNode(&find);
    if(n8 != nullptr)
    {
        TeamByPower findp(2983, n8->m_info->m_wins, n8->m_info->m_power);
        Node<TeamByPower> *found = m_teamsByPower->findNode(&findp);
        if(found != nullptr)
        {
            int sum_extra = m_teamsByPower->getAddedWins(found->m_info);
            int total_wins = sum_extra + found->m_info->m_wins;
            if(total_wins != 4)
            {
                int a = 1;
            }
        }
    }*/
    if(teamId <= 0 || playerStrength <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    TeamByID *teamInHash = m_teamsHash->find(teamId);
    if(teamInHash == nullptr)
    {
        return StatusType::FAILURE;
    }
    TeamByID teamFinder(teamId);
    if(m_teamsByID->findNode(&teamFinder) == nullptr)
    {
        try
        {
            TeamByID* newteam = new TeamByID(teamId, teamInHash->m_hashwins, playerStrength);
            m_teamsByID->insertNode(newteam);
        }catch(std::bad_alloc&)
        {
            return StatusType::ALLOCATION_ERROR;
        }
    }
    Node<TeamByID>* team = m_teamsByID->findNode(&teamFinder);
    isValid(team->m_info->m_playersByCreated->m_root);
    try
    {
        PlayerByCreated *playerbycreated = new PlayerByCreated(team->m_info->m_player_count, playerStrength);
        team->m_info->m_playersByCreated->insertNode(playerbycreated);
        PlayerByStrength *playerbystrength = new PlayerByStrength(team->m_info->m_player_count, playerStrength);
        team->m_info->m_playersByStrength->insertNode(playerbystrength);
    }catch(std::bad_alloc&)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    team->m_info->m_player_count++;
    isValid(team->m_info->m_playersByCreated->m_root);
    TeamByPower teamPowerFinder(teamId, team->m_info->m_power);
    Node<TeamByPower> *teampow = m_teamsByPower->findNode(&teamPowerFinder);
    int original_wins;
    if(teampow == nullptr)
    {
        original_wins = teamInHash->m_hashwins;
    }
    else
    {
        int added_wins = m_teamsByPower->getAddedWins(teampow->m_info);
        original_wins = added_wins;
    }
    m_teamsByPower->removeNode(&teamPowerFinder);

    team->m_info->updateMedianAndPower();
    TeamByPower* updatedTeamPower = new TeamByPower(teamId, team->m_info->m_power);
    m_teamsByPower->insertNode(updatedTeamPower,original_wins);

    Node<TeamByPower>* temp =  m_teamsByPower->findNode(updatedTeamPower);
    temp->m_maxRank = updatedTeamPower->m_power + m_teamsByPower->getAddedWins(temp->m_info);
    m_teamsByPower->updateMaxRec(temp);
    m_highestRank = m_teamsByPower->m_root->m_maxRank;

    isValid(team->m_info->m_playersByCreated->m_root);
    if(m_teamsByID->m_treeSize > 1)
    {
        m_teamsByPower->updateMaxRec(m_teamsByPower->select(m_teamsByPower->m_root,m_teamsByPower->m_treeSize));
        m_teamsByPower->updateMaxRec(m_teamsByPower->select(m_teamsByPower->m_root,m_teamsByPower->m_treeSize - 1));
    }
    else if(m_teamsByID->m_treeSize == 1)
    {
        m_teamsByPower->updateMaxRec(m_teamsByPower->select(m_teamsByPower->m_root,m_teamsByPower->m_treeSize));
    }
    if(m_teamsByPower->m_root != nullptr)
    {
        m_highestRank = m_teamsByPower->m_root->m_maxRank;
    }

	return StatusType::SUCCESS;
}

StatusType olympics_t::remove_newest_player(int teamId)
{
    /*if(teamId == 2983)
    {
        int a = 1;
    }
    TeamByID find(2983);
    Node<TeamByID>* n8 = m_teamsByID->findNode(&find);
    if(n8 != nullptr)
    {
        TeamByPower findp(2983, n8->m_info->m_wins, n8->m_info->m_power);
        Node<TeamByPower> *found = m_teamsByPower->findNode(&findp);
        if(found != nullptr)
        {
            int sum_extra = m_teamsByPower->getAddedWins(found->m_info);
            int total_wins = sum_extra + found->m_info->m_wins;
            if(total_wins != 4)
            {
                int a = 1;
            }
        }
    }*/
	if(teamId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    TeamByID teamFinder(teamId);
    Node<TeamByID>* team = m_teamsByID->findNode(&teamFinder);
    if(team == nullptr)
    {
        return StatusType::FAILURE;
    }
    if(m_teamsByID->m_treeSize > 1)
    {
        m_teamsByPower->updateMaxRec(m_teamsByPower->select(m_teamsByPower->m_root,m_teamsByPower->m_treeSize));
        m_teamsByPower->updateMaxRec(m_teamsByPower->select(m_teamsByPower->m_root,m_teamsByPower->m_treeSize - 1));
    }
    else if(m_teamsByID->m_treeSize == 1)
    {
        m_teamsByPower->updateMaxRec(m_teamsByPower->select(m_teamsByPower->m_root,m_teamsByPower->m_treeSize));
    }
    PlayerByCreated* newest = maxNode(team->m_info->m_playersByCreated->m_root)->m_info;
    PlayerByStrength strcopy(newest->m_created, newest->m_strength);
    team->m_info->m_playersByCreated->removeNode(newest);
    team->m_info->m_playersByStrength->removeNode(&strcopy);
    team->m_info->m_player_count--;
    TeamByPower teamPowerFinder(teamId, team->m_info->m_power);
    TeamByPower *teambypow = m_teamsByPower->findNode(&teamPowerFinder)->m_info;
    if(team->m_info->m_playersByCreated->m_treeSize == 0)
    {
        int added_wins = m_teamsByPower->getAddedWins(teambypow);
        m_teamsHash->find(teamId)->m_hashwins = added_wins;
        m_teamsByID->removeNode(team->m_info);
        m_teamsByPower->removeNode(&teamPowerFinder);
    }
    else
    {
        int original_wins;
        TeamByPower* teampow = m_teamsByPower->findNode(&teamPowerFinder)->m_info;
        original_wins = m_teamsByPower->getAddedWins(teampow);
        m_teamsByPower->removeNode(&teamPowerFinder);
        team->m_info->updateMedianAndPower();
        TeamByPower *updatedPower = new TeamByPower(teamId, team->m_info->m_power);
        m_teamsByPower->insertNode(updatedPower,original_wins);
        Node<TeamByPower>* temp =  m_teamsByPower->findNode(updatedPower);
        temp->m_maxRank = updatedPower->m_power + m_teamsByPower->getAddedWins(temp->m_info); //TODO is temp always a leaf?
        m_teamsByPower->updateMaxRec(temp);
        isValid(team->m_info->m_playersByCreated->m_root);
    }
    if(m_teamsByID->m_treeSize == 0)
    {
        m_highestRank = 0;
    }
    else
    {
        m_highestRank = m_teamsByPower->m_root->m_maxRank;
    }
    if(m_teamsByID->m_treeSize > 1)
    {
        m_teamsByPower->updateMaxRec(m_teamsByPower->select(m_teamsByPower->m_root,m_teamsByPower->m_treeSize));
        m_teamsByPower->updateMaxRec(m_teamsByPower->select(m_teamsByPower->m_root,m_teamsByPower->m_treeSize - 1));
    }
    else if(m_teamsByID->m_treeSize == 1)
    {
        m_teamsByPower->updateMaxRec(m_teamsByPower->select(m_teamsByPower->m_root,m_teamsByPower->m_treeSize));
    }
    if(m_teamsByPower->m_root != nullptr)
    {
        m_highestRank = m_teamsByPower->m_root->m_maxRank;
    }
	return StatusType::SUCCESS;

    //TODO update median and power of rankteam
}

output_t<int> olympics_t::play_match(int teamId1, int teamId2)
{
    /*TeamByID find(2983);
    Node<TeamByID>* n8 = m_teamsByID->findNode(&find);
    if(n8 != nullptr)
    {
        TeamByPower findp(2983, n8->m_info->m_wins, n8->m_info->m_power);
        Node<TeamByPower> *found = m_teamsByPower->findNode(&findp);
        if(found != nullptr)
        {
            int sum_extra = m_teamsByPower->getAddedWins(found->m_info);
            int total_wins = sum_extra + found->m_info->m_wins;
            if(total_wins != 4)
            {
                int a = 1;
            }
        }
    }*/
    if(teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2)
    {
        return StatusType::INVALID_INPUT;
    }
    TeamByID teamFinder1(teamId1);
    TeamByID teamFinder2(teamId2);
    Node<TeamByID>* team1 = m_teamsByID->findNode(&teamFinder1);
    Node<TeamByID>* team2 = m_teamsByID->findNode(&teamFinder2);
    if(team1 == nullptr || team2 == nullptr)
    {
        return StatusType::FAILURE;
    }
    if(teamId1 == 8 || teamId2 == 8)
    {
        int a = 1;
    }
    TeamByPower teamPowerFinder1(teamId1, team1->m_info->m_power);
    TeamByPower teamPowerFinder2(teamId2, team2->m_info->m_power);
    Node<TeamByPower> *team1Power = m_teamsByPower->findNode(&teamPowerFinder1);
    Node<TeamByPower> *team2Power = m_teamsByPower->findNode(&teamPowerFinder2);
    int added_wins = m_teamsByPower->getAddedWins(team1Power->m_info);
    int winningID;
    if(team1->m_info->m_power > team2->m_info->m_power)
    {
        //team1->m_info->m_wins++;
        m_teamsByPower->addWins(team1Power,1);
        //team1Power->m_wins++;
        winningID = teamId1;
        m_teamsHash->find(teamId1)->m_hashwins++;
    }
    else if(team1->m_info->m_power < team2->m_info->m_power)
    {
        //team2->m_info->m_wins++;
        m_teamsByPower->addWins(team2Power,1);
        //team2Power->m_wins++;
        winningID = teamId2;
        m_teamsHash->find(teamId2)->m_hashwins++;
    }
    else
    {
        if(teamId1 < teamId2)
        {
            //team1->m_info->m_wins++;
            //team1Power->m_wins++;
            m_teamsByPower->addWins(team1Power,1);
            winningID = teamId1;
            m_teamsHash->find(teamId1)->m_hashwins++;
        }
        else
        {
            //team2->m_info->m_wins++;
            //team2Power->m_wins++;
            m_teamsByPower->addWins(team2Power,1);
            winningID = teamId2;
            m_teamsHash->find(teamId2)->m_hashwins++;
        }
    }
    team1Power->m_maxRank =  team1Power->m_info->m_power + m_teamsByPower->getAddedWins(team1Power->m_info);
    m_teamsByPower->updateMaxRec(team1Power);
    team2Power->m_maxRank = team2Power->m_info->m_power + m_teamsByPower->getAddedWins(team2Power->m_info);
    m_teamsByPower->updateMaxRec(team2Power);
    m_highestRank = m_teamsByPower->m_root->m_maxRank;
    if(m_teamsByID->m_treeSize > 1)
    {
        m_teamsByPower->updateMaxRec(m_teamsByPower->select(m_teamsByPower->m_root,m_teamsByPower->m_treeSize));
        m_teamsByPower->updateMaxRec(m_teamsByPower->select(m_teamsByPower->m_root,m_teamsByPower->m_treeSize - 1));
    }
    else if(m_teamsByID->m_treeSize == 1)
    {
        m_teamsByPower->updateMaxRec(m_teamsByPower->select(m_teamsByPower->m_root,m_teamsByPower->m_treeSize));
    }
    if(m_teamsByPower->m_root != nullptr)
    {
        m_highestRank = m_teamsByPower->m_root->m_maxRank;
    }
    return winningID;
}

output_t<int> olympics_t::num_wins_for_team(int teamId)
{
    /*TeamByID find(2983);
    Node<TeamByID>* n8 = m_teamsByID->findNode(&find);
    if(teamId == 2983)
    {
        if (n8 != nullptr)
        {
            TeamByPower findp(2983, n8->m_info->m_wins, n8->m_info->m_power);
            Node<TeamByPower> *found = m_teamsByPower->findNode(&findp);
            if (found != nullptr)
            {
                int sum_extra = m_teamsByPower->getAddedWins(found->m_info);
                int total_wins = sum_extra + found->m_info->m_wins;
                if (total_wins != 4)
                {
                    int a = 1;
                }
            }
        }
    }*/
    if(teamId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    if(m_teamsHash->find(teamId) == nullptr)
    {
        return StatusType::FAILURE;
    }
    TeamByID teamIDFinder(teamId);
    Node<TeamByID> *team = m_teamsByID->findNode(&teamIDFinder);
    if(team == nullptr)
    {
        return m_teamsHash->find(teamId)->m_hashwins;
    }
    TeamByPower teamPowerFinder(teamId, team->m_info->m_power);
    TeamByPower *teamByPower = m_teamsByPower->findNode(&teamPowerFinder)->m_info;
    int added_wins = m_teamsByPower->getAddedWins(teamByPower);
    return added_wins;
}

output_t<int> olympics_t::get_highest_ranked_team()
{
    //std::cout << "max power id: " << maxNode(m_teamsByPower.m_root)->m_info->m_teamID << '\n';
    //std::cout << "max power: " << maxNode(m_teamsByPower.m_root)->m_info->m_power << '\n';
    if(m_teamsHash->m_occupancy == 0)
    {
        return -1;
    }
    if(m_teamsByPower->m_treeSize == 0)
    {
        return 0;
    }
    return m_teamsByPower->m_root->m_maxRank + m_teamsByPower->m_root->m_extra;
}

StatusType olympics_t::unite_teams(int teamId1, int teamId2)
{
    /*TeamByID find(2983);
    Node<TeamByID>* n8 = m_teamsByID->findNode(&find);
    if(n8 != nullptr)
    {
        TeamByPower findp(2983, n8->m_info->m_wins, n8->m_info->m_power);
        Node<TeamByPower> *found = m_teamsByPower->findNode(&findp);
        if(found != nullptr)
        {
            int sum_extra = m_teamsByPower->getAddedWins(found->m_info);
            int total_wins = sum_extra + found->m_info->m_wins;
            if(total_wins != 4)
            {
                int a = 1;
            }
        }
    }*/
	if(teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2)
    {
        return StatusType::INVALID_INPUT;
    }
    TeamByID teamFinder1(teamId1);
    TeamByID teamFinder2(teamId2);
    TeamByID *team1hash = m_teamsHash->find(teamId1);
    TeamByID *team2hash = m_teamsHash->find(teamId2);
    if(team1hash == nullptr || team2hash == nullptr)
    {
        return StatusType::FAILURE;
    }
    Node<TeamByID>* team1 = m_teamsByID->findNode(&teamFinder1);
    Node<TeamByID>* team2 = m_teamsByID->findNode(&teamFinder2);
    if(team2 == nullptr)
    {
        m_teamsHash->remove(teamId2);
        return StatusType::SUCCESS;
    }
    else if(team1 == nullptr)
    {
        TeamByID *team1new = new TeamByID(teamId1, team1hash->m_hashwins, team1hash->m_power);
        m_teamsByID->insertNode(team1new);
        team1 = m_teamsByID->findNode(team1new);
    }
    isValid(team1->m_info->m_playersByCreated->m_root);
    isValid(team2->m_info->m_playersByCreated->m_root);
    TeamByPower team1PowerFinder(teamId1, team1->m_info->m_power);
    TeamByPower team2PowerFinder(teamId2, team2->m_info->m_power);
    Node<TeamByPower> *team1pow = m_teamsByPower->findNode(&team1PowerFinder);
    int original_wins;
    if(team1pow == nullptr)
    {
        original_wins = team1hash->m_hashwins;
    }
    else
    {
        original_wins = m_teamsByPower->getAddedWins(team1pow->m_info);
    }
    Node<TeamByPower> *team2pow = m_teamsByPower->findNode(&team2PowerFinder);
    m_teamsByPower->removeNode(&team1PowerFinder);
    m_teamsByPower->removeNode(&team2PowerFinder);
    int sizeOfArray1 = 0;
    if(team1 != nullptr)
    {
        sizeOfArray1 = team1->m_info->m_playersByCreated->m_treeSize;
    }
    int sizeOfArray2 = team2->m_info->m_playersByCreated->m_treeSize;

    PlayerByCreated **arrayCreated1;
    PlayerByCreated **arrayCreated2;
    PlayerByCreated **arrayMergedCreated;
    PlayerByStrength **arrayStrength1;
    PlayerByStrength **arrayStrength2;
    PlayerByStrength **arrayMergedStrength;

    try
    {
        arrayCreated1 = new PlayerByCreated *[sizeOfArray1];
        arrayCreated2 = new PlayerByCreated *[sizeOfArray2];
        arrayMergedCreated = new PlayerByCreated *[sizeOfArray1+sizeOfArray2];
        arrayStrength1 = new PlayerByStrength *[sizeOfArray1];
        arrayStrength2 = new PlayerByStrength *[sizeOfArray2];
        arrayMergedStrength = new PlayerByStrength *[sizeOfArray1+sizeOfArray2];
    } catch (std::bad_alloc &)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    InorderTransversalIntoArray(team1->m_info->m_playersByCreated->m_root, arrayCreated1, sizeOfArray1, 0);
    InorderTransversalIntoArray(team2->m_info->m_playersByCreated->m_root, arrayCreated2, sizeOfArray2, 0);
    InorderTransversalIntoArray(team1->m_info->m_playersByStrength->m_root, arrayStrength1, sizeOfArray1, 0);
    InorderTransversalIntoArray(team2->m_info->m_playersByStrength->m_root, arrayStrength2, sizeOfArray2, 0);
    int inc;
    if(team1->m_info->m_playersByCreated->m_treeSize == 0)
    {
        inc = 0;
    }
    else
    {
        inc = team1->m_info->m_player_count;
        // maxNode(team1->m_info->m_playersByCreated->m_root)->m_info->m_created;
    }
    for(int i = 0; i < sizeOfArray2; i++)
    {
        arrayCreated2[i]->m_created += inc;
        arrayStrength2[i]->m_created += inc;
    }
    team1->m_info->m_player_count = team1->m_info->m_player_count + team2->m_info->m_player_count;
    mergeTwoArraysIntoOne(arrayCreated1, arrayCreated2, arrayMergedCreated, sizeOfArray1, sizeOfArray2);
    mergeTwoArraysIntoOne(arrayStrength1, arrayStrength2, arrayMergedStrength, sizeOfArray1, sizeOfArray2);

    Node<PlayerByCreated> *newRootCreated = mergedArrayIntoBalTree(arrayMergedCreated, 0, sizeOfArray1 + sizeOfArray2 - 1);
    Node<PlayerByStrength> *newRootStrength = mergedArrayIntoBalTree(arrayMergedStrength, 0, sizeOfArray1 + sizeOfArray2 - 1);
    isValid(newRootCreated);
    delete team1->m_info->m_playersByStrength;
    delete team1->m_info->m_playersByCreated;

    team1->m_info->m_playersByCreated = new AVLRankTree<PlayerByCreated>();
    team1->m_info->m_playersByStrength = new AVLRankTree<PlayerByStrength>();
    team1->m_info->m_playersByCreated->m_root = newRootCreated;
    team1->m_info->m_playersByStrength->m_root = newRootStrength;
    team1->m_info->m_playersByCreated->m_treeSize = sizeOfArray1 + sizeOfArray2;
    team1->m_info->m_playersByStrength->m_treeSize = sizeOfArray1 + sizeOfArray2;
    //team2->m_info->m_playersByCreated->m_root = nullptr;
    //team2->m_info->m_playersByStrength->m_root = nullptr;
    m_teamsByID->removeNode(team2->m_info);
    team1->m_info->updateMedianAndPower();
    TeamByPower *updatedTeamPower1 = new TeamByPower(team1->m_info->m_teamID, team1->m_info->m_power);
    m_teamsByPower->insertNode(updatedTeamPower1, original_wins);
    m_teamsHash->remove(teamId2);
    m_highestRank = m_teamsByPower->m_root->m_maxRank;
    /*for(int i = 0; i < sizeOfArray1 + sizeOfArray2; i++)
    {
        delete arrayMergedCreated[i];
        delete arrayMergedStrength[i];
    }*/
    /*for(int i = 0; i < sizeOfArray1; i++)
    {
        delete arrayCreated1[i];
        delete arrayStrength1[i];
    }*/
    /*for(int i = 0; i < sizeOfArray2; i++)
    {
        delete arrayCreated2[i];
        delete arrayStrength2[i];
    }*/
    delete[] arrayCreated1;
    delete[] arrayCreated2;
    delete[] arrayStrength1;
    delete[] arrayStrength2;
    delete[] arrayMergedCreated;
    delete[] arrayMergedStrength;
    isValid(team1->m_info->m_playersByCreated->m_root);
    if(m_teamsByID->m_treeSize > 1)
    {
        m_teamsByPower->updateMaxRec(m_teamsByPower->select(m_teamsByPower->m_root,m_teamsByPower->m_treeSize));
        m_teamsByPower->updateMaxRec(m_teamsByPower->select(m_teamsByPower->m_root,m_teamsByPower->m_treeSize - 1));
    }
    else if(m_teamsByID->m_treeSize == 1)
    {
        m_teamsByPower->updateMaxRec(m_teamsByPower->select(m_teamsByPower->m_root,m_teamsByPower->m_treeSize));
    }
    /*n8 = m_teamsByID->findNode(&find);
    if(n8 != nullptr)
    {
        TeamByPower findp(2983, n8->m_info->m_wins, n8->m_info->m_power);
        Node<TeamByPower> *found = m_teamsByPower->findNode(&findp);
        if(found != nullptr)
        {
            int sum_extra = m_teamsByPower->getAddedWins(found->m_info);
            int total_wins = sum_extra + found->m_info->m_wins;
            if(total_wins != 4)
            {
                int a = 1;
            }
        }
    }*/
    if(m_teamsByPower->m_root != nullptr)
    {
        m_highestRank = m_teamsByPower->m_root->m_maxRank;
    }
    return StatusType::SUCCESS;
}

output_t<int> olympics_t::play_tournament(int lowPower, int highPower)
{
    TeamByID find(2983);
    Node<TeamByID>* n8 = m_teamsByID->findNode(&find);
    int added_wins;
    /*if(n8 != nullptr)
    {
        TeamByPower findp(8, n8->m_info->m_wins, n8->m_info->m_power);
        Node<TeamByPower> *found = m_teamsByPower->findNode(&findp);
        if(found != nullptr)
        {
            added_wins = m_teamsByPower->getAddedWins(found->m_info);
            int n8rank = m_teamsByPower->rank(found->m_info);
        }
    }*/

    if(lowPower <= 0 || highPower <= 0 || highPower <= lowPower)
    {
        return StatusType::INVALID_INPUT;
    }
    if(m_teamsByID->m_treeSize == 0)
    {
        return StatusType::FAILURE;
    }
    TeamByID *maxIDTeam = maxNode(m_teamsByID->m_root)->m_info;
    Node<TeamByPower> *lowestInRange;
    Node<TeamByPower> *highestInRange;
    TeamByPower *lowPowerTeam = new TeamByPower(maxIDTeam->m_teamID + 1,lowPower);
    m_teamsByPower->insertNode(lowPowerTeam, 0);
    Node<TeamByPower> * lowernode = m_teamsByPower->findNode(lowPowerTeam);

    if (lowernode->m_left != nullptr && lowernode->m_right != nullptr) //if has two sons
    {
        lowestInRange = minNode(lowernode->m_right);
    }

    else if ((lowernode->m_left == nullptr && lowernode->m_right != nullptr)) //if only has right son todo check
    {
        lowestInRange = minNode(lowernode->m_right);
    }

    else if (lowernode->m_left != nullptr && lowernode->m_right == nullptr) //if only has left son
    {
        if (*(maxNode(m_teamsByPower->m_root)->m_info) == lowernode->m_info)
        {
            lowestInRange = nullptr;
        }
        else if(lowernode->m_parent == nullptr)
        {
            lowestInRange = nullptr;
        }
        else if(lowernode->m_parent->m_right == lowernode)
        {
            Node<TeamByPower> *ptr = lowernode;

            while (ptr->m_parent != nullptr && ptr->m_parent->m_right == ptr)
            {
                ptr = ptr->m_parent;
            }
            if (ptr->m_parent != nullptr)
            {
                lowestInRange = ptr->m_parent;
            } else
            {
                lowestInRange = nullptr;
            }
        }else if (lowernode->m_parent->m_left == lowernode)
        {
            lowestInRange = lowernode->m_parent;
        }
    }else
    {
        if (lowernode->m_parent == nullptr) //if player is a leaf (no sons)
        {
            lowestInRange = nullptr;
        } else if (lowernode->m_parent->m_left == lowernode)
        {
            lowestInRange = lowernode->m_parent;
        } else if (lowernode->m_parent->m_right == lowernode)
        {

            Node<TeamByPower> *ptr = lowernode;

            while (ptr->m_parent != nullptr && ptr->m_parent->m_right == ptr)
            {
                ptr = ptr->m_parent;
            }
            if (ptr->m_parent != nullptr)
            {
                lowestInRange = ptr->m_parent;
            } else
            {
                lowestInRange = nullptr;
            }
        }
    }
    m_teamsByPower->removeNode(lowPowerTeam);
    TeamByPower *highPowerTeam = new TeamByPower(-1, highPower);
    m_teamsByPower->insertNode(highPowerTeam, 0);
    Node<TeamByPower> *highernode = m_teamsByPower->findNode(highPowerTeam);

    if (highernode->m_left != nullptr && highernode->m_right != nullptr) //if has two sons
    {
        highestInRange = maxNode(highernode->m_left);

    }

    else if ((highernode->m_left == nullptr && highernode->m_right != nullptr)) //if only has right son todo check
    {
        if (*(minNode(m_teamsByPower->m_root)->m_info) == highernode->m_info)
        {
            highestInRange = nullptr;
        }
        else if(highernode->m_parent == nullptr)
        {
            highestInRange = nullptr;
        }
        else if(highernode->m_parent->m_left == highernode)
        {
            Node<TeamByPower> *ptr = highernode;

            while (ptr->m_parent != nullptr && ptr->m_parent->m_left == ptr)
            {
                ptr = ptr->m_parent;
            }
            if (ptr->m_parent != nullptr)
            {
                highestInRange = ptr->m_parent;
            } else
            {
                highestInRange = nullptr;
            }
        }else if (highernode->m_parent->m_right == highernode)
        {
            highestInRange = highernode->m_parent;
        }
    }
    else
    {
        if (highernode->m_parent == nullptr) //if leaf
        {
            highestInRange = nullptr;
        } else if (highernode->m_parent->m_left == highernode)
        {
            Node<TeamByPower> *ptr = highernode;

            while (ptr->m_parent != nullptr && ptr->m_parent->m_left == ptr)
            {
                ptr = ptr->m_parent;
            }
            if (ptr->m_parent != nullptr)
            {
                highestInRange = ptr->m_parent;
            } else
            {
                highestInRange = nullptr;
            }
        }
        if (highernode->m_parent->m_right == highernode)
        {
            highestInRange = highernode->m_parent;
        }
    }
    m_teamsByPower->removeNode(highPowerTeam);
    if(lowestInRange == nullptr || highestInRange == nullptr)
    {
        return StatusType::FAILURE;
    }

    int lowrank = m_teamsByPower->rank(lowestInRange->m_info);
    int highrank = m_teamsByPower->rank(highestInRange->m_info);


    int num_in_range = highrank - lowrank + 1;
    int temp = num_in_range;
    if(temp == 1)
    {
        return lowestInRange->m_info->m_teamID;
    }
    if(temp == 0)
    {
        return StatusType::FAILURE;
    }
    while(temp != 0)
    {
        if(temp % 2 != 0 && temp != 1)
        {
            return StatusType::FAILURE;
        }
        temp /=2;
    }
    int j = m_teamsByPower->rank(highestInRange->m_info);
    int i = m_teamsByPower->rank(lowestInRange->m_info);
    int middle;
    Node<TeamByPower> *middleTeam = lowestInRange;
    while(num_in_range != 2)
    {
        if (i % 2 == 1 && j % 2 == 0 || j % 2 == 1 && i % 2 == 0)
        {
            middle = i + (j - i) / 2 + 1;
        } else
        {
            middle = i + (j - i) / 2;
        }
        middleTeam = m_teamsByPower->select(m_teamsByPower->m_root, middle - 1);
        m_teamsByPower->addWinsToLessEqual(highestInRange->m_info, 1);
        m_teamsByPower->addWinsToLessEqual(middleTeam->m_info, -1);
        num_in_range /= 2;
        i = middle;
    }
    /*if(n8 != nullptr)
    {
        TeamByPower findp(2983, n8->m_info->m_wins, n8->m_info->m_power);
        Node<TeamByPower> *found = m_teamsByPower->findNode(&findp);
        if(found != nullptr)
        {
            added_wins = m_teamsByPower->getAddedWins(found->m_info);
            int n8rank = m_teamsByPower->rank(found->m_info);
            if(n8rank >= lowrank && n8rank <= highrank)
            {
                int a=1;
            }
        }
    }*/
    if(num_in_range == 2)
    {
        //highestInRange->m_wins ++;
        m_teamsByPower->addWins(highestInRange,1);
        TeamByID winnerFinder(highestInRange->m_info->m_teamID);
        //TeamByID *winnerByID = m_teamsByID->findNode(&winnerFinder)->m_info;
        //winnerByID->m_wins++;
        //Node<TeamByPower> *highestnode = m_teamsByPower->findNode(highestInRange);
        //Node<TeamByPower> *runnerup = m_teamsByPower->findNode(middleTeam);
        highestInRange->m_maxRank = highestInRange->m_info->m_power + m_teamsByPower->getAddedWins(highestInRange->m_info);
        middleTeam->m_maxRank = middleTeam->m_info->m_power + m_teamsByPower->getAddedWins(middleTeam->m_info);
        m_teamsByPower->updateMaxRec(highestInRange);
        m_teamsByPower->updateMaxRec(middleTeam);
    }
    if(m_teamsByID->m_treeSize > 1)
    {
        m_teamsByPower->updateMaxRec(m_teamsByPower->select(m_teamsByPower->m_root,m_teamsByPower->m_treeSize));
        m_teamsByPower->updateMaxRec(m_teamsByPower->select(m_teamsByPower->m_root,m_teamsByPower->m_treeSize - 1));
    }
    else if(m_teamsByID->m_treeSize == 1)
    {
        m_teamsByPower->updateMaxRec(m_teamsByPower->select(m_teamsByPower->m_root,m_teamsByPower->m_treeSize));
    }
    if(m_teamsByPower->m_root != nullptr)
    {
        m_highestRank = m_teamsByPower->m_root->m_maxRank;
    }
    return highestInRange->m_info->m_teamID;
}