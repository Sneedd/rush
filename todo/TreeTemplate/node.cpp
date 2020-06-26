

#include "node.h"
#include "treecontainer.h"

//--------------------------------------------------------------------------------
Node::Node()
/**
 * \brief Standartkonstruktor.
 **/
{
    m_data = NULL;
    m_id = -1;
    m_name = "";
    m_parent = NULL;
    m_childs = NULL;
    m_count = 0;
    m_tree = NULL;
}


//--------------------------------------------------------------------------------
Node::Node(Data* data, const int id, const std::string& name)
/**
 * \brief Konstruiert ein neuer Node mit den übergebenen Informationen
 * es werden hier allerdings keine Überprüfungen wegen einzigartigen Ids
 * oder Namen durchgeführt.
 **/
{
    m_data = data;
    m_id = id;
    m_name = name;
    m_parent = NULL;
    m_childs = NULL;
    m_count = 0;
    m_tree = NULL;
}


//--------------------------------------------------------------------------------
Node::~Node()
/**
 * \brief Destruktor.
 **/
{
    if (m_tree->m_freedata) {
        if (m_data != NULL) delete m_data;
    }
    RemoveAll(m_tree->m_freedata);
}


//--------------------------------------------------------------------------------
bool Node::SetId(const int id)
/**
 * \brief Ändert die Id für den Node. Sind die Ids in dem Baum einzigartig
 * und die Id existiert schon, wird false zurückgeliefert und die Id bleibt
 * im alten Zustand.
 * \param id Die neue Id des Knoten.
 **/
{
    if (m_tree->m_uniqueids) {
        if (m_tree->ExistsId(id)) {
            return (false);
        }
    }
    m_id = id;
    return (true);
}


//--------------------------------------------------------------------------------
bool Node::SetName(const std::string& name)
/**
 * \brief Setzt den Namen für den Node. Sind Namen in dem Baum einzigartig
 * und der Name existiert schon, wird false zurückgeliefert und der Name
 * bleibt im alten Zustand.
 * \param name Der neue Name des Knoten.
 **/
{
    if (m_tree->m_uniquenames) {
        if (m_tree->ExistsName(name)) {
            return (false);
        }
    }
    m_name = name;
    return (true);
}



//--------------------------------------------------------------------------------
void Node::SetData(Data* data)
/**
 * \brief Setzt die Daten in dem Knoten neu.
 **/
{
    m_data = data;
}



//--------------------------------------------------------------------------------
bool Node::Add(Data* data, int id, const std::string& name)
/**
 * \brief Fügt einen neuen Kindknoten in diesen Knoten ein. Wird eine
 * Id oder ein Name angegeben und ist einer dieser Werte einzigartig,
 * dann wird überprüft ob dieser Wert existiert. Sollte er existieren
 * wird false zurückgeliefert. Wird einer der default Werte für die id
 * oder den Namen verwendet, werden neue einzigartige Namen oder IDs
 * erzeugt. Ist dieser Baum ein Binärer Baum, kann es nur zwei Knoten
 * geben werden mehr eingefügt wird false zurück geliefert.
 * \param data Die Daten die dieser Knoten enthalten soll.
 * \param id Die Id die der Knoten bekommen soll.
 * \param name Der Name der der Knoten bekommen soll.
 **/
{
    // TODO: inline wenn template
    return (Add(data, name, id));
}


