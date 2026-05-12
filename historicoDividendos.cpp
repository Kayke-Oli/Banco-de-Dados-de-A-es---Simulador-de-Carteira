#include <iostream>
#include "historicoDividendos.h"
#include <iostream>
#include <cassert>

DividendoTicker::DividendoTicker() : _ticker("") {}

DividendoTicker::DividendoTicker(const std::string &ticker) : _ticker(ticker) {}

const std::string &DividendoTicker::get_ticker() const
{
    return _ticker;
}

int DividendoTicker::get_tamanho() const
{
    return _registros.size();
}

const RegistroDividendo &DividendoTicker::get_registro(int i) const
{
    return _registros[i];
}

void DividendoTicker::adicionar(const Data &data, int valor)
{
    RegistroDividendo r;
    r.data = data;
    r.valor = valor;
    _registros.push_back(r);
}

void DividendoTicker::ordenar()
{
    _registros.mergeSort([](const RegistroDividendo &a, const RegistroDividendo &b)
                         { return a.data < b.data; });
}

// Retorna o índice do primeiro registro com data >= firstData
int DividendoTicker::primeiro(const Data &firstData) const
{
    int lo = 0, hi = _registros.size();
    while (lo < hi)
    {
        int mid = lo + (hi - lo) / 2;
        if (_registros[mid].data < firstData)
            lo = mid + 1;
        else
            hi = mid;
    }
    return lo;
}

// Retorna o índice do último registro com data <= lastData
int DividendoTicker::ultimo(const Data &lastData) const
{
    int lo = 0, hi = _registros.size() - 1, res = -1;
    while (lo <= hi)
    {
        int mid = lo + (hi - lo) / 2;
        if (_registros[mid].data <= lastData)
        {
            res = mid;
            lo = mid + 1;
        }
        else
        {
            hi = mid - 1;
        }
    }
    return res;
}

// Soma todos os dividendos do ticker no intervalo [inicio, fim]
int DividendoTicker::somatorio(const Data &inicio, const Data &fim) const
{
    int p = primeiro(inicio);
    int u = ultimo(fim);
    if (p > u)
        return 0; // nenhum registro no intervalo
    int total = 0;
    for (int i = p; i <= u; i++)
        total += _registros[i].valor;
    return total;
}

HistoricoDividendo::HistoricoDividendo() {}

// Busca o ticker no vetor; se não existir, cria e retorna ponteiro para ele
DividendoTicker *HistoricoDividendo::buscar_criar(const std::string &ticker)
{
    for (int i = 0; i < _tickers.size(); i++)
    {
        if (_tickers[i].get_ticker() == ticker)
            return &_tickers[i];
    }
    _tickers.push_back(DividendoTicker(ticker));
    return &_tickers[_tickers.size() - 1];
}

void HistoricoDividendo::ler(int n)
{
    _tickers.reserve(5000);
    DividendoTicker *ultimo = nullptr;

    for (int i = 0; i < n; i++)
    {
        Data data;
        std::string ticker;
        double valor;
        std::cin >> data >> ticker >> valor;
        int valorCentavos = valor * 100 + 0.5;

        if (ultimo != nullptr && ultimo->get_ticker() == ticker)
        {
            ultimo->adicionar(data, valorCentavos);
        }
        else
        {
            ultimo = buscar_criar(ticker);
            ultimo->adicionar(data, valorCentavos);
        }
    }
}

// Ordena os registros de cada ticker por data
void HistoricoDividendo::ordenarTodos()
{
    for (int i = 0; i < _tickers.size(); i++)
        _tickers[i].ordenar();
}

// Busca um ticker no vetor; retorna nullptr se não encontrar
const DividendoTicker *HistoricoDividendo::buscarTicker(const std::string &ticker) const
{
    for (int i = 0; i < _tickers.size(); i++)
    {
        if (_tickers[i].get_ticker() == ticker)
            return &_tickers[i];
    }
    return nullptr;
}