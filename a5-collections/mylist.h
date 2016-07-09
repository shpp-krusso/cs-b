#ifndef MYLIST_H
#define MYLIST_H
#include <iostream>
using namespace std;


template<typename T>
class MyList {
public:

    /* Data structure, that contain a data, pointer to next elem, and pointer to previous element*/
    struct Node {
        T data;
        Node* next;
        Node* prev;
    };

    struct MyIterator {
        MyList :: Node** ptr;
        MyIterator() {
            ptr = 0;
        }

        void operator++() {
            ptr = (*ptr)->next;
        }

        void operator--() {
            ptr = (*ptr)->prev;
        }

        Node** operator=(Node** elem) {
            return  ptr = elem;
        }

        bool operator!=(Node** elem) {
            return *ptr != *elem;
        }
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
    Node** end();
    Node** begin();
private:
    int countOfElem; // Number of filled elements in a list. When a list is empty, it's  value equals 0;
};

template<typename T>
MyList<T> :: MyList() {
    countOfElem = 0;
    first = last = NULL;
}

template<typename T>
MyList<T> :: MyList(const MyList<T>& origin) {
    countOfElem = 0;
    first = last = NULL;
    if (!origin.isEmpty()) {
        for (Node* node = origin.first; node != NULL; node = node->next) {
            push_back(node->data);
        }
    }
}

template<typename T>
MyList<T> :: ~MyList() {
    clear();
}

template<typename T>
void MyList<T> :: clear() {
    while(countOfElem) {
        Node* tmp = last;
        if(last->prev != NULL) {
            last = tmp->prev;
        }
        if(last->next != NULL) {
            last->next = NULL;
        }
        delete tmp;
        countOfElem--;
    }
}


/* Return the number of filled elements in the list*/
template<typename T>
int MyList<T> :: size() {
    return countOfElem;
}

/* Add a new element into a list as the last element.*/
template<typename T>
void MyList<T> :: push_back(const T &newElem) {
    Node* node = new Node;
    node->data = newElem;
    if (countOfElem) {
        node->prev = last;
        last->next = node;
        last = node;
    } else {
        first = last = node;
    }
    countOfElem++;
}

/* Add a new element into a list as the first element. */
template<typename T>
void MyList<T> :: push_front(const T &newElement) {
    Node* node = new Node;
    node->data = newElement;
    if (countOfElem) {
        node->next = first;
        first->prev = node;
        first = node;
    } else {
        first = last = node;
    }
    countOfElem++;
}

/* Delete the last element of a list. */
template<typename T>
void MyList<T> :: pop_back() {
    if (countOfElem > 1) {
        Node* tmp = last->prev->prev;
        last->prev = tmp;
        tmp->next = last;
        countOfElem--;
    } else if (countOfElem == 1) {
        last->prev = 0;
        first = last;
        countOfElem--;
    }
}

/* Delete the last element of a list. */
template<typename T>
void MyList<T> :: pop_front() {
    if (countOfElem > 1) {
        first = first->next;
        first->prev = 0;
        countOfElem--;
    } else if (first != last) {
        last->prev = 0;
        first = last;
    }
}

/* Return true, if a list is empty. */
template<typename T>
bool MyList<T> :: isEmpty() {
    return !countOfElem;
}

/* Return a data of a last element in a list */
template<typename T>
T &MyList<T> :: back() {
    Node* tmp = last->prev;
    if (tmp)
        return tmp->data;
}

/* Return a data of a first element in a list */
template<typename T>
T &MyList<T> :: front() {
    if (countOfElem)
        return first->data;
}

/* Return an adress of a memory section, that is the next after the last element in a list.
 * In other words, it returns an adress of an end of a list*/
template<typename T>
typename MyList<T> :: Node** MyList<T> :: end() {
    return &last;
}

/* Return an adress of a first element in a list */
template<typename T>
typename MyList<T> :: Node** MyList<T> :: begin() {
    return &first;
}

/* Add a new element into a list on the current postion. The element, that had already been on this position now is putting on next position and so on.*/
template<typename T>
void MyList<T> :: insert(MyIterator position, T newElement) {
    Node *node = new Node();
    *(*position.ptr)->prev = node;
    *(*(position-1).ptr)->next = node;
    node->data = newElement;
    node->next = *position;
    node->prev = *(position--);
}

#endif // MYLIST_H
