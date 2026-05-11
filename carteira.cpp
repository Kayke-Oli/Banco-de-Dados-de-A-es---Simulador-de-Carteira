#include <iostream>
#include "carteira.h"
#include <iostream>
#include <iomanip>

Carteira::Carteira() {}

// Busca uma ação pelo ticker; retorna nullptr se não encontrar
Acao* Carteira::buscar(const std::string& ticker){
    for (int i = 0; i < _acoes.size(); i++) {
        if (_acoes[i].ticker == ticker)
            return &_acoes[i];
    }
    return nullptr;
}

// Lê n ações: ticker quantidade custoTotal dividendoAcumulado
void Carteira::ler(int n) {
    for (int i = 0; i < n; i++) {
        Acao a;
        double custo, dividendo;
        std::cin >> a.ticker >> a.quantidade >> custo >> dividendo;
        a.custoTotal = custo*100 + 0.5;
        a.dividendoAcumulado = dividendo * 100 + 0.5;
        _acoes.push_back(a);
    }
}

// Busca sequencial: retorna o preço do ticker na data, ou -1 se não encontrar
void Carteira::valor(const std::string& ticker, const Data& data, const Cotacao& cot) const {
    const CotacaoTicker* ct = cot.buscarTicker(ticker);
    if (ct == nullptr) {
        std::cout << "Ticker " << ticker << " nao encontrado.\n";
        return;
    }
    int preco = ct->buscaSequencial(data);
    if (preco == -1) {
        std::cout << "Cotacao nao encontrada para " << ticker << " em " << data << ".\n";
        return;
    }
    const Acao* a = nullptr;
    for (int i = 0; i < _acoes.size(); i++)
        if (_acoes[i].ticker == ticker){ 
            a = &_acoes[i]; 
            break;}
    if (a == nullptr) {
        std::cout << "Acao " << ticker << " nao encontrada na carteira.\n";
        return;
    }
    int valorTotal = preco * a->quantidade;
    std::cout << ticker << " " << data << " " << std::fixed << std::setprecision(2) << valorTotal / 100.0 << "\n";
}

// Busca binária: retorna o preço do ticker na data, ou -1 se não encontrar
void Carteira::valorFast(const std::string& ticker, const Data& data, const Cotacao& cot) const {
    const CotacaoTicker* ct = cot.buscarTicker(ticker);
    if (ct == nullptr) {
        std::cout << "Ticker " << ticker << " nao encontrado.\n";
        return;
    }
    int preco = ct->buscaBinaria(data);
    if (preco == -1) {
        std::cout << "Cotacao nao encontrada para " << ticker << " em " << data << ".\n";
        return;
    }
    const Acao* a = nullptr;
    for (int i = 0; i < _acoes.size(); i++)
        if (_acoes[i].ticker == ticker){ 
            a = &_acoes[i]; 
            break;}
    if (a == nullptr) {
        std::cout << "Acao " << ticker << " nao encontrada na carteira.\n";
        return;
    }
    int valorTotal = preco * a->quantidade;
    std::cout << ticker << " " << data << " " << std::fixed << std::setprecision(2) << valorTotal / 100.0 << "\n";
}

// Retorna o menor e maior preço do ticker no intervalo [inicio, fim]
void Carteira::mimax(const std::string& ticker, const Data& inicio, const Data& fim, const Cotacao& cot) const {
    const CotacaoTicker* ct = cot.buscarTicker(ticker);
    if (ct == nullptr) {
        std::cout << "Ticker " << ticker << " nao encontrado.\n";
        return;
    }
    int p = ct->primeiro(inicio);
    int u = ct->ultimo(fim);
    if (p > u) {
        std::cout << "Nenhuma cotacao no intervalo para " << ticker << ".\n";
        return;
    }
    int minPreco = ct->get_registro(p).preco;
    int maxPreco = ct->get_registro(p).preco;
    for (int i = p + 1; i <= u; i++) {
        int preco = ct->get_registro(i).preco;
        if (preco < minPreco) 
            minPreco = preco;
        if (preco > maxPreco) 
            maxPreco = preco;
    }
    std::cout << ticker << " " << inicio << " " << fim << " " << std::fixed << std::setprecision(2) << minPreco / 100.0 << " " << maxPreco / 100.0 << "\n";
}

