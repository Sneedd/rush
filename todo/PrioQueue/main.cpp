#include <iostream>
#include <time.h>
#include "list.h"
#include <list>


//using namespace std;

void printlist(List<int>* list)
{
    std::cout << "ptr:   head = " << list->GetHead()
              << " / tail = " << list->GetTail() << std::endl;
    if (list->GetHead() != NULL) {
        if (list->GetHead()->GetValue() != NULL)
            std::cout << "value: head = " << *(list->GetHead()->GetValue());
        else
            std::cout << "value: head = NULL";
        if (list->GetTail()->GetValue() != NULL)
            std::cout << " / tail = " << *(list->GetTail()->GetValue()) << std::endl;
        else
            std::cout << " / tail = NULL" << std::endl;
    }
    std::cout << "list= ";
    for (size_t i=0; i<list->Count(); ++i)
    {
        int* ip = (*list)[i];
        if (ip==NULL) std::cout << " NULL";
        else std::cout << " " << *ip;
    }
    std::cout << std::endl;
    std::cout << "-----------------------------------\n";
}

void speedtest(List<int>* list)
{
    int count = 500000000;
    time_t tt;
    int k = 10;
    int l = 9;
    std::list<int*> stdlist;
    for (size_t i=0; i<list->Count(); ++i)
    {
        int* ip = new int;
        *ip = i;
        stdlist.push_back(ip);
    }
    tt = time(NULL);
    for (int i=0; i<count; ++i)
    {
        for(std::list<int*>::iterator iter = stdlist.begin(); iter != stdlist.end(); iter++)
        {
            if (k == l) break;
        }
    }
    std::cout << "time(std) = " << difftime(time(NULL),tt) << std::endl;
    tt = time(NULL);
    for (int i=0; i<count; ++i)
    {
        for (size_t i=0; i<list->Count(); ++i)
        {
            if (k == l) break;
        }
    }
    std::cout << "time = " << difftime(time(NULL),tt) << std::endl;
}


List<int>* initlist()
{
    List<int>* list = new List<int>(20);
	printlist(list);
    for (size_t i=0; i<list->Count(); ++i)
    {
        int* ip = new int;
        *ip = i;
        (*list)[i] = ip;
    }
    return (list);
}



int main()
{
	List<int>* list = initlist();
	printlist(list);
	//list->RemoveAt(10);
	int* d = new int;
	*d = 333;
	list->Add(d);
	printlist(list);
	list->AddRange(1);
	printlist(list);
	list->Add(d);
	list->Add(d);
	printlist(list);
	list->AddRange(10);
	printlist(list);
	list->RemoveLast(false);
	printlist(list);
	list->Add(d);
	printlist(list);
	list->Remove(false);
	printlist(list);
	for (int i=0; i<30; ++i) list->Remove(false);
	printlist(list);
	list->Remove(false);
	printlist(list);
	list->Remove(false);
	printlist(list);
	list->Remove(false);
	printlist(list);
	int** array = new int*[10];
	for (int i=0; i<10; ++i)
	{
	    array[i] = new int;
	    *(array[i]) = i;
	}
	list->AddRange(array, 10);
	printlist(list);
	list->AddRange(2);
	printlist(list);
	list->AddRange(array, 5);
	printlist(list);
    (*list)[5] = d;
	printlist(list);
	//speedtest(list);
	delete list;
	return 0;
}
