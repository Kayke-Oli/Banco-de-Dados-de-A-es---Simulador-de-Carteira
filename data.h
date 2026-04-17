#ifndef DATA_H
#define DATA_H
#include <string>

class Data{
private:
    int _data;
public:
    Data(int data);
    std::string converte();
    bool compara(const int& a,const int& b);
};
#endif