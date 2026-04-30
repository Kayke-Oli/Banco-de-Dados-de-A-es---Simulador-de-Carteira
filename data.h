#ifndef DATA_H
#define DATA_H
#include <string>

class Data{
private:
    int _dia;
    int _mes;
    int _ano;
public:
    Data();
    Data(int dia, int mes, int ano);
    Data(const std::string& data); //Construtor para receber data como string
    int get_dia() const;
    int get_mes() const;
    int get_ano() const;
    int to_int() const; //converte a data. Ex: 11/12/2024 fica 20241211
    //Como a ordem importa, converter dessa maneira fica mais fácil de ordenar para a busca binária
    bool operator<(const Data& outro) const; //Operators para a comparação das datas
    bool operator<=(const Data& outro) const;
    bool operator>(const Data& outro) const;
    bool operator==(const Data& outro) const;
    bool operator!=(const Data& outro) const;
    friend std::istream& operator>>(std::istream& in, Data& d);
    friend std::ostream& operator<<(std::ostream& out, const Data& d);
};
#endif