#include <iostream>
#include "data.h"
#include <string>

Data::Data(int data){
    this->_data = data;
}

std::string Data::converte(){
    std::string ds = std::to_string(_data);
    return ds;
}

bool Data::compara(const int& a, const int& b){
    if(a > b)
        return true;
    return false;
}