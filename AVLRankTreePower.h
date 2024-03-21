//
// Created by Gal Ishai on 3/21/24.
//

#ifndef WET_2_AVLRANKTREEPOWER_H
#define WET_2_AVLRANKTREEPOWER_H


#include "Node.h"
#include "TeamByPower.h"

class AVLRankTreePower
{
public:
    Node<TeamByPower> *m_root;

    int m_treeSize;

    AVLRankTreePower();

    ~AVLRankTreePower();

    void destroyTree(Node<TeamByPower> *root);

    Node<TeamByPower> *balanceNode(Node<TeamByPower> *node);

    Node<TeamByPower> *findNode(TeamByPower *key); //nullptr if doesnt exist in tree

    int getAddedWins(TeamByPower *key);

    void removeNode(TeamByPower *info);

    //void updateBFAndHeight(Node<T> *node);

    void insertNode(TeamByPower *new_T);

    Node<TeamByPower> *RightRightRotation(Node<TeamByPower> *node);

    Node<TeamByPower> *RightLeftRotation(Node<TeamByPower> *node);

    Node<TeamByPower> *LeftLeftRotation(Node<TeamByPower> *node);

    Node<TeamByPower> *LeftRightRotation(Node<TeamByPower> *node);

    Node<TeamByPower> *select(Node<TeamByPower>* node, int index);///////////

    int rank(TeamByPower* key);

    void addWinsToLessEqual(TeamByPower* key, int addWins);
};




#endif //WET_2_AVLRANKTREEPOWER_H
