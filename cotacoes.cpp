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
    _registros.mergeSort();
}

int CotacaoTicker::buscaBinaria(const Data& data) const{

}

int CotacaoTicker::buscaSequencial(const Data&data) const{

}

