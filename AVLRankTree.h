
#ifndef WET_2_AVLRANKTREE_H
#define WET_2_AVLRANKTREE_H

#include "Node.h"
#include <iostream>

template<class T>
class AVLRankTree
{
public:
    Node<T> *m_root;

    int m_treeSize;

    AVLRankTree();

    ~AVLRankTree();

    void destroyTree(Node<T> *root);

    Node<T> *balanceNode(Node<T> *node);

    Node<T> *findNode(T *key); //nullptr if doesnt exist in tree

    int getAddedWins(T *key);

    void removeNode(T *info);

    //void updateBFAndHeight(Node<T> *node);

    void insertNode(T *new_T, int wins = 0, int power = 0);

    Node<T> *RightRightRotation(Node<T> *node);

    Node<T> *RightLeftRotation(Node<T> *node);

    Node<T> *LeftLeftRotation(Node<T> *node);

    Node<T> *LeftRightRotation(Node<T> *node);

    Node<T> *select(Node<T>* node, int index);///////////

    int rank(T* key);

    void addWinsToLessEqual(T* key, int addWins);

    //void debugging_printTree(const std::string &prefix, const Node<T> *node, bool isLeft, std::string &str);

    //void debugging_printTree(const Node<T> *node, std::string &str);

    //std::string debugging_printTree();
};

template<class T>///////////
Node<T> * AVLRankTree<T>::select(Node<T>* node, int index)
{
    if (index<0 || node == nullptr) ///////
    {
        return nullptr;
    }
    if (getSize(node->m_left) == index - 1)
    {
        return node;
    }
    else if (getSize(node->m_left) > index - 1)
    {
        return select(node->m_left, index);
    }
    else
    {
        return select(node->m_right, (index - getSize(node->m_left) - 1));
    }

}

template<class T>
int AVLRankTree<T>::rank(T *key)
{
    int r = 0;
    if(key == nullptr)
    {
        return -1;
    }
    Node<T> *ptr = m_root;
    while (ptr != nullptr)
    {
        if (*(ptr->m_info) == key)
        {
            if(ptr->m_left == nullptr)
            {
                r++;
            }
            else
            {
                r += ptr->m_left->m_size + 1;
            }
            return r;
        } else if (*(ptr->m_info) < key)
        {
            if(ptr->m_left != nullptr)
            {
                r += ptr->m_left->m_size + 1;
            }
            else
            {
                r += 1;
            }
            ptr = ptr->m_right;
        } else
        {
            ptr = ptr->m_left;
        }
    }
    return r;
}

template<class T>
void AVLRankTree<T>::addWinsToLessEqual(T* key, int addWins)
{
    int right_turns = 0;
    Node<T> *ptr = m_root;
    while (ptr != nullptr)
    {
        if (*(ptr->m_info) == key)
        {
            if(right_turns == 0)
            {
                ptr->m_addWins += addWins;
            }
            if(ptr->m_right != nullptr)
            {
                ptr->m_right->m_addWins -= addWins;
            }
        } else if (*(ptr->m_info) < key)
        {
            if(right_turns == 0)
            {
                ptr->m_addWins += addWins;
            }
            ptr = ptr->m_right;
            right_turns++;
        } else
        {
            if(right_turns != 0)
            {
                ptr->m_addWins -= addWins;
            }
            ptr = ptr->m_left;
            right_turns = 0;
        }
    }
}



template<class T>
void updateHeight(Node<T> *node)
{
    node->m_height = 1 + max(getHeight(node->m_left), getHeight(node->m_right));
}

template<class T>
void updateSize(Node<T> *node)
{
    node->m_size = getSize(node->m_left) + getSize(node->m_right) + 1;
}

