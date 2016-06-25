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
        Node(T data) {
            this->data = data;
            next = 0;
            prev = 0;
        }

        Node() {
            next = 0;
            prev = 0;
        }

    };

    struct MyIterator {
        MyList :: Node** ptr;
        MyIterator() {
            ptr = 0;
        }

        void operator++() {
            ptr = &(*ptr)->next;
        }

        void operator--() {
            ptr = &(*ptr)->prev;
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
    T front();
    T back();
    void push_back(T new_element);
    void push_front(T new_element);
    void pop_front();
    void pop_back();
    void insert(MyIterator position, T new_element);
    int size();
    bool isEmpty();
    Node** end();
    Node** begin();
private:
    int filled; // Number of filled elements in a list. When a list is empty, it's  value equals 0;
};

template<typename T>
MyList<T> :: MyList() {
    Node* node = new Node();
    filled = 0;
    first = last = node;
}

/* Return the number of filled elements in the list*/
template<typename T>
int MyList<T> :: size() {
    return filled;
}

/* Add a new element into a list as the last element.*/
template<typename T>
void MyList<T> :: push_back(T new_element) {
    Node* node = new Node(new_element);
    if (filled) {
        node->prev = last->prev;
        node->next = last;
        last->prev->next = node;
        last->prev = node;
    } else {
        first = node;
        last->prev = node;
    }
    filled++;
}

/* Add a new element into a list as the first element. */
template<typename T>
void MyList<T> :: push_front(T new_element) {
    Node* node = new Node(new_element);
    if (filled) {
        node->next = first;
        first->prev = node;
        first = node;
    } else {
        first = node;
    }
    filled++;
}

/* Delete the last element of a list. */
template<typename T>
void MyList<T> :: pop_back() {
    if (filled > 1) {
        delete  last->prev;
        Node* tmp = last->prev;
        tmp = tmp->prev;
        tmp->next = last;
        filled--;
    }
    else if (filled == 1) {
        delete last->prev;
        first = last;
        filled--;
    }
}

/* Delete the last element of a list. */
template<typename T>
void MyList<T> :: pop_front() {
    if (filled > 1) {
        first = first->next;
        delete first->prev;
        first->prev = 0;
        filled--;
    }
    else if (first == last) {
        delete first;
        first = last;
    }
}

/* Return true, if a list is empty. */
template<typename T>
bool MyList<T> :: isEmpty() {
    return filled == 0;
}

/* Return a data of a last element in a list */
template<typename T>
T MyList<T> :: back() {
    Node* tmp = last->prev;
    if (tmp)
        return tmp->data;
}

/* Return a data of a first element in a list */
template<typename T>
T MyList<T> :: front() {
    if (filled)
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
void MyList<T> :: insert(MyIterator position, T new_element) {
       Node *node = new Node();
       *(*position.ptr)->prev = node;
       *(*(position-1).ptr)->next = node;
       node->data = new_element;
       node->next = *position;
       node->prev = *(position--);
}

#endif // MYLIST_H
