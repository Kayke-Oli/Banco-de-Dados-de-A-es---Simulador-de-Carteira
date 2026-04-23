#include <iostream>
#include "cotacoes.h"
#include <cassert>

CotacaoTicker::CotacaoTicker() : _ticker(""), _registros(nullptr), _tamanho(0), _capacidade(0) {}

CotacaoTicker::CotacaoTicker(const std::string& ticker) : _ticker(ticker), _tamanho(0), _capacidade(4) {
    _registros = new RegistroCotacao[_capacidade];
}

CotacaoTicker::~CotacaoTicker(){
    delete[] _registros;
}

