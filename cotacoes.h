#ifndef COTACOES_H
#define COTACOES_H
#include "data.h"
#include "myVec.h"
#include <string>
#include <iostream>

//Um registro de cotação
struct RegistroCotacao {
    Data data;
    int preco; 
};

//Cotação de uma ação em específico
class CotacaoTicker{
private:
    std::string _ticker;
    MyVec<RegistroCotacao> _registros;
public:
    //Construtores
    CotacaoTicker();
    CotacaoTicker(const std::string& ticker);
    //Destrutores não são necessários, devido ao uso do MyVec
    //Funções da Classe CotacaoTicker
    const std::string& get_ticker() const {return _ticker;};
    void adicionar(const Data& data, int preco);
    void ordenar();
    int buscaSequencial(const Data& data) const;
    int buscaBinaria(const Data& data) const;
    int primeiro(const Data& firstData) const;
    int ultimo(const Data& lastData) const;
    int get_tamanho() const { return _registros.size();};
    const RegistroCotacao& get_registro(int res) const { return _registros[res];};
};

//Banco completo de cotações
class Cotacao{
private:
    MyVec<CotacaoTicker> _tickers;
    CotacaoTicker* buscar_criar(const std::string& ticker);
public:
    Cotacao();
    void ler(int n);
    void ordenarTodos();
    const CotacaoTicker* buscarTicker(const std::string& ticker) const;
};

#endif