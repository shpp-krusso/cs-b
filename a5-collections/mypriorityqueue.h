#ifndef MYPRIORITYQUEUE_H
#define MYPRIORITYQUEUE_H
#include <vector>
using namespace std;


template<typename T>
class MyPriorityQueue {
public:
    MyPriorityQueue();
    bool empty();
    int size();
    void push(T elem);
    void pop();
    void swap(int pos1, int pos2);
    T top();
private:
    vector<T> vec;
    int countOfElem;                //count of elements in a list
    void elemToRightPosition(int pos);
    void elemToRightPosition();
    int getLessChildPosition(int pos);
};

/*
 * The [0]'th element of the list is neverused, so it contains a trash.
 * In fact thr the top element is element on position [1].
 */
template<typename T>
MyPriorityQueue<T> :: MyPriorityQueue() {
    countOfElem = 0;
    T t;
    vec.push_back(t);
}

/*
 * Return true if queue is empty.
 */
template<typename T>
bool MyPriorityQueue<T> :: empty() {
    return !countOfElem;
}

/*
 * Return a count of elements in the queue. The 0'th position is ignored.
 */
template<typename T>
int MyPriorityQueue<T> :: size() {
    return countOfElem;
}

/*
 * @param pos1  position of the first element.
 * @param pos2  position of the second element.
 * Replays element on position pos1 and element on position pos2
 */
template<typename T>
void MyPriorityQueue<T> :: swap(int pos1, int pos2) {
    T tmp;
    tmp = vec[pos1];
    vec[pos1] = vec[pos2];
    vec[pos2] = tmp;
}

/*
 * Function adds a new element into queue according to it's value.
 */
template<typename T>
void MyPriorityQueue<T> :: push(T i) {
    vec[countOfElem + 1] = i;
    countOfElem++;
    elemToRightPosition(countOfElem);
}

/*
 * @param pos   the number of element
 * Function sets an element that is on current position
 */
template<typename T>
void MyPriorityQueue<T> :: elemToRightPosition(int pos) {
    int parrentPos = countOfElem / 2;
    while (vec[parrentPos] > vec[pos]) {
        swap(parrentPos, pos);
        pos = parrentPos;
        parrentPos = pos / 2;
    }
}

/* Delete the last element in a list*/
template<typename T>
void MyPriorityQueue<T> :: pop() {
    swap(1, countOfElem);
    vec.pop_back();
    countOfElem--;
    elemToRightPosition();
}

/* If an element has more than one child, it return position of the smaller ones. If an element has one  child, it return its position.
 * If an element has no children it return -1*/
template<typename T>
int MyPriorityQueue<T> :: getLessChildPosition(int pos) {
    if (pos * 2 > countOfElem) {
        return -1;
    }
    if (pos * 2 + 1 > countOfElem) {
        return pos * 2;
    }
    if (vec[pos * 2] < vec[pos * 2 + 1])
        return pos * 2;
    return (pos * 2) + 1;
}

/* Move an element on its rigth posion according to its value.*/
template<typename T>
void MyPriorityQueue<T> :: elemToRightPosition() {
    int pos = 1;
    int lessChildPos = getLessChildPosition(pos);
    if (lessChildPos == -1) {
        return;
    }
    while (vec[pos] > vec[lessChildPos]) {
        swap(pos, lessChildPos);
        pos = lessChildPos;
        lessChildPos = getLessChildPosition(pos);
    }
}

/* Return the less value in the queue*/
template<typename T>
T MyPriorityQueue<T> :: top() {
   return vec[1];
}

#endif // MYPRIORITYQUEUE_H