/*template<class T>
void updateMax(Node<T> *node)
{
    int child_max = max(getMax(node->m_left), getMax(node->m_right));
    node->m_maxRank = max(node->m_maxRank, child_max);
}

template<class T>
void updateMaxRec(Node<T> *node)
{

    Node<T> *temp = node;
    while (temp != nullptr)
    {
        updateMax(temp);
        temp = temp->m_parent;
    }
}*/

template<class T>
Node<T> *AVLRankTree<T>::balanceNode(Node<T> *node)
{
    int heightOfLT;
    int heightOfRT;
    Node<T> *lt, *rt;
    if (node->m_left == nullptr)
    {
        heightOfLT = 0;
    } else
    {
        heightOfLT = node->m_left->m_height + 1;
    }
    if (node->m_right == nullptr)
    {
        heightOfRT = 0;
    } else
    {
        heightOfRT = node->m_right->m_height + 1;
    }
    int bal = heightOfLT - heightOfRT;
    if (bal > -2 && bal < 2)
    {
        return node;
    }
    if (bal == 2)
    {
        lt = node->m_left;
        if (getHeight(lt->m_left) >= getHeight(lt->m_right))
        {
            return AVLRankTree<T>::LeftLeftRotation(node);
        } else
        {
            return AVLRankTree<T>::LeftRightRotation(node);
        }
    } else
    {
        rt = node->m_right;
        if (getHeight(rt->m_right) >= getHeight(rt->m_left))
        {
            return AVLRankTree<T>::RightRightRotation(node);
        } else
        {
            return AVLRankTree<T>::RightLeftRotation(node);
        }
    }
}

template<class T>
static int InorderTransversalIntoArray(Node<T> *root, T *array[], int sizeOfArray, int index)
{
    Node<T> *ptr = root;
    if (ptr == nullptr)
    {
        return index;
    }
    index = InorderTransversalIntoArray(ptr->m_left, array, sizeOfArray, index);
    if (index >= sizeOfArray)
    {
        return index;
    }
    array[index++] = root->m_info;
    return InorderTransversalIntoArray(ptr->m_right, array, sizeOfArray, index);
}

template<class T>
void mergeTwoArraysIntoOne(T *array1[], T *array2[], T *mergedArray[], int sizeof1, int sizeof2)
{
    try
    {
        int i1 = 0, i2 = 0, i3 = 0;
        while (i1 < sizeof1 && i2 < sizeof2)
        {
            if (*array1[i1] < array2[i2])
            {
                T *obj1Copy = new T(array1[i1++]);
                mergedArray[i3++] = obj1Copy;
            } else if(*array2[i2] < array1[i1])
            {
                T *obj2Copy = new T(array2[i2++]);
                mergedArray[i3++] = obj2Copy;
            }
            else
            {
                T* obj3Copy = new T(array1[i1++]);
                i2++;
                mergedArray[i3++] = obj3Copy;
            }
        }
        while (i1 < sizeof1)
        {
            T *objl1Copy = new T(array1[i1++]);
            mergedArray[i3++] = objl1Copy;
        }
        while (i2 < sizeof2)
        {
            T *objl2Copy = new T(array2[i2++]);
            mergedArray[i3++] = objl2Copy;
        }
    }catch (std::bad_alloc& error)
    {
        for(int i = 0; i < sizeof1 + sizeof2; i++)
        {
            delete mergedArray[i];
        }
        throw;
    }
}