//--------------------------------------------------------------------------------
bool Node::Add(Data* data, const std::string& name, int id)
/**
 * \brief Fügt einen neuen Kindknoten in diesen Knoten ein. Wird eine
 * Id oder ein Name angegeben und ist einer dieser Werte einzigartig,
 * dann wird überprüft ob dieser Wert existiert. Sollte er existieren
 * wird false zurückgeliefert. Wird einer der default Werte für die id
 * oder den Namen verwendet, werden neue einzigartige Namen oder IDs
 * erzeugt. Ist dieser Baum ein Binärer Baum, kann es nur zwei Knoten
 * geben werden mehr eingefügt wird false zurück geliefert.
 * \param data Die Daten die dieser Knoten enthalten soll es können NULL
 * Daten übergeben werden.
 * \param name Der Name der der Knoten bekommen soll.
 * \param id Die Id die der Knoten bekommen soll.
 **/
{
    // Überprüfen ob dieser Baum ein binärer ist
    if (m_tree->m_binarytree && m_count > 2) {
        return (false);
    }

    // Überprüfen ob ein eindeutiger Namen gesucht werden muss
    std::string strg = name;
    if (m_tree->m_uniquenames) {
        if (name.empty()) {
            // TODO: name ist const!!!!!!
            strg = m_tree->CreateUniqueName();
        } else {
            if (m_tree->ExistsName(name)) {
                return (false);
            }
        }
    }

    // Überprüfen ob eine eindeutige Id gesucht werden muss
    if (m_tree->m_uniqueids) {
        if (id == -1) {
            id = m_tree->CreateUniqueId();
        } else {
            if (m_tree->ExistsId(id)) {
                return (false);
            }
        }
    }

    // Das Kindknoten Array erstellen oder erweitern
    if (m_childs == NULL) {
        m_childs = new Node*[1];
    } else {
        Node** temp = m_childs;
        m_childs = new Node*[m_count+1];
        for (int i=0; i<m_count; ++i) m_childs[i] = temp[i];
        delete [] temp;
    }

    // Den neuen Node hinzufügen
    Node* node = new Node(data, id, strg);
    node->m_tree = m_tree;
    node->m_parent = this;
    m_childs[m_count] = node;
    m_count++;
    return (true);
}


//--------------------------------------------------------------------------------
bool Node::AddRange(Data** data, int count)
/**
 * \brief Fügt mehrere Kindknoten diesem Knoten hinzu. Die Funktion verhält
 * sich exakt wie Add()-Methoden. Ausser das das hinzufügen optimiert ist.
 **/
{
    // TODO: inline wenn template
    return (AddRange(data, NULL, NULL, count));
}


//--------------------------------------------------------------------------------
bool Node::AddRange(Data** data, int* id, std::string* name, int count)
/**
 * \brief Fügt mehrere Kindknoten diesem Knoten hinzu. Die Funktion verhält
 * sich exakt wie Add()-Methoden. Ausser das das hinzufügen optimiert ist.
 * Es ist zu beachten, das jedes Array das übergeben wird genau count groß
 * ist. Die Arrays selbst werden nicht gelöscht und müssen von der Aufrufenden
 * Funktion gelöscht werden. Bei den Daten ist allerdings aufzupassen, das
 * man die Daten nicht löscht. Es kann für jedes Element im id Array ein -1
 * für den default Wert verwendet werden oder aber null für das gesamte Array.
 * Bei String Array verhält es sich gleich nur das ein Leerer String angegeben
 * werden muss anstatt eine -1;
 **/
{
    // Überprüfen ob dieser Baum ein binärer ist
    if (m_tree->m_binarytree && count+m_count > 2) {
        return (false);
    }

    // Überprüfen ob ein eindeutiger Namen gesucht werden muss
    if (m_tree->m_uniquenames) {
        // TODO
    }

    // Überprüfen ob eine eindeutige Id gesucht werden muss
    if (m_tree->m_uniqueids) {
        // TODO
    }

    // Kindknoten Array erstellen oder erweitern
    if (m_childs == NULL) {
        m_childs = new Node*[count];
    } else {
        Node** temp = m_childs;
        m_childs = new Node*[m_count+count];
        for (int i=0; i<m_count; ++i) m_childs[i] = temp[i];
        delete [] temp;
    }
    for (int i=0; i<count; ++i) {
        int t_id = -1;
        std::string t_name = "";
        if (id != NULL) t_id = id[i];
        if (name != NULL) t_name = name[i];
        Node* node = new Node(data[i], t_id, t_name);
        m_childs[i+m_count] = node;
        node->m_tree = m_tree;
        node->m_parent = this;
    }
    m_count += count;
    return (true);
}


