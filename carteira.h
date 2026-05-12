#ifndef CARTEIRA_H
#define CARTEIRA_H
#include "myVec.h"
#include "data.h"
#include "cotacoes.h"
#include "historicoDividendos.h"
#include <string>
#include <iostream>

struct Acao
{
    std::string ticker;
    int quantidade = 0;
    long long custoTotal = 0;
    long long dividendoAcumulado = 0;
};

class Carteira
{
private:
    MyVec<Acao> _acoes;
    Acao *buscar(const std::string &ticker);

public:
    Carteira();
    void ler(int n);

    // Operações do trabalho
    void valor(const std::string &ticker, const Data &data, const Cotacao &cot) const;
    void valorFast(const std::string &ticker, const Data &data, const Cotacao &cot) const;
    void mimax(const std::string &ticker, const Data &inicio, const Data &fim, const Cotacao &cot) const;
    void dividendo(const std::string &ticker, const Data &inicio, const Data &fim, const HistoricoDividendo &hist) const;
    void ordenar(const std::string &criterio);
    void aporte(const std::string &ticker, int quantidade, int preco);
    int tamanho() const { return _acoes.size(); };
    const Acao &get(int i) const { return _acoes[i]; };

    friend std::ostream &operator<<(std::ostream &out, const Carteira &c);
};
#endif