template<class T>
Node<T> *AVLRankTree<T>::RightRightRotation(Node<T> *nodeB)
{
    Node<T> *nodeA = nodeB->m_right;

    if (nodeB == m_root)
    {
        m_root = nodeA;
    } else if (nodeB == nodeB->m_parent->m_left)
    {
        nodeB->m_parent->m_left = nodeA;
    } else
    {
        nodeB->m_parent->m_right = nodeA;
    }
    nodeB->m_right = nodeA->m_left;
    if (nodeB->m_right != nullptr)
    {
        nodeB->m_right->m_parent = nodeB;
    }
    int al_old;
    if(nodeA->m_left == nullptr)
    {
        al_old = 0;
    }
    else
    {
        al_old = nodeA->m_left->m_addWins;
    }
    nodeA->m_left = nodeB;
    nodeA->m_parent = nodeB->m_parent;
    nodeB->m_parent = nodeA;
    nodeB->m_height = max(getHeight(nodeB->m_right), getHeight(nodeB->m_left)) + 1;
    nodeA->m_height = max(getHeight(nodeA->m_right), nodeB->m_height) + 1;
    nodeB->m_size = getSize(nodeB->m_left) + getSize(nodeB->m_right) + 1;//////////
    nodeA->m_size = getSize(nodeA->m_left) + getSize(nodeA->m_right) + 1;//////////

    int a_old = nodeA->m_addWins;
    int b_old = nodeB->m_addWins;
    if(nodeB->m_right != nullptr)
    {
        nodeB->m_right->m_addWins = al_old + nodeA->m_addWins;
    }
    nodeA->m_addWins = a_old + b_old;
    nodeB->m_addWins = b_old - nodeA->m_addWins;

    nodeB->m_maxRank = max(getMax(nodeB->m_left), getMax(nodeB->m_right));
    nodeA->m_maxRank = max(getMax(nodeA->m_left), getMax(nodeA->m_right));
    return nodeA;

}

template<class T>
Node<T> *AVLRankTree<T>::LeftLeftRotation(Node<T> *nodeB)
{
    Node<T> *nodeA = nodeB->m_left;

    if (nodeB == m_root)
    {
        m_root = nodeA;
    } else if (nodeB == nodeB->m_parent->m_right)
    {
        nodeB->m_parent->m_right = nodeA;
    } else
    {
        nodeB->m_parent->m_left = nodeA;
    }
    nodeB->m_left = nodeA->m_right;
    if (nodeB->m_left != nullptr)
    {
        nodeB->m_left->m_parent = nodeB;
    }
    int ar_old;
    if(nodeA->m_right == nullptr)
    {
        ar_old = 0;
    }
    else
    {
        ar_old = nodeA->m_right->m_addWins;
    }
    nodeA->m_right = nodeB;
    nodeA->m_parent = nodeB->m_parent;
    nodeB->m_parent = nodeA;

    nodeB->m_height = max(getHeight(nodeB->m_left), getHeight(nodeB->m_right)) + 1;
    nodeA->m_height = max(getHeight(nodeA->m_left), nodeB->m_height) + 1;
    nodeB->m_size = getSize(nodeB->m_left) + getSize(nodeB->m_right) + 1;//////////
    nodeA->m_size = getSize(nodeA->m_left) + getSize(nodeA->m_right) + 1;//////////


    int a_old = nodeA->m_addWins;
    int b_old = nodeB->m_addWins;
    if(nodeB->m_left != nullptr)
    {
        nodeB->m_left->m_addWins = ar_old + nodeA->m_addWins;
    }
    nodeA->m_addWins = a_old + b_old;
    nodeB->m_addWins = b_old - nodeA->m_addWins;

    nodeB->m_maxRank = max(getMax(nodeB->m_left), getMax(nodeB->m_right));
    nodeA->m_maxRank = max(getMax(nodeA->m_left), getMax(nodeA->m_right));
    return nodeA;
}

template<class T>
Node<T> *AVLRankTree<T>::RightLeftRotation(Node<T> *node)
{
    node->m_right = LeftLeftRotation(node->m_right);
    node = RightRightRotation(node);
    return node;
}

template<class T>
Node<T> *AVLRankTree<T>::LeftRightRotation(Node<T> *node)
{
    node->m_left = RightRightRotation(node->m_left);
    node = LeftLeftRotation(node);
    return node;
}

template<class T>
AVLRankTree<T>::AVLRankTree():m_root(nullptr), m_treeSize(0)
{}

