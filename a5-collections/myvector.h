#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <iostream>
using namespace std;

template <class T>
class MyVector {
private:
    T* array;
    const double defaultCoefMemoryResize  = 2;
    static const int defaultStartVectorSize = 2;
    const double fillLimitCoef = 0.75;
    const double unfillLimitCoef = 1 - fillLimitCoef;
    int maxSize, filled;
    void resize(double resizeCoef);

public:
    MyVector(int s = defaultStartVectorSize);
    MyVector(const MyVector<T> &vec);
    ~MyVector();
    void push_back(const T &newElem);
    T &back();
    T &front();
    int size();
    int capacity();
    void pop_back();
    bool empty();
    void shrink_to_fit();
    MyVector<T>& operator=(const MyVector<T> &vec);
    T& operator[](const int index);
};


template <typename T>
MyVector<T>::MyVector(int s) {
    maxSize = (s > 1) ? s : defaultStartVectorSize;
    filled = 0;
    array = new T[maxSize];
}

template <typename T>
MyVector<T>::MyVector(const MyVector<T> &vec) {
    filled = vec.filled;
    maxSize = vec.maxSize;
    array = new T[maxSize];
    for (int i = 0; i < filled; i++) {
        array[i] = vec.array[i];
    }
}

template <typename T>
MyVector<T>::~MyVector() {
    delete[] array;
    filled = maxSize = 0;
}

template <typename T>
void MyVector<T>::resize(double resizeCoef) {
    maxSize = (int) maxSize * resizeCoef;
    T* tmp = new T[maxSize];
    for (int i = 0; i < filled; i++) {
        tmp[i] = array[i];
    }
    delete[] array;
    array = tmp;
}

template <typename T>
void MyVector<T>::push_back(const T &newElem) {
    if (filled >= (int)(maxSize * fillLimitCoef)) {
        resize(defaultCoefMemoryResize);
    }
    array[filled] = newElem;
    filled++;
}

template <typename T>
T& MyVector<T>::back() {
    if (filled) {
        return array[filled -1];
    } else {
        return *array;
    }
}

template <typename T>
T& MyVector<T>::front() {
    return *array;
}

template <typename T>
int MyVector<T>::size() {
    return filled;
}

template <typename T>
int MyVector<T>::capacity() {
    return maxSize;
}

template <typename T>
void MyVector<T>::pop_back() {
    if (!empty()) {
        filled--;
    }
    if (filled < (int)(maxSize * unfillLimitCoef)) {
        resize(1 / defaultCoefMemoryResize);
    }
}

template <typename T>
bool MyVector<T>::empty() {
    return !filled;
}

template <typename T>
void MyVector<T>::shrink_to_fit() {
    T* tmp = new T[filled];
    for (int i = 0; i < filled; i++) {
        tmp[i] = array[i];
    }
    delete[] array;
    array = tmp;
    maxSize = filled;
}

template <typename T>
MyVector<T> &MyVector<T>::operator=(const MyVector<T> &vec) {
    if (array != vec.array) {
        delete[] array;
        maxSize = vec.maxSize;
        array = new T[maxSize];
        filled = vec.filled;
        for (int i = 0; i < filled; i++) {
            array[i] = vec.array[i];
        }
    }
    return *this;
}

template <typename T>
T &MyVector<T>::operator[](const int index) {
    if (index >= 0 && index < filled) {
        return array[index];
    } else {
        return *array;
    }
}





#endif // MYVECTOR_H

