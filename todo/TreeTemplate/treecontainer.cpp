

#include "treecontainer.h"
#include "node.h"



//--------------------------------------------------------------------------------
TreeContainer::TreeContainer()
{
    m_root = new Node(NULL,0,"root");
    m_root->m_tree = this;
    m_freeid = 1;
    m_uniqueids = false;
    m_uniquenames = false;
    m_binarytree = false;
    m_freedata = true;
}



//--------------------------------------------------------------------------------
TreeContainer::TreeContainer(bool binary, bool uniqueids, bool uniquenames)
/**
 * \brief Setzt ob dieser Baum eindeutige Ids unterstützen soll. Dies ist
 * standartmäßig nicht der Fall. Es sollten überlegungen angestellt werden
 * ob dies überhaupt notwendig ist, da die Überprüfungen ob eine Id
 * existiert relativ aufwenig ist, besonders bei großen Bäumen. Achtung:
 * Wird diese Eigenschaft erst gesetzt
 **/
{
    m_root = new Node(NULL,0,"root");
    m_root->m_tree = this;
    m_freeid = 1;
    m_uniqueids = uniqueids;
    m_uniquenames = uniquenames;
    m_binarytree = binary;
    m_freedata = true;
}


//--------------------------------------------------------------------------------
TreeContainer::TreeContainer(const TreeContainer& tree)
/**
 * \brief Kopiert den übergebenen kompletten Baum in diesen. Allerdings
 * auch nur wenn in der Klasse T ein operator=() implementiert ist.
 **/
{
    // TODO
}



//--------------------------------------------------------------------------------
TreeContainer& TreeContainer::operator=(const TreeContainer& tree)
/**
 * \brief Kopiert den übergebenen kompletten Baum in diesen. Allerdings
 * auch nur wenn in der Klasse T ein operator=() implementiert ist.
 **/
{
}



//--------------------------------------------------------------------------------
TreeContainer::~TreeContainer()
/**
 * \brief Destruktor.
 **/
{
    if (m_root != NULL) {
        m_freedata = true;
        delete m_root;
    }
}

static int count = 0;

void RecCount(Node* node)
{
    if (node == NULL) return;
    count++;
    for (int i=0; i<node->Count(); ++i)
    {
        RecCount(node->GetChild(i));
    }
}


//--------------------------------------------------------------------------------
int TreeContainer::CountNodes()
{
    RecCount(m_root);
    return (count);
}


//--------------------------------------------------------------------------------
std::string TreeContainer::CreateUniqueName()
{
    // TODO
}


//--------------------------------------------------------------------------------
int TreeContainer::CreateUniqueId()
{
    if (ExistsId(m_freeid)) {
        // Neue ID suchen
    } else {
        int id = m_freeid;
        m_freeid++;
        return (id);
    }
}