template<class T>
AVLRankTree<T>::~AVLRankTree()
{
    destroyTree(m_root);
}

template<class T>
void AVLRankTree<T>::destroyTree(Node<T> *root)
{
    if (root == nullptr)
    {
        return;
    }
    destroyTree(root->m_left);
    destroyTree(root->m_right);
    if (root->m_info != nullptr)
    {
        delete root;
    }
}

template<class T>
Node<T> *minNode(Node<T> *node)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    if (node->m_left == nullptr)
    {
        return node;
    }
    return minNode(node->m_left);
}

template<class T>
Node<T> *maxNode(Node<T> *node)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    if (node->m_right == nullptr)
    {
        return node;
    }
    return maxNode(node->m_right);
}

template<class T>
void AVLRankTree<T>::removeNode(T *info) //based on assumption that such info already exists in tree.
{
    Node<T> *nodeToRemove = findNode(info);
    if(nodeToRemove == nullptr)
    {
        return;
    }

    Node<T> *nodeToRemoveParent = nodeToRemove->m_parent;

    if (nodeToRemove->m_left == nullptr && nodeToRemove->m_right == nullptr) //if leaf
    {
        if (nodeToRemove == m_root)
        {
            m_root = nullptr;
            nodeToRemove->m_parent = nullptr;
            delete nodeToRemove;
            m_treeSize--;
            return;
            //height
        } else if (nodeToRemoveParent->m_right == nodeToRemove)
        {
            nodeToRemoveParent->m_right = nullptr;
            //updateMaxRec(nodeToRemoveParent);
        } else
        {
            nodeToRemoveParent->m_left = nullptr;
            //updateMaxRec(nodeToRemoveParent);
        }
        nodeToRemove->m_parent = nullptr;
        nodeToRemove->m_left = nullptr;
        nodeToRemove->m_right = nullptr;
        delete nodeToRemove;
    } else if (nodeToRemove->m_left != nullptr && nodeToRemove->m_right == nullptr) //if has only left son
    {
        nodeToRemove->m_left->m_addWins += nodeToRemove->m_addWins;
        if (nodeToRemove == m_root)
        {
            m_root = nodeToRemove->m_left;
            m_root->m_parent = nullptr;
            delete nodeToRemove;
            m_treeSize--;
            return;//
        } else if (nodeToRemoveParent->m_left == nodeToRemove)
        {
            nodeToRemove->m_left->m_parent = nodeToRemoveParent;
            nodeToRemoveParent->m_left = nodeToRemove->m_left;
            //updateMaxRec(nodeToRemoveParent);
        } else
        {
            nodeToRemove->m_left->m_parent = nodeToRemoveParent;
            nodeToRemoveParent->m_right = nodeToRemove->m_left;
            //updateMaxRec(nodeToRemoveParent);
        }
        delete nodeToRemove;
    } else if (nodeToRemove->m_right != nullptr && nodeToRemove->m_left == nullptr) //if has only right son
    {
        nodeToRemove->m_right->m_addWins += nodeToRemove->m_addWins;
        if (nodeToRemove == m_root)
        {
            m_root = nodeToRemove->m_right;
            m_root->m_parent = nullptr;
            delete nodeToRemove;
            m_treeSize--;
            return;//
        } else if (nodeToRemoveParent->m_right == nodeToRemove)
        {
            nodeToRemove->m_right->m_parent = nodeToRemoveParent;
            nodeToRemoveParent->m_right = nodeToRemove->m_right;
            //updateMaxRec(nodeToRemoveParent);
        } else
        {
            nodeToRemove->m_right->m_parent = nodeToRemoveParent;
            nodeToRemoveParent->m_left = nodeToRemove->m_right;
            //updateMaxRec(nodeToRemoveParent);
        }
        delete nodeToRemove;
    }
    else
    {
        Node<T> *temp = minNode(nodeToRemove->m_right); //y
        Node<T> *temp1 = nodeToRemove->m_right;
        Node<T> *tempUpdateMax = temp->m_right;
        if(tempUpdateMax == nullptr)
        {
            tempUpdateMax = temp->m_parent;
        }
        int subset_extra = 0;
        while(temp1 != nullptr)
        {
            subset_extra += temp1->m_addWins;
            temp1 = temp1->m_left;
        }
        int e1 = 0;
        int e2 = nodeToRemove->m_addWins;
        int e3 = temp->m_addWins;
        int e4 = 0;
        int e6 = 0;

        if(nodeToRemove->m_left != nullptr)
        {
            e1 = nodeToRemove->m_left->m_addWins;
        }
        if(nodeToRemove->m_right != nullptr)
        {
            e4 = nodeToRemove->m_right->m_addWins;;
        }
        if(temp->m_right != nullptr)
        {
            e6 = temp->m_right->m_addWins;
            temp->m_right->m_addWins += e3;
        }
        temp->m_addWins = e2 + subset_extra;
        if(nodeToRemove->m_left != nullptr)
        {
            nodeToRemove->m_left->m_addWins = e1 - subset_extra;
        }
        if(nodeToRemove->m_right != nullptr)
        {
            nodeToRemove->m_right->m_addWins = e4 - subset_extra;
        }

        Node<T> *tempFather = temp->m_parent;
        temp->m_left = nodeToRemove->m_left;
        temp->m_left->m_parent = temp;
        if (nodeToRemove == m_root)
        {
            m_root = temp;
        } else if (nodeToRemoveParent->m_right == nodeToRemove)
        {
            nodeToRemoveParent->m_right = temp;
        } else
        {
            nodeToRemoveParent->m_left = temp;
        }
        if (temp->m_parent != nodeToRemove)
        {
            if (temp->m_right != nullptr)
            {
                temp->m_right->m_parent = temp->m_parent;
            }
            temp->m_parent->m_left = temp->m_right;
            temp->m_right = nodeToRemove->m_right;
            temp->m_right->m_parent = temp;
        }
        if (temp != nullptr)
        {
            temp->m_parent = nodeToRemoveParent;
        }

        bool flag = false;
        if(tempFather != nodeToRemove)
        {
            flag = true;
        }

        delete nodeToRemove;

        if(flag)
        {
            while (tempFather != nullptr)
            {
                updateHeight(tempFather);
                updateSize(tempFather);
                //updateMax(tempFather);
                balanceNode(tempFather);
                tempFather = tempFather->m_parent;
            }
        }

        if(temp->m_left != nullptr)
        {
            updateHeight(temp->m_left);
            updateSize(temp->m_left);
            //updateMax(temp->m_left);
            balanceNode(temp->m_left);
        }
        if(temp->m_right != nullptr)
        {
            updateHeight(temp->m_right);
            updateSize(temp->m_right);
            //updateMax(temp->m_right);
            balanceNode(temp->m_right);
        }
        while (temp != nullptr)
        {
            updateHeight(temp);
            updateSize(temp);
            //updateMax(temp);
            temp = balanceNode(temp);
            temp = temp->m_parent;
        }
        m_treeSize--;
        //updateMaxRec(tempUpdateMax);
        return;
    }
    while (nodeToRemoveParent != nullptr)
    {
        updateHeight(nodeToRemoveParent);
        updateSize(nodeToRemoveParent);
        //updateMax(nodeToRemoveParent);
        nodeToRemoveParent = balanceNode(nodeToRemoveParent);
        nodeToRemoveParent = nodeToRemoveParent->m_parent;
    }
    m_treeSize--;
}


