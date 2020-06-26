

#include <iostream>
#include <time.h>
#include "treecontainer.h"


void CreateBigTree()
{
    std::cout << "Begin create big tree ..." << std::endl;
    time_t tp = time(NULL);
    TreeContainer* tree = new TreeContainer();
    int maxsize = 200;
    Data** data = new Data*[maxsize];
    for (int i=0; i<maxsize; ++i) data[i] = NULL;
    int stop = 0;
    Node* node = tree->GetRoot();
    while (stop < 2000)
    {
        if (stop%1000 == 0)
            std::cout << stop << std::endl;
        node->AddRange(data,maxsize);
        node->GetChild(stop%200)->AddRange(data,maxsize);
        stop++;
    }
    double db = difftime(time(NULL),tp);
    std::cout << "Time taken: " << db << std::endl;
    std::cout << "End of create big tree ..." << std::endl;
    std::cout << "Begin to count ..." << std::endl;
    tp = time(NULL);
    std::cout << tree->CountNodes() << std::endl;
    db = difftime(time(NULL),tp);
    std::cout << "Time taken: " << db << std::endl;
    std::cout << "End to count ..." << std::endl;
}


int main()
{
	std::cout << "---------------------" << std::endl;
	CreateBigTree();
	return 0;
}