// Soma os dividendos do ticker no intervalo [inicio, fim]
void Carteira::dividendo(const std::string& ticker, const Data& inicio, const Data& fim, const HistoricoDividendo& hist) const {
    const Acao* a = nullptr;
    for (int i = 0; i < _acoes.size(); i++)
        if (_acoes[i].ticker == ticker){ 
            a = &_acoes[i]; 
            break;}
    if (a == nullptr) {
        std::cout << "Acao " << ticker << " nao encontrada na carteira.\n";
        return;
    }
    const DividendoTicker* dt = hist.buscarTicker(ticker);
    if (dt == nullptr) {
        std::cout << "Nenhum dividendo encontrado para " << ticker << ".\n";
        return;
    }
    int total = dt->somatorio(inicio, fim) * a->quantidade;
    std::cout << ticker << " " << inicio << " " << fim << " " << std::fixed << std::setprecision(2) << total / 100.0 << "\n";
}

// Ordena as ações da carteira pelo critério especificado
void Carteira::ordenar(const std::string& criterio) {
    if (criterio == "ticker") {
        _acoes.mergeSort([](const Acao& a, const Acao& b) {
            return a.ticker < b.ticker;
        });
    } else if (criterio == "quantidade") {
        _acoes.mergeSort([](const Acao& a, const Acao& b) {
            return a.quantidade > b.quantidade;
        });
    } else if (criterio == "custo") {
        _acoes.mergeSort([](const Acao& a, const Acao& b) {
            return a.custoTotal > a.custoTotal;
        });
    } else if (criterio == "dividendo") {
        _acoes.mergeSort([](const Acao& a, const Acao& b) {
            return a.dividendoAcumulado < b.dividendoAcumulado;
        });
    }
    else if (criterio == "dividendoticker") {
    std::cerr << "--- ANTES dividendoticker ---\n";
    for (int i = 0; i < _acoes.size(); i++)
        std::cerr << _acoes[i].ticker << " div=" << _acoes[i].dividendoAcumulado << "\n";

    _acoes.mergeSort([](const Acao& a, const Acao& b) {
        if (a.dividendoAcumulado != b.dividendoAcumulado)
            return a.dividendoAcumulado > b.dividendoAcumulado;
        return a.ticker < b.ticker;
    });

    std::cerr << "--- DEPOIS dividendoticker ---\n";
    for (int i = 0; i < _acoes.size(); i++)
        std::cerr << _acoes[i].ticker << " div=" << _acoes[i].dividendoAcumulado << "\n";
}
}

// Adiciona uma compra à carteira
void Carteira::aporte(const std::string& ticker, int quantidade, int preco) {
    Acao* a = buscar(ticker);
    if (a != nullptr) {
        // Ticker já existe — atualiza quantidade e custo
        a->quantidade += quantidade;
        a->custoTotal += quantidade * preco;
    } else {
        // Ticker novo — adiciona à carteira
        Acao nova;
        nova.ticker = ticker;
        nova.quantidade = quantidade;
        nova.custoTotal = quantidade * preco;
        nova.dividendoAcumulado = 0;
        _acoes.push_back(nova);
    }
}

// Imprime todas as ações da carteira
std::ostream& operator<<(std::ostream& out, const Carteira& c) {
    for (int i = 0; i < c._acoes.size(); i++) {
        const Acao& a = c._acoes[i];
        out << a.ticker << " " << a.quantidade << " " << std::fixed << std::setprecision(2) << a.custoTotal / 100.0 << " " << a.dividendoAcumulado / 100.0 << "\n";
    }
    return out;
}