template<class T>
Node<T> *AVLRankTree<T>::findNode(T *key) //nullptr if doesnt exist in tree
{
    if(key == nullptr)
    {
        return nullptr;
    }
    Node<T> *ptr = m_root;
    while (ptr != nullptr)
    {
        if (*(ptr->m_info) == key)
        {
            return ptr;
        } else if (*(ptr->m_info) < key)
        {
            ptr = ptr->m_right;
        } else
        {
            ptr = ptr->m_left;
        }
    }
    return nullptr;
}

template<class T>
int AVLRankTree<T>::getAddedWins(T *key)
{
    int addedWins = 0;
    Node<T> *ptr = m_root;
    while (ptr != nullptr)
    {
        addedWins += ptr->m_addWins;
        if (*(ptr->m_info) == key)
        {
            return addedWins;
        } else if (*(ptr->m_info) < key)
        {
            ptr = ptr->m_right;
        } else
        {
            ptr = ptr->m_left;
        }
    }
    return addedWins;
}

template<class T>
void AVLRankTree<T>::insertNode(T *new_T, int wins, int power) //inserts new node when guaranteed that node doesnt exist in tree
{
    int temp_extra = 0;
    if (m_root == nullptr)
    {
        Node<T> *newNode = new Node<T>(new_T);
        m_root = newNode;
        m_treeSize++;
        return;
    }
    Node<T> *ptr = m_root;
    while (ptr != nullptr)
    {
        if (*new_T < ptr->m_info)
        {
            if (ptr->m_left == nullptr)
            {
                Node<T> *newNode = new Node<T>(new_T);
                newNode->m_addWins -= temp_extra;
                ptr->m_left = newNode;
                newNode->m_parent = ptr;
                ptr = newNode;
                break;
            }
            temp_extra += ptr->m_addWins;
            ptr = ptr->m_left;
        } else
        {
            if (ptr->m_right == nullptr)
            {
                Node<T> *newNode = new Node<T>(new_T);
                newNode->m_addWins -= temp_extra;
                ptr->m_right = newNode;
                newNode->m_parent = ptr;
                ptr = newNode;
                break;
            }
            temp_extra += ptr->m_addWins;
            ptr = ptr->m_right;
        }
    }
    Node<T>* temp = ptr;
    ptr->m_maxRank = wins + power;
    while (ptr != nullptr)
    {
        ptr->m_height = 1 + max(getHeight(ptr->m_left), getHeight(ptr->m_right));
        updateSize(ptr);
        //updateMax(ptr);
        ptr = balanceNode(ptr);
        ptr = ptr->m_parent;
    }
    m_treeSize++;
}

