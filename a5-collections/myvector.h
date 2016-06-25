#ifndef MY_VECTOR_H
#define MY_VECTOR_H
#include <iostream>
#include <string>

using namespace std;
template<typename T>
class MyVector {
private:
    T* array;
    void allocNewMemory();
public:
    void pop_back();
    int capacity, filled;
    MyVector();
    MyVector(int capacity);
    MyVector(const MyVector&);
    ~MyVector();
    void push_back(T new_element);
    int size();
    T operator[](int position);
    MyVector& operator = (const MyVector&);
    T at(int position);
};

/* The method reserves a free space to make sure the vector will have never overflowed. */
template<typename T>
void MyVector<T> :: allocNewMemory() {
    capacity *= 2;
    T* newArray = new  T[capacity];
    for (int i = 0; i < filled; i++) {
        newArray[i] = array[i];
    }
    delete[] array;
    array = newArray;
}

/* Returns the number of elements in the vector*/
template<typename T>
int MyVector<T> :: size() {
    return filled;
}

/* Delete the last filled element in the vector*/
template<typename T>
void MyVector<T> :: pop_back() {
    if (filled != 0)
        filled--;
}

/* Constructor creates a new vector.*/
template<typename T>
MyVector<T> :: MyVector() {
    array = 0;
    capacity  = filled = 0;

}

/* Constructor creates a new vector with desired capacity.
 * @param  int _capasity - the capscity of the vector */
template<typename T>
MyVector<T> :: MyVector(int _capacity) {
    array = new T[_capacity];
    capacity = _capacity;
    filled = _capacity*2;
}

template<typename T>
T MyVector<T> :: operator[](int position) {
    if (position >= 0 && position <= filled) {
        return array[position];
    }
}


template<typename T>
MyVector<T> :: MyVector(const MyVector &_vector) {
    capacity = _vector.capacity;
    array = new T[capacity];
    filled = 0;
            for (int i = 0; i < capacity; i++) {
        array[i] = _vector.array[i];
        filled++;
    }
}

//destructor
template<typename T>
MyVector<T> :: ~MyVector() {
    delete[] array;
}

/* Adds a new element on the position after the last filled element.*/
template<typename T>
void MyVector<T> :: push_back(T new_element) {
    if (array == 0) {
        array = new T[2];
        capacity = 2;
    }
    else if (filled == capacity) {
        allocNewMemory();
    }
    array[filled] = new_element;
    filled++;
}

template<typename T>
MyVector<T>& MyVector<T> :: operator = (const MyVector<T> &source) {
    if (this != &source) {
        delete[] array;
        filled = 0;
        this->capacity = source.capacity;
        array = new T[capacity];
        for (int i = 0; i < source.filled; i++) {
            array[i] = source.array[i];
            filled++;
        }
    }
    return *this;
}

/* Retutn an element on the current position
 * @param - the current position*/
template<typename T>
T MyVector<T> :: at(int position) {
    if (position >= 0 && position <= this->filled)
        return array[position];
}


#endif // MY_VECTOR_H
