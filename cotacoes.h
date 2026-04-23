#ifndef COTACOES_H
#define COTACOES_H
#include "data.h"
#include <string>

//Um registro de cotação
struct RegistroCotacao {
    Data data;
    int preco; 
};

//Cotação de uma ação em específico
class CotacaoTicker{
private:
    std::string _ticker;
    RegistroCotacao* _registros;
    int _tamanho;
    int _capacidade;

    void _redimensionar();
public:
  CotacaoTicker();
  CotacaoTicker(const std::string& ticker);
  ~CotacaoTicker();
  
  const std::string& get_ticker() const;
  void adicionar(const Data& data, int preco);
  void ordenar();
  int buscaSequencial(const Data& data) const;
  int buscaBinaria(const Data& data) const;
  int primeiro(const Data& firstData) const;
  int ultimo(const Data& lastData) const;
  int get_tamanho() const;
  const RegistroCotacao& get_registro(int i) const;
};

//Banco completo de cotações
class Cotacao{
private:
    CotacaoTicker* _tickers;
    int _numTickers;
    int _capacidade;

    CotacaoTicker* buscar_criar(const std::string& ticker);
    void redimensionar();
public:
    Cotacao();
    ~Cotacao();
    void ler(int n);
    void ordenarTodos();
    CotacaoTicker* buscarTicker(const std::string& ticker) const;
};

#endif