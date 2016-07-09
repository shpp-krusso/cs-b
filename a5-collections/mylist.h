#ifndef MYLIST_H
#define MYLIST_H
#include <iostream>
using namespace std;


template<typename T>
class MyList
{
public:

    /* Data structure, that contain a data, pointer to next elem, and pointer to previous element*/
    struct Node
    {
        T data;
        Node* next;
        Node* prev;
    };

    class MyIterator
    {
    public:
        MyList<T>::Node* ptr;
        MyIterator();
        MyIterator (Node* node);
        MyIterator operator++();
        MyIterator operator--();
        bool operator!=(const MyIterator &iter);
        bool operator==(const MyIterator &iter);
        T &operator*();
    };

    Node* first; // pointer to the first element in a list
    Node* last;  //pointer to the last element in a list
    MyList();
    MyList(const MyList &orig);
    ~MyList();
    T &front();
    T &back();
    void clear();
    void push_back(const T &newElement);
    void push_front(const T &newEelement);
    void pop_front();
    void pop_back();
    void insert(MyIterator position, T newElement);
    int size();
    bool isEmpty();
    void printErrorMessageListIsEmptyAndExitProgram(string nameOfFunc);
    MyIterator end();
    MyIterator begin();
private:
    int countOfElem; // Number of filled elements in a list. When a list is empty, it's  value equals 0;


};

template<typename T>
MyList<T> :: MyList()
{
    countOfElem = 0;
    first = last = NULL;
}

template<typename T>
MyList<T> :: MyList(const MyList<T>& origin)
{
    countOfElem = 0;
    first = last = NULL;
    if (!origin.isEmpty())
    {
        for (Node* node = origin.first; node != NULL; node = node->next)
        {
            push_back(node->data);
        }
    }
}

template<typename T>
MyList<T> :: ~MyList()
{
    clear();
}

/* Clear a list*/
template<typename T>
void MyList<T> :: clear()
{
    while(countOfElem)
    {
        Node* tmp = last;
        if(last->prev != NULL)
        {
            last = tmp->prev;
        }
        if(last->next != NULL)
        {
            last->next = NULL;
        }
        delete tmp;
        countOfElem--;
    }
}


/* Return the number of filled elements in the list*/
template<typename T>
int MyList<T> :: size()
{
    return countOfElem;
}

/* Add a new element into a list as the last element.*/
template<typename T>
void MyList<T> :: push_back(const T &newElem)
{
    Node* node = new Node;
    node->data = newElem;
    if (countOfElem)
    {
        node->prev = last;
        last->next = node;
        last = node;
    }
    else
    {
        first = last = node;
    }
    countOfElem++;
}

/* Add a new element into a list as the first element. */
template<typename T>
void MyList<T> :: push_front(const T &newElement)
{
    Node* node = new Node;
    node->data = newElement;
    if (countOfElem)
    {
        node->next = first;
        first->prev = node;
        first = node;
    }
    else
    {
        first = last = node;
    }
    countOfElem++;
}

/* Delete the last element of a list. */
template<typename T>
void MyList<T> :: pop_back()
{
    if (countOfElem)
    {
        last = last->prev;
        (last == NULL) ? first = NULL : last->next = NULL;
        countOfElem--;
    }
    else
    {
        printErrorMessageListIsEmptyAndExitProgram("pop_back()");
    }
}

/* Delete the last element of a list. */
template<typename T>
void MyList<T>::pop_front()
{
    if (countOfElem)
    {
        first = first->next;
        first->prev = NULL;
        countOfElem--;
    }
    else
    {
        printErrorMessageListIsEmptyAndExitProgram("pop_front()");
    }
}


template<typename T>
bool MyList<T>::MyIterator::operator==(const MyIterator &iter)
{
    return ptr == iter.ptr;
}

template<typename T>
bool MyList<T>::MyIterator::operator!=(const MyIterator &iter)
{
    return ptr != iter.ptr;
}

/* Return true, if a list is empty. */
template<typename T>
bool MyList<T>::isEmpty()
{
    return !countOfElem;
}

/* Return a data of a last element in a list */
template<typename T>
T &MyList<T>::back()
{
    if (!countOfElem)
    {
        printErrorMessageListIsEmptyAndExitProgram("back()");
    }
    else
    {
        return last->data;
    }
}

/* Return a data of a first element in a list */
template<typename T>
T &MyList<T>::front()
{
    if (!countOfElem)
    {
        printErrorMessageListIsEmptyAndExitProgram("front()");
    }
    else
    {
        return first->data;
    }
}

template<typename T>
void MyList<T>::printErrorMessageListIsEmptyAndExitProgram(string nameOfFunc)
{
    cerr << "Error! The list is empty! [" << nameOfFunc << "]" << endl;
    exit(1);
}

/* Return an adress of a memory section, that is the next after the last element in a list.
 * In other words, it returns an adress of an end of a list*/
template<typename T>
typename MyList<T>::MyIterator MyList<T>::end()
{
    return MyIterator(last->next);
}

/* Return an adress of a first element in a list */
template<typename T>
typename MyList<T>::MyIterator MyList<T>::begin()
{
    return MyIterator(first);
}


template<typename T>
MyList<T>::MyIterator::MyIterator()
{
    ptr = NULL;
}

template<typename T>
MyList<T>::MyIterator::MyIterator(Node* node)
{
    ptr = node;
}

template<typename T>
T &MyList<T>::MyIterator::operator*()
{
    return ptr->data;
}

template<typename T>
typename MyList<T>::MyIterator MyList<T>::MyIterator::operator++()
{
    return ptr = ptr->next;
    return *this;
}

template<typename T>
typename MyList<T>::MyIterator MyList<T>::MyIterator::operator--()
{
    return ptr = ptr->prev;
    return *this;
}


#endif // MYLIST_H
