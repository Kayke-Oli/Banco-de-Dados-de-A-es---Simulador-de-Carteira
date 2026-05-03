#ifndef HISTORICO_DIVIDENDOS_H
#define HISTORICO_DIVIDENDOS_H
#include "myVec.h"
#include "cotacoes.h"

struct RegistroDividendo {
    Data data;
    int valor; // em centavos
};

class DividendoTicker {
private:
    std::string _ticker;
    MyVec<RegistroDividendo> _registros;
public:
    DividendoTicker();
    DividendoTicker(const std::string& ticker);
    const std::string& get_ticker() const;
    void adicionar(const Data& data, int valor);
    void ordenar();
    int somatorio(const Data& inicio, const Data& fim) const;
    int primeiro(const Data& firstData) const;
    int ultimo(const Data& lastData) const;
    int get_tamanho() const;
    const RegistroDividendo& get_registro(int i) const;
};

class HistoricoDividendo {
private:
    MyVec<DividendoTicker> _tickers;
    DividendoTicker* buscar_criar(const std::string& ticker);
public:
    HistoricoDividendo();
    void ler(int n);
    void ordenarTodos();
    const DividendoTicker* buscarTicker(const std::string& ticker) const;
};
#endif