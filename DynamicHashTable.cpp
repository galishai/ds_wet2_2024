
#include "DynamicHashTable.h"

int DynamicHashTable::hashFunction (int key)
{
    return key % m_size;
}

TeamByID* DynamicHashTable::find(int key)
{
    int index = hashFunction(key);
    //if (m_arr[index] == nullptr)
    //{
     //   return nullptr;
    //}
    TeamByID teamFinder(key);
    Node<TeamByID>* foundteam = m_arr[index].findNode(&teamFinder);
    if(foundteam == nullptr)
    {
        return nullptr;
    }
    return foundteam->m_info;
}

void DynamicHashTable::insert(int key, TeamByID* info)
{
    //shared_ptr<HashNode> nodeToAdd = make_shared<HashNode>(key, info);
    if (m_occupancy + 1 > LOAD_FACTOR * m_size)
    {
        resize();
    }
    int index = hashFunction(key);/////
    //shared_ptr<HashNode> temp = m_arr[index];
    if (m_arr[index].m_treeSize == 0)
    {
        //m_arr[index] = new AVLRankTree<TeamByID>();
        m_occupancy++;
    }
    m_arr[index].insertNode(info);
}

void DynamicHashTable::remove(int key)
{
    if (find(key) == nullptr)
    {
        return;
    }
    else
    {
        int index = hashFunction(key);
        TeamByID teamCopy(key);
        m_arr[index].removeNode(&teamCopy);
        if(m_arr[index].m_treeSize == 0)
        {
            m_occupancy--;
        }
    }
}

void DynamicHashTable::resize()
{
    int newSize = m_size * EXPANSION;///////
    /////loadFactor
    AVLRankTree<TeamByID> *newArr =  new AVLRankTree<TeamByID> [newSize]();
    for (int i=0; i<m_size; i++)
    {
        if (m_arr[i].m_treeSize != 0)
        {
            TeamByID **array = new TeamByID *[m_arr[i].m_treeSize];
            InorderTransversalIntoArray(m_arr[i].m_root, array, m_arr[i].m_treeSize, 0);
            for (int j = 0; j < m_arr[i].m_treeSize; j++)
            {
                int newIndex = array[j]->m_teamID % newSize;
                //if (newArr[newIndex]. == nullptr)
                //{
                //    newArr[newIndex] = new AVLRankTree<TeamByID>();
                //}
                newArr[newIndex].insertNode(array[j]);
            }
        }
    }
    m_size = newSize;
    delete[] m_arr;
    //TODO delete contents of old array
    m_arr = newArr;
}

