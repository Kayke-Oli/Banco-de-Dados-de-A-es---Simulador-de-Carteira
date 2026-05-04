#include <iostream>
#include "data.h"
#include <string>
#include <iomanip>
#include <cassert>

Data::Data() : _dia(0), _mes(0), _ano(0){}

Data::Data(int dia, int mes, int ano) : _dia(dia), _mes(mes), _ano(ano){}

Data::Data(const std::string& data){
    //Garantir que o formator seja: DD/MM/AAAA
    assert(data.size()==10 && data[2] == '/' && data[5] == '/');
    _dia = std::stoi(data.substr(0, 2));
    _mes = std::stoi(data.substr(3, 2));
    _ano = std::stoi(data.substr(6, 4));  
}

int Data::get_dia() const{
    return _dia;
}
    
int Data::get_mes() const{
    return _mes;
}
    
int Data::get_ano() const{
    return _ano;
}
    
int Data::to_int() const{
    return _ano*10000 + _mes*100 + _dia;
}

bool Data::operator<(const Data& outro) const{
    return to_int() < outro.to_int();
} 

bool Data::operator<=(const Data& outro) const{
    return to_int() <= outro.to_int();
}

bool Data::operator>(const Data& outro) const{
    return to_int() > outro.to_int();
}

bool Data::operator==(const Data& outro) const{
    return to_int() == outro.to_int();
}

bool Data::operator!=(const Data& outro) const{
    return to_int() != outro.to_int();
}

std::istream& operator>>(std::istream& in, Data& d) {
    char sep;
    in >> d._dia >> sep >> d._mes >> sep >> d._ano;
    return in;
}

std::ostream& operator<<(std::ostream& out, const Data& d) {
    if (d._dia < 10) 
        out << '0';
    out << d._dia << '/';
    if (d._mes < 10) 
        out << '0';
    out << d._mes << '/' << d._ano;
    return out;
}