#ifndef MYVEC_H
#define MYVEC_H
#include <string>
#include <cassert>


//Excessao usada pela classe MyVec
class MyVecException {
private:
	std::string msg;
public:
	MyVecException (const std::string &msg0): msg(msg0) { }
	const std::string & what() const { return msg; }
};


template <class T>
class MyVec{
private:
    T* _data;
    int _dataSize;
    int _dataCapacity;

    void create();
    void destroy();
     // Auxiliar recursivo do merge sort
    template <class Comparator>
    void _mergeSortAux(int beg, int end, Comparator cmp);
 
    // Merge de dois subvetores ordenados
    template <class Comparator>
    void _merge(int beg, int mid, int end, Comparator cmp);
public:
    typedef T* iterator;//define iterador

    iterator begin() {return _data;}
    const iterator begin() const {return _data;}

    iterator end() {return _data+_dataSize;}
    const iterator end() const {return _data+_dataSize;}

    //Construtores
    MyVec();
    MyVec(int n, const T&init=T());
    // Construtor de cópia
    MyVec(const MyVec<T>& outro);
    MyVec &operator=(const MyVec<T>& );
    //Destrutor
    ~MyVec();
    //funcoes de acesso
	T &operator[](int pos) {return _data[pos];}
	const T &operator[](int pos) const {return _data[pos];}
    // Operador de atribuição
    MyVec<T>& operator=(const MyVec<T>& outro);
    //Funções essenciais
    void push_back(const T&elem);
    void pop_back();
    void resize(int NewSize);
    void insert(int pos, const T&elem);
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
void MyVec<T>::clear(){
    destroy();
    create();
}

template <class T>
void MyVec<T>::create(){
    _data = NULL;
    _dataSize = _dataCapacity = 0;
}

template <class T>
void MyVec<T>::destroy(){
    delete[] _data;
    _dataSize = _dataCapacity = 0;
}

template <class T>
MyVec<T>::MyVec(){
    create();
}

template <class T>
MyVec<T>::MyVec(int n, const T&init){
    _dataSize = _dataCapacity = n;
    _data = new T[n];
    for(int i=0;i<n;i++) _data[i] = init;
}

template <class T>
MyVec<T>::MyVec(const MyVec<T>&outro) : _data(new T[outro._dataSize]), _dataSize(outro._dataSize), _dataCapacity(outro._dataCapacity){
    for (int i = 0; i < _dataSize; ++i)
        _data[i] = outro._data[i];}

template <class T>
void MyVec<T>::push_back(const T&elem){
    if(size() == _dataCapacity){
        if(_dataCapacity == 0)
            reserve(1);
        else
            reserve(_dataCapacity*2);}
    _data[_dataSize] = elem;
    _dataSize++;
}

template <class T>
void MyVec<T>::pop_back(){
    assert(_dataSize > 0);
    _dataSize--;
}

template <class T>
void MyVec<T>::resize(int newSize){
    assert(newSize > 0);
    if(newSize >= _dataCapacity)
        reserve(newSize);
    for(int i=_dataSize;i<newSize;i++){
        _data[i] = T();
    }
    _dataSize = newSize;
}

template <class T>
bool MyVec<T>::empty() const{
    return _dataSize==0;
}

template <class T>
int MyVec<T>::size() const{
    return _dataSize;
}

template <class T>
int MyVec<T>::capacity() const{
    return _dataCapacity;
}

template <class T>
void MyVec<T>::insert(int pos, const T&elem){
    assert(pos>=0 && pos<=_dataSize);
    if(_dataSize == _dataCapacity){
        if(_dataCapacity == 0)
            reserve(1);
        else
            reserve(_dataCapacity*2);}
    for(int i=_dataSize;i>pos;i--)
        _data[i] = _data[i-1];
    _data[pos] = elem;
    _dataSize++;
}

template<class T>
void MyVec<T>::reserve(int newCapacity) {
	if(newCapacity<=_dataCapacity)
		return; 
	T* oldData = _data;
	_data = new T[newCapacity];
	for(int i=0;i<_dataSize;i++)
		_data[i] = oldData[i];
	delete []oldData;
	_dataCapacity = newCapacity;
}

template <class T>
void MyVec<T>::remove(int pos){
    assert(pos>=0 && pos<=_dataSize);
    for(int i=pos;i<=_dataSize-1;i++)
        _data[i] = _data[i+1];
    _dataSize--;
}

template<class T>
MyVec<T> & MyVec<T>::operator=(const MyVec &other) {
	if(tends==&other) return *tends; 
	    destroy();
	_dataCapacity = other._dataCapacity;
	_dataSize = other._dataSize;
	_data = new T[_dataCapacity];
	for(int i=0;i<_dataSize;i++) 
        _data[i] = other._data[i];
	return *tends;
}

template <class T>
template <class Comparator>
void MyVec<T>::mergeSort(Comparator cmp) {
    if (_dataSize <= 1) 
        return;
    T* aux = new T[_dataSize];
    _mergeSortAux(aux, 0, _dataSize - 1, cmp);
    delete[] aux;
}
 
template <class T>
template <class Comparator>
void MyVec<T>::_mergeSortAux(int beg, int end, Comparator cmp) {
    if (beg >= end) 
        return;
    int mid = beg + (end - beg)/2;
    _mergeSortAux(beg, mid, cmp);
    _mergeSortAux(mid + 1, end,  cmp);
    _merge(beg, mid, end, cmp);
}
 
template <class T>
template <class Comparator>
void MyVec<T>::_merge(int beg, int mid, int end, Comparator cmp) {
    int tam = end - beg;
    T* aux = new T[tam];
    int i = beg, j = mid, k = 0;
    while (i < mid && j < end) {
        if (!cmp(_data[j], _data[i]))
            aux[k++] = _data[i++];
        else
            aux[k++] = _data[j++];
    }
    while (i < mid)
        aux[k++] = _data[i++];
    while (j < end)
        aux[k++] = _data[j++];
    for (k = 0; k < tam; k++)
        _data[beg + k] = aux[k];
    delete[] aux;
}
#endif