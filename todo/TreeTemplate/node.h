#ifndef _TREE_CONTAINER_NODE_H_
#define _TREE_CONTAINER_NODE_H_

#include <string>
#include "data.h"

// Forward Definition
class TreeContainer;



/**
 * \brief The Node class is a node in a treecontainer class and
 * cannot be initalized by the user only by the treecontainer
 **/
class Node
{
    private:
        friend class TreeContainer;
        Node();
        Node(Data* data, const int id, const std::string& name);
        ~Node();

    public:
        // Getter Functions
        int         Count();
        Node*       GetChild(int index);
        Node*       operator[](int index);
        Node*       GetFirst();
        Node*       GetLast();
        Node*       GetParent();
        Data*       GetData();
        int         GetId();
        std::string& GetName();

        // Setter Functions
        bool        SetId(const int id);
        bool        SetName(const std::string& name);
        void        SetData(Data* data);

        // Container Functions
        bool        Add(Data* data, int id, const std::string& name = "");
        bool        Add(Data* data, const std::string& name = "", int id = -1);
        bool        AddRange(Data** data, int count);
        bool        AddRange(Data** data, int* id, std::string* name, int count);
        void        Remove(int index, bool freedata = true);
        void        RemoveAll(bool freedata = true);

        // Active Functions
        Node*       FindFirst(std::string name, bool recursive = true);
        Node*       FindFirst(int id, bool recursive = true);
        Node**      Find(std::string name, int& count, bool recursive = true);
        Node**      Find(int id, int& count, bool recursive = true);
        int         GetLevel();
        bool        IsLeaf();
        bool        IsRoot();

    private:
        int             m_id;       // Id
        Data*           m_data;     // Data In Node
        std::string     m_name;     // Node Name
        TreeContainer*  m_tree;     // Tree

        Node*           m_parent;   // Previous Node
        Node**          m_childs;   // Next Nodes
        int             m_count;    // Next Nodes Count


};


//--------------------------------------------------------------------------------
inline int Node::Count()
/**
 * \brief Liefert die Anzahl der Kindknoten zurück.
 **/
{
    return (m_count);
}


//--------------------------------------------------------------------------------
inline Node* Node::GetChild(int index)
/**
 * \brief Liefert ein Kindkonten oder NULL wenn an der Position
 * keines existiert.
 **/
{
    if (index >= 0 && index < m_count) {
        return (m_childs[index]);
    }
    return (NULL);
}


//--------------------------------------------------------------------------------
inline Node* Node::operator[](int index)
/**
 * \brief Liefert ein Kindknoten oder NULL wenn an der Position
 * keines existiert.
 **/
{
    if (index >= 0 && index < m_count) {
        return (m_childs[index]);
    }
    return (NULL);
}



//--------------------------------------------------------------------------------
inline Node* Node::GetFirst()
/**
 * \brief Liefert den ersten Kindknoten. Falls es keinen Kindknoten gibt
 * wird NULL zurück geliefert. Diese Function ist ein wenig verständlicher
 * wenn der Baum ein binärer ist.
 **/
{
    if (m_count > 0) {
        return (m_childs[0]);
    }
    return (NULL);
}



//--------------------------------------------------------------------------------
inline Node* Node::GetLast()
/**
 * \brief Liefert den letzten Kindknoten. Falls es keinen Kindknoten gibt
 * oder nur ein Knoten existiert, dann wird NULL zurückgeliefert. Diese
 * Funktion ist ein wenig verständlicher wenn der Baum ein binärer ist.
 **/
{
    if (m_count > 1) {
        return (m_childs[m_count-1]);
    }
    return (NULL);
}



//--------------------------------------------------------------------------------
inline Node* Node::GetParent()
/**
 * \brief Liefert den Elternknoten.
 **/
{
    return (m_parent);
}



//--------------------------------------------------------------------------------
inline Data* Node::GetData()
/**
 * \brief Liefert die Daten in dem Knoten.
 **/
{
    return (m_data);
}



//--------------------------------------------------------------------------------
inline int Node::GetId()
/**
 * \brief Liefert die Id des Knoten.
 **/
{
    return (m_id);
}



//--------------------------------------------------------------------------------
inline std::string& Node::GetName()
/**
 * \brief Liefert den Namen des Knoten.
 **/
{
    return (m_name);
}



#endif // _TREE_CONTAINER_NODE_H_
