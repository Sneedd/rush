/*
 * testlist.cpp - Implementation of UnitTest::TestList method
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */




#include "unittest.h"
#include <list>


//-----------------------------------------------------------------------------
class TestObject
{
    public:
        TestObject(int value) : Value(value) {}
        int Value;
};



//-----------------------------------------------------------------------------
void TestListSpeed()
{
    int maxLoops = 5000;
    int maxElements = 4*1024;
    size_t stdTime = 0;
    size_t rushTime = 0;

    // Speed test std list ---------------------------------
    stdTime = rush::System::GetTicks();
    std::list<int*> stdlist;
    for (int j=0; j<maxElements; ++j)
    {
        int* ip = new int;
        *ip = j;
        stdlist.push_back(ip);
    }

    for (int i=0; i<maxLoops; ++i)
    {
        for(std::list<int*>::iterator iter = stdlist.begin(); iter != stdlist.end(); iter++)
        {
            int value = **iter;
            value += 1;
        }
    }
    stdTime = rush::System::GetTicks() - stdTime;


    // Speed test rush list ----------------------------------
    rushTime = rush::System::GetTicks();
    rush::List<TestObject> rushList;
    for (int j=0; j<maxElements; ++j)
    {
        rushList.Add(new TestObject(j));
    }
    for (int i=0; i<maxLoops; ++i)
    {
        for (size_t j=0; j<rushList.Count(); ++j)
        {
            int value = rushList[j]->Value;
            value += 1;
        }
    }
    rushTime = rush::System::GetTicks() - rushTime;

    // Print result
    rush::Console::WriteLine(_T("std::list<int*> = %ims  rush::List<int> = %ims"), stdTime, rushTime);
}


//-----------------------------------------------------------------------------
void PrintListInt(rush::List<TestObject>* list, bool pointer = false)
{
    rush::String info = rush::String::Format(_T("List<int> (Count = %i) = {"), list->Count());
    if (pointer)
    {
        for (size_t i=0; i<list->Count(); ++i)
        {
            info.AppendFormat(_T("%i"), (*list)[i]->Value);
            if (i != list->Count()-1) info.Append(_T(", "));
        }
    }
    else
    {
//        std::cout << "ptr:   head = " << list->GetHead()
//                  << " / tail = " << list->GetTail() << std::endl;
//        if (list->GetHead() != NULL) {
//            if (list->GetHead()->GetValue() != NULL)
//                std::cout << "value: head = " << *(list->GetHead()->GetValue());
//            else
//                std::cout << "value: head = NULL";
//            if (list->GetTail()->GetValue() != NULL)
//                std::cout << " / tail = " << *(list->GetTail()->GetValue()) << std::endl;
//            else
//                std::cout << " / tail = NULL" << std::endl;
//        }
//        std::cout << "list= ";
//        for (size_t i=0; i<list->Count(); ++i)
//        {
//            int* ip = (*list)[i];
//            if (ip==NULL) std::cout << " NULL";
//            else std::cout << " " << *ip;
//        }
//        std::cout << std::endl;
//        std::cout << "-----------------------------------\n";
    }
    info.Append(_T(" } \n"));
    rush::Console::WriteLine(_T("%s"), info.c_str());
}


//-----------------------------------------------------------------------------
void UnitTest::TestList()
{
    this->BeginTest(_T("List"));
    //TestListSpeed();

    rush::List<TestObject> list;
    for (int i=0; i<20; ++i) list.Add(new TestObject(i));

    this->Assert(_T("Add1"), list.Count() != 20);
    this->Assert(_T("Add2"), list[19]->Value != 19);
    this->Assert(_T("Add3"), list[0]->Value != 0);

    list.AddLast(new TestObject(333));
    this->Assert(_T("AddLast1"), list.Count() != 21);
    this->Assert(_T("AddLast2"), list[list.Count()-1]->Value != 333);

    list.AddFirst(new TestObject(777));
    this->Assert(_T("AddFirst1"), list.Count() != 22);
    this->Assert(_T("AddFirst2"), list[0]->Value != 777);

    // TODO

//	list->RemoveLast(false);
//	printlist(list);
//	list->Add(d);
//	printlist(list);
//	list->Remove(false);
//	printlist(list);
//	for (int i=0; i<30; ++i) list->Remove(false);
//	printlist(list);
//	list->Remove(false);
//	printlist(list);
//	list->Remove(false);
//	printlist(list);
//	list->Remove(false);
//	printlist(list);
//	int** array = new int*[10];
//	for (int i=0; i<10; ++i)
//	{
//	    array[i] = new int;
//	    *(array[i]) = i;
//	}
//	list->AddRange(array, 10);
//	printlist(list);
//	list->AddRange(2);
//	printlist(list);
//	list->AddRange(array, 5);
//	printlist(list);
//    (*list)[5] = d;
//	printlist(list);
//	//speedtest(list);
//	delete list;
//	return 0;





    this->EndTest();
}