template<class T>
Node<T> *SupremumOfMin(Node<T> *root, T *min, T *max) //returns nullptr if no key within range
{
    Node<T> *wantedNode = nullptr;
    Node<T> *ptr = root;
    while (ptr != nullptr)
    {
        if (*(ptr->m_info) < min)
        {

            ptr = ptr->m_right;
        } else
        {
            wantedNode = ptr;
            ptr = ptr->m_left;
        }
    }
    if (wantedNode != nullptr && (*(wantedNode->m_info) < max || *(wantedNode->m_info) == max))
    {
        return wantedNode;
    }
    return nullptr;
}

template<class T>
Node<T> *mergedArrayIntoBalTree(T **mergedArray, int startingIndex, int endingIndex)
{
    if (startingIndex > endingIndex)
    {
        return nullptr;
    }

    int middleIndex = (startingIndex + endingIndex) / 2;
    Node<T> *root = new Node<T>(mergedArray[middleIndex]);
    root->m_left = mergedArrayIntoBalTree(mergedArray, startingIndex, middleIndex - 1);
    if(root->m_left != nullptr)
    {
        root->m_left->m_parent = root;
    }
    root->m_right = mergedArrayIntoBalTree(mergedArray, middleIndex + 1, endingIndex);
    if(root->m_right != nullptr)
    {
        root->m_right->m_parent = root;
    }
    updateHeight(root);
    updateSize(root);
    //updateMax(root);
    return root;
}

#endif //WET_2_AVLRANKTREE_H
