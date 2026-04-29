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
    void resizeCapacity(int NewCapacity);

public:
    template<class T2>
	friend std::ostream& operator<<(std::ostream &, const MyVec<T2> &);

    //Construtores
    MyVec();
    MyVec(int n, const T&init=T());
    // Construtor de cópia
    MyVec(const MyVec<T>& outro);
    //Destrutor
    ~MyVec();
    //funcoes de acesso
	T &operator[](int pos) {return _data[pos];}
	const T &operator[](int pos) const {return _data[pos];}
    // Operador de atribuição
    MyVec<T>& operator=(const MyVec<T>& outro);
    //Funções essenciais
    void push_back(const T&newData);
    void pop_back();
    void resize(int NewSize);
    void insert(int pos, const T&newData);
    void clear();
    void empty();
    int size();
    void reserve(int newCapacity)
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


#endif