#include <iostream>
#include "cotacoes.h"
#include <cassert>

CotacaoTicker::CotacaoTicker() : _ticker(""){}

CotacaoTicker::CotacaoTicker(const std::string& ticker) : _ticker(ticker) {}

Cotacao::Cotacao(){}

void CotacaoTicker::adicionar(const Data& data, int preco){
    RegistroCotacao elem;
    elem.data = data;
    elem.preco = preco;
    _registros.push_back(elem);
}

void CotacaoTicker::ordenar(){
    _registros.mergeSort([](const RegistroCotacao& a, const RegistroCotacao& b){
        return a.data < b.data;
    });
}

int CotacaoTicker::buscaBinaria(const Data& data) const{
    int beg = 0, end = _registros.size() - 1;
    while (beg <= end) {
        int mid = beg + (end - beg) / 2;
        if (_registros[mid].data == data)
            return _registros[mid].preco;
        else if (_registros[mid].data < data)
            beg = mid + 1;
        else
            end = mid - 1;
    }
    return -1;
}   

int CotacaoTicker::buscaSequencial(const Data&data) const{
    for(int i=0; i<_registros.size(); i++){
        if(_registros[i].data == data)
            return _registros[i].preco;
    }
    return -1;
}

// Útil para delimitar o início de um intervalo
int CotacaoTicker::primeiro(const Data& firstData) const {
    int beg = 0, end = _registros.size();
    while (beg < end) {
        int mid = beg + (end - beg) / 2;
        if (_registros[mid].data < firstData)
            beg = mid + 1;
        else
            end = mid;
    }
    return beg;
}

// Útil para delimitar o fim de um intervalo
int CotacaoTicker::ultimo(const Data& lastData) const {
    int beg = 0, end = _registros.size() - 1, res = -1;
    while (beg <= end) {
        int mid = beg + (end - beg) / 2;
        if (_registros[mid].data <= lastData) {
            res = mid;
            beg  = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    return res;
}

// Busca o ticker no vetor; se não existir, cria e retorna ponteiro para ele
CotacaoTicker* Cotacao::buscar_criar(const std::string& ticker) {
    for (int i = 0; i < _tickers.size(); i++) {
        if (_tickers[i].get_ticker() == ticker)
            return &_tickers[i];
    }
    _tickers.push_back(CotacaoTicker(ticker));
    return &_tickers[_tickers.size() - 1];
}

void Cotacao::ler(int n) {
    for (int i = 0; i < n; i++) {
        Data data;
        std::string ticker;
        double preco;
        std::cin >> data >> ticker >> preco;
        int precoCentavos = preco * 100 + 0.5; // arredonda para centavos
        buscar_criar(ticker)->adicionar(data, precoCentavos);
    }
}

// Ordena os registros de cada ticker por data
void Cotacao::ordenarTodos() {
    for (int i = 0; i < _tickers.size(); i++)
        _tickers[i].ordenar();
}
 
// Busca um ticker no vetor;
const CotacaoTicker* Cotacao::buscarTicker(const std::string& ticker) const {
    for (int i = 0; i < _tickers.size(); i++) {
        if (_tickers[i].get_ticker() == ticker)
            return &_tickers[i];
    }
    return nullptr;
}