//--------------------------------------------------------------------------------
void Node::Remove(int index, bool freedata)
{
}


//--------------------------------------------------------------------------------
void Node::RemoveAll(bool freedata)
/**
 * \brief Löscht alle Kindknoten und recursiv die Knoten die unter den Kindknoten
 * liegen.
 **/
{
    m_tree->m_freedata = freedata;
    if (m_childs != NULL) {
        for (int i=0; i<m_count; ++i) {
            if (m_childs[i] != NULL) {
                delete m_childs[i];
            }
        }
        delete [] m_childs;
        m_childs = NULL;
        m_count = 0;
    }
    m_tree->m_freedata = false;
}


//--------------------------------------------------------------------------------
Node* Node::FindFirst(std::string name, bool recursive)
{
}


//--------------------------------------------------------------------------------
Node* Node::FindFirst(int id, bool recursive)
{
}


//--------------------------------------------------------------------------------
Node** Node::Find(std::string name, int& count, bool recursive)
/**
 * \brief Sucht alle Vorkommnisse des angegebenen Namen und liefert
 * ein Array der Nodes zurück.
 * \param name Der Name nach der gesucht werden soll.
 * \param count Die Anzahl der Knoten die zurückgeliefert werden.
 * \param recursive True wenn recursiv gesucht werden soll.
 * \return Liefert ein Array der gefunden Nodes, außerdem gibt count die Anzahl der
 *         im Array befindlichen Nodes zurück. Sollten keine Vorkommnisse gefunden
 *         werden wird NULL zurückgeliefert.
 **/
{
    // Überprüfen ob Namen einzigartig sind und falls ja kann Find First verwendet werden
    if (m_tree->m_uniquenames) {
        Node* found = FindFirst(name, recursive);
        if (found == NULL) {
            count = 0;
            return (NULL);
        } else {
            Node** nodes = new Node*[1];
            nodes[0] = found;
            count = 1;
            return (nodes);
        }
    }

    // Suchen
    // TODO
}


//--------------------------------------------------------------------------------
Node** Node::Find(int id, int& count, bool recursive)
/**
 * \brief Sucht alle Vorkommnisse der angegebenen Id und liefert
 * ein Array der Nodes zurück.
 * \param id Die Id nach der gesucht werden soll.
 * \param count Die Anzahl der Knoten die zurückgeliefert werden.
 * \param recursive True wenn recursiv gesucht werden soll.
 * \return Liefert ein Array der gefunden Nodes, außerdem gibt count die Anzahl der
 *         im Array befindlichen Nodes zurück. Sollten keine Vorkommnisse gefunden
 *         werden wird NULL zurückgeliefert.
 **/
{
    // Überprüfen ob Id einzigartig sind und falls ja kann Find First verwendet werden
    if (m_tree->m_uniqueids) {
        Node* found = FindFirst(id, recursive);
        if (found == NULL) {
            count = 0;
            return (NULL);
        } else {
            Node** nodes = new Node*[1];
            nodes[0] = found;
            count = 1;
            return (nodes);
        }
    }

    // Suchen
    // TODO
}


//--------------------------------------------------------------------------------
int Node::GetLevel()
/**
 * \brief Liefert die Tiefe des Knotens im Baum. Der Wurzelknoten liefert
 * 0 zurück, der Kindknoten des Wurzelknoten 1, ...
 **/
{
    Node* node = this;
    int count = 0;
    while (node != NULL)
    {
        node = node->m_parent;
        count++;
    }
    return (count);
}


//--------------------------------------------------------------------------------
bool Node::IsLeaf()
/**
 * \brief Liefert true wenn dieser Knoten ein Blattknoten ist. Also
 * keine weiteren Kindknoten besitzt.
 **/
{
    return (m_count == 0);
}


//--------------------------------------------------------------------------------
bool Node::IsRoot()
/**
 * \brief Liefert true wenn dieser Knoten der Wurzel Knoten ist.
 **/
{
    return (m_parent == NULL);
}


