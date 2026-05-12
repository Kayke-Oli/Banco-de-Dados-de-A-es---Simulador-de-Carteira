#ifndef MYVEC_H
#define MYVEC_H
#include <string>
#include <cassert>
#include <utility>

class MyVecException
{
private:
    std::string msg;

public:
    MyVecException(const std::string &msg0) : msg(msg0) {}
    const std::string &what() const { return msg; }
};

template <class T>
class MyVec
{
private:
    T *_data;
    int _dataSize;
    int _dataCapacity;

    void create();
    void destroy();
    template <class Comparator>
    void _mergeSortAux(int beg, int end, Comparator cmp, T *aux);
    template <class Comparator>
    void _merge(int beg, int mid, int end, Comparator cmp, T *aux);

public:
    typedef T *iterator;
    iterator begin() { return _data; }
    const iterator begin() const { return _data; }
    iterator end() { return _data + _dataSize; }
    const iterator end() const { return _data + _dataSize; }

    MyVec();
    MyVec(int n, const T &init = T());
    MyVec(const MyVec<T> &outro);

    // --- MOVE SEMANTICS C++11 (O SALVADOR DE MEMÓRIA) ---
    MyVec(MyVec<T> &&outro) noexcept : _data(outro._data), _dataSize(outro._dataSize), _dataCapacity(outro._dataCapacity)
    {
        outro._data = NULL;
        outro._dataSize = 0;
        outro._dataCapacity = 0;
    }
    MyVec<T> &operator=(MyVec<T> &&other) noexcept
    {
        if (this == &other)
            return *this;
        destroy();
        _data = other._data;
        _dataSize = other._dataSize;
        _dataCapacity = other._dataCapacity;
        other._data = NULL;
        other._dataSize = 0;
        other._dataCapacity = 0;
        return *this;
    }

    ~MyVec();
    T &operator[](int pos) { return _data[pos]; }
    const T &operator[](int pos) const { return _data[pos]; }
    MyVec<T> &operator=(const MyVec<T> &outro);

    void push_back(const T &elem);
    void pop_back();
    void resize(int NewSize);
    void insert(int pos, const T &elem);
    void clear();
    bool empty() const;
    int size() const;
    int capacity() const;
    void reserve(int newCapacity);
    template <class Comparator>
    void mergeSort(Comparator cmp);
    void remove(int pos);
};

template <class T>
void MyVec<T>::clear()
{
    destroy();
    create();
}
template <class T>
void MyVec<T>::create()
{
    _data = NULL;
    _dataSize = _dataCapacity = 0;
}
template <class T>
void MyVec<T>::destroy()
{
    delete[] _data;
    _dataSize = _dataCapacity = 0;
}
template <class T>
MyVec<T>::MyVec() { create(); }
template <class T>
MyVec<T>::~MyVec() { destroy(); }
template <class T>
MyVec<T>::MyVec(int n, const T &init)
{
    _dataSize = _dataCapacity = n;
    _data = new T[n];
    for (int i = 0; i < n; i++)
        _data[i] = init;
}
template <class T>
MyVec<T>::MyVec(const MyVec<T> &outro) : _data(new T[outro._dataCapacity]), _dataSize(outro._dataSize), _dataCapacity(outro._dataCapacity)
{
    for (int i = 0; i < _dataSize; ++i)
        _data[i] = outro._data[i];
}

template <class T>
void MyVec<T>::push_back(const T &elem)
{
    if (size() == _dataCapacity)
    {
        if (_dataCapacity == 0)
            reserve(1);
        else
            reserve(_dataCapacity * 2);
    }
    _data[_dataSize] = elem;
    _dataSize++;
}

template <class T>
void MyVec<T>::pop_back()
{
    assert(_dataSize > 0);
    _dataSize--;
}
template <class T>
void MyVec<T>::resize(int newSize)
{
    assert(newSize > 0);
    if (newSize >= _dataCapacity)
        reserve(newSize);
    for (int i = _dataSize; i < newSize; i++)
        _data[i] = T();
    _dataSize = newSize;
}
template <class T>
bool MyVec<T>::empty() const { return _dataSize == 0; }
template <class T>
int MyVec<T>::size() const { return _dataSize; }
template <class T>
int MyVec<T>::capacity() const { return _dataCapacity; }
template <class T>
void MyVec<T>::insert(int pos, const T &elem)
{
    assert(pos >= 0 && pos <= _dataSize);
    if (_dataSize == _dataCapacity)
    {
        if (_dataCapacity == 0)
            reserve(1);
        else
            reserve(_dataCapacity * 2);
    }
    for (int i = _dataSize; i > pos; i--)
        _data[i] = _data[i - 1];
    _data[pos] = elem;
    _dataSize++;
}

template <class T>
void MyVec<T>::reserve(int newCapacity)
{
    if (newCapacity <= _dataCapacity)
        return;
    T *oldData = _data;
    _data = new T[newCapacity];
    for (int i = 0; i < _dataSize; i++)
        _data[i] = std::move(oldData[i]);
    delete[] oldData;
    _dataCapacity = newCapacity;
}

template <class T>
void MyVec<T>::remove(int pos)
{
    assert(pos >= 0 && pos <= _dataSize);
    for (int i = pos; i <= _dataSize - 1; i++)
        _data[i] = _data[i + 1];
    _dataSize--;
}
template <class T>
MyVec<T> &MyVec<T>::operator=(const MyVec<T> &other)
{
    if (this == &other)
        return *this;
    destroy();
    _dataCapacity = other._dataCapacity;
    _dataSize = other._dataSize;
    _data = new T[_dataCapacity];
    for (int i = 0; i < _dataSize; i++)
        _data[i] = other._data[i];
    return *this;
}
template <class T>
template <class Comparator>
void MyVec<T>::mergeSort(Comparator cmp)
{
    if (_dataSize <= 1)
        return;
    T *aux = new T[_dataSize];
    _mergeSortAux(0, _dataSize - 1, cmp, aux);
    delete[] aux;
}
template <class T>
template <class Comparator>
void MyVec<T>::_mergeSortAux(int beg, int end, Comparator cmp, T *aux)
{
    if (beg >= end)
        return;
    int mid = beg + (end - beg) / 2;
    _mergeSortAux(beg, mid, cmp, aux);
    _mergeSortAux(mid + 1, end, cmp, aux);
    _merge(beg, mid, end, cmp, aux);
}
template <class T>
template <class Comparator>
void MyVec<T>::_merge(int beg, int mid, int end, Comparator cmp, T *aux)
{
    int i = beg, j = mid + 1, k = 0;
    while (i <= mid && j <= end)
    {
        if (cmp(_data[j], _data[i]))
            aux[k++] = _data[j++];
        else
            aux[k++] = _data[i++];
    }
    while (i <= mid)
        aux[k++] = _data[i++];
    while (j <= end)
        aux[k++] = _data[j++];
    for (k = 0; k < (end - beg + 1); k++)
        _data[beg + k] = aux[k];
}
#endif