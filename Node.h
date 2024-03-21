//
// Created by Gal Ishai on 3/15/24.
//

#ifndef WET_2_NODE_H
#define WET_2_NODE_H

template<class T>
class Node
{
public:
    Node *m_parent;
    Node *m_left;
    Node *m_right;
    T *m_info;
    int m_height;
    int m_size;////////////
    int m_maxRank;
    int m_addWins;

    ~Node()
    {
        delete m_info;
        m_left = nullptr;
        m_right = nullptr;
        m_parent = nullptr;
        m_info = nullptr;
    }

    explicit Node(T *info) : m_parent(nullptr), m_left(nullptr), m_right(nullptr), m_info(info), m_height(0), m_size(1), m_maxRank(0), m_addWins(0)
    {};

};

static int max(int a, int b)
{
    return a >= b ? a : b;
}

template<class T>
int getHeight(Node<T> *node)
{
    if (node == nullptr)
    {
        return -1;
    }
    return node->m_height;
}

template<class T>//////////
int getSize(Node<T> *node)
{
    if (node == nullptr)
    {
        return 0;///////////
    }
    return node->m_size;
}

template<class T>
int getMax(Node<T> *node)
{
    if (node == nullptr)
    {
        return 0;///////////
    }
    return node->m_maxRank;
}

#endif //WET_2_NODE_H
