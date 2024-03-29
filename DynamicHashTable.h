
#ifndef WET_2_DYNAMICHASHTABLE_H
#define WET_2_DYNAMICHASHTABLE_H

#define EXPANSION 2
#define INITIAL_SIZE 10
#define LOAD_FACTOR 0.5

#include <memory>
//#include "AVLRankTree.h"
#include "TeamByID.h"

using namespace std;

class DynamicHashTable {
public:

    AVLRankTree<TeamByID> **m_arr;
    int m_size;
    int m_occupancy;
    //double loadFactor;

    DynamicHashTable()
    {
        m_arr = new AVLRankTree<TeamByID>*[INITIAL_SIZE]();//////
        m_size = INITIAL_SIZE;
        m_occupancy = 0;
    }

    ~DynamicHashTable()
    {
        for(int i = 0; i < m_size; i++)
        {
            delete m_arr[i];
        }
        delete[] m_arr;
    }

    /*DynamicHashTable(const DynamicHashTable &other)
    {
        m_arr = new shared_ptr<HashNode>[other.m_size]();
        m_size = other.m_size;
        m_occupancy = other.m_occupancy;
        for (int i=0; i<other.m_occupancy; i++)
        {
            m_arr[i] = other.m_arr[i];
        }
    }*/

    //DynamicHashTable& operator= (const DynamicHashTable &other);

    TeamByID* find(int key);

    void insert(int key, TeamByID* info);

    void remove(int key);

    void resize();

    void desize();

    //double loadFactor()//////////////////////////
    int hashFunction (int key);
};

#endif //WET_2_DYNAMICHASHTABLE_H
