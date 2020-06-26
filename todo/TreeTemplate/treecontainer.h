#ifndef _TREE_CONTAINER_H
#define _TREE_CONTAINER_H


#include <string>
#include "node.h"


/**
 * \brief
 * Überhaupt nicht thread sicher.
 **/
class TreeContainer
{
    private:
        friend class Node;
    public:
        TreeContainer();
        TreeContainer(bool binary, bool uniqueids = false, bool uniquenames = false);
        TreeContainer(const TreeContainer& tree);
        TreeContainer& operator=(const TreeContainer& tree);
        ~TreeContainer();

        // Behaivor Functions
        bool HasUniqueIds();
        bool HasUniqueNames();
        bool IsBinaryTree();

        Node* GetRoot();
        Node** GetLeafs(int& count);
        int CountNodes();

    private:
        // Action Functions
        bool ExistsId(const int id);
        bool ExistsName(const std::string& name);

        std::string CreateUniqueName();
        int CreateUniqueId();



    private:
        bool    m_uniqueids;
        bool    m_uniquenames;
        bool    m_binarytree;   //
        int     m_freeid;       // Eine freie ID Optimierung bei UniqueIds
        bool    m_freedata;

        Node*   m_root;
};



//--------------------------------------------------------------------------------
inline bool TreeContainer::HasUniqueIds()
/**
 * \brief Liefert ob dieser Baum eindeutige Ids besitzt.
 **/
{
    return (m_uniqueids);
}


//--------------------------------------------------------------------------------
inline bool TreeContainer::HasUniqueNames()
/**
 * \brief Liefert ob dieser Baum einduetige Namen besitzt.
 **/
{
    return (m_uniquenames);
}


//--------------------------------------------------------------------------------
inline bool TreeContainer::IsBinaryTree()
/**
 * \brief Liefert ob dieser Baum ein Binärbaum ist.
 **/
{
    return (m_binarytree);
}


//--------------------------------------------------------------------------------
inline Node* TreeContainer::GetRoot()
/**
 * \brief Liefert den Wurzelknoten des Baums.
 **/
{
    return (m_root);
}


//--------------------------------------------------------------------------------
inline bool TreeContainer::ExistsId(const int id)
/**
 * \brief Liefert ob ein Knoten mit der Id existiert.
 **/
{
    return (m_root->FindFirst(id,true) != NULL);
}


//--------------------------------------------------------------------------------
inline bool TreeContainer::ExistsName(const std::string& name)
/**
 * \brief Liefert ob ein Knoten mit dem Namen existiert.
 **/
{
    return (m_root->FindFirst(name,true) != NULL);
}



#endif // _TREE_CONTAINER_H
