#include <iostream>
#include <string>
#include <iomanip>
#include "data.h"
#include "cotacoes.h"
#include "historicoDividendos.h"
#include "carteira.h"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    int nCotacoes;
    std::cin >> nCotacoes;
    Cotacao cotacao;
    cotacao.ler(nCotacoes);
    cotacao.ordenarTodos();

    int nDividendos;
    std::cin >> nDividendos;
    HistoricoDividendo historico;
    historico.ler(nDividendos);
    historico.ordenarTodos();

    int nCarteira;
    std::cin >> nCarteira;
    Carteira carteira;
    carteira.ler(nCarteira);

    std::string formato;
    std::cin >> formato;
    bool mostrarCabecalhos = (formato == "mostrarCabecalhos");
    bool compacta = (formato == "compacta");

    std::string operacao;
    while (std::cin >> operacao) {
        if (operacao == "valor" || operacao == "valorFast") {
            Data data;
            std::cin >> data;

            int total = 0;
            MyVec<int> valores;

            for (int i = 0; i < carteira.tamanho(); i++) {
                const Acao& a = carteira.get(i);
                const CotacaoTicker* ct = cotacao.buscarTicker(a.ticker);
                int preco = -1;
                if (ct != nullptr) {
                    if (operacao == "valorFast")
                        preco = ct->buscaBinaria(data);
                    else
                        preco = ct->buscaSequencial(data);
                }
                int val = preco * a.quantidade;
                valores.push_back(val);
                total += val;
            }

            if (compacta) {
                std::cout << std::fixed << std::setprecision(2) << total / 100.0 << '\n';
            } else {
                if (mostrarCabecalhos) {
                    std::cout << "Data: " << data << '\n';
                    std::cout << std::left  << std::setw(7)  << "Ticker" << std::right << std::setw(10) << "Quantidade" << std::right << std::setw(14) 
                              << "Compra" << std::right << std::setw(14) << "Dividendo" << std::right << std::setw(14) << "Valor" << '\n';
                }
                for (int i = 0; i < carteira.tamanho(); i++) {
                    const Acao& a = carteira.get(i);
                    std::cout << std::left  << std::setw(7)  << a.ticker << std::right << std::setw(10) << a.quantidade << std::fixed << std::setprecision(2)
                              << std::right << std::setw(14) << a.custoTotal / 100.0 << std::right << std::setw(14) << a.dividendoAcumulado / 100.0
                              << std::right << std::setw(14) << valores[i] / 100.0 << '\n';
                }
                std::cout << std::left << std::setw(45) << "Valor total da carteira:" << std::fixed << std::setprecision(2) << std::right << std::setw(14) << total / 100.0 << '\n';
                if (mostrarCabecalhos) 
                    std::cout << '\n';
            }
        }
        else if (operacao == "mimax") {
            Data inicio, fim;
            std::cin >> inicio >> fim;

            int minVal = -1, maxVal = -1;
            Data minData, maxData;

            MyVec<const CotacaoTicker*> cache_ct;
            for (int j = 0; j < carteira.tamanho(); j++) {
                cache_ct.push_back(cotacao.buscarTicker(carteira.get(j).ticker));
            }

            for (int i = 0; i < carteira.tamanho(); i++) {
                const CotacaoTicker* ct0 = cache_ct[i];
                if (ct0 == nullptr) 
                    continue;
                int p = ct0->primeiro(inicio);
                int u = ct0->ultimo(fim);
                if (p > u) continue;

                for (int d = p; d <= u; d++) {
                    const Data& dataAtual = ct0->get_registro(d).data;
                    int totalDia = 0;
                    bool valido = true;
                    for (int j = 0; j < carteira.tamanho(); j++) {
                        const CotacaoTicker* ct = cache_ct[j];
                        if (ct == nullptr) { 
                            valido = false; break; }
                        int preco = ct->buscaBinaria(dataAtual);
                        if (preco == -1) { 
                            valido = false; break; }
                        totalDia += preco * carteira.get(j).quantidade;
                    }
                    if (!valido) 
                        continue;
                    if (minVal == -1 || totalDia < minVal) { 
                        minVal = totalDia; minData = dataAtual; }
                    if (maxVal == -1 || totalDia > maxVal) { 
                        maxVal = totalDia; maxData = dataAtual; }
                }
                break; 
            }   

            if (compacta) {
                std::cout << std::fixed << std::setprecision(2) << minVal / 100.0 << '\n' << maxVal / 100.0 << '\n';
            } else {
                if (mostrarCabecalhos)
                    std::cout << "Minimos e maximos no intervalo: " << inicio << " a " << fim << '\n';
                std::cout << "Valor minimo no dia " << minData << ":" << std::fixed << std::setprecision(2) << std::right << std::setw(14) << minVal / 100.0 << '\n';
                std::cout << "Valor maximo no dia " << maxData << ":" << std::fixed << std::setprecision(2) << std::right << std::setw(14) << maxVal / 100.0 << '\n';
                if (mostrarCabecalhos) std::cout << '\n';
            }
        }
        else if (operacao == "dividendo") {
            Data inicio, fim;
            std::cin >> inicio >> fim;

            int totalGeral = 0;
            MyVec<int> divs;

            for (int i = 0; i < carteira.tamanho(); i++) {
                const Acao& a = carteira.get(i);
                const DividendoTicker* dt = historico.buscarTicker(a.ticker);
                int soma = 0;
                if (dt != nullptr)
                    soma = dt->somatorio(inicio, fim) * a.quantidade;
                divs.push_back(soma);
                totalGeral += soma;
            }

            if (compacta) {
                std::cout << std::fixed << std::setprecision(2) << totalGeral / 100.0 << '\n';
            } else {
                if (mostrarCabecalhos) {
                    std::cout << "Dividendos no intervalo: " << inicio << " a " << fim << '\n';
                    std::cout << std::left  << std::setw(7)  << "Ticker" << std::right << std::setw(10) << "Quantidade" << std::right << std::setw(14) << "Compra"
                              << std::right << std::setw(14) << "Dividendo" << std::right << std::setw(14) << "Div.inter." << '\n';
                }
                for (int i = 0; i < carteira.tamanho(); i++) {
                    const Acao& a = carteira.get(i);
                    std::cout << std::left  << std::setw(7)  << a.ticker << std::right << std::setw(10) << a.quantidade << std::fixed << std::setprecision(2)
                              << std::right << std::setw(14) << a.custoTotal / 100.0 << std::right << std::setw(14) << a.dividendoAcumulado / 100.0
                              << std::right << std::setw(14) << divs[i] / 100.0 << '\n';
                }
                std::cout << std::left << std::setw(45) << "Total de dividendos:" << std::fixed << std::setprecision(2)
                          << std::right << std::setw(14) << totalGeral / 100.0 << '\n';
                if (mostrarCabecalhos) 
                    std::cout << '\n';
            }
        }
        else if (operacao == "ordenar") {
            std::string criterio;
            std::cin >> criterio;
            carteira.ordenar(criterio);
        }
        else if (operacao == "aporte") {
            Data data;
            double valorAporteD;
            std::cin >> data >> valorAporteD;
            int saldo = valorAporteD * 100 + 0.5;

            int tamOriginal = carteira.tamanho();
            if (tamOriginal == 0) continue; // Trava de segurança

            MyVec<int> precos;
            for (int i = 0; i < tamOriginal; i++) {
                const CotacaoTicker* ct = cotacao.buscarTicker(carteira.get(i).ticker);
                if (ct == nullptr)
                    precos.push_back(-1);
                else
                    precos.push_back(ct->buscaBinaria(data));
            }

            const int INF = 2000000000;
            MyVec<int> valoresAtual;
            for (int i = 0; i < tamOriginal; i++) {
                if (precos[i] <= 0) {
                    valoresAtual.push_back(INF); // Cega ações sem preço no dia
                } else {
                    valoresAtual.push_back(precos[i] * carteira.get(i).quantidade);
                }
            }

            MyVec<int> qtdComprada(tamOriginal);

            // VOLTAMOS PARA A SUA LÓGICA ORIGINAL (1 POR 1)
            // Como a memória já foi otimizada nos outros arquivos, isso vai rodar rápido!
            while (true) {
                int idx = -1;
                for (int i = 0; i < tamOriginal; i++) {
                    if (precos[i] <= 0 || valoresAtual[i] == INF) continue;

                    if (idx == -1) {
                        idx = i;
                    } else if (valoresAtual[i] < valoresAtual[idx] || 
                              (valoresAtual[i] == valoresAtual[idx] && carteira.get(i).ticker < carteira.get(idx).ticker)) {
                        idx = i;
                    }
                }
                
                // Condição de parada: saldo não paga a mais barata ou não há ações válidas
                if (idx == -1 || saldo < precos[idx])
                    break;
                
                saldo -= precos[idx];
                valoresAtual[idx] += precos[idx];
                qtdComprada[idx]++;
            }

            int totalAportado = 0;
            if (!compacta && mostrarCabecalhos) {
                std::cout << "Dados do aporte:\n";
                std::cout << std::left  << std::setw(7)  << "Ticker" << std::right << std::setw(10) << "Quantidade" << std::right << std::setw(14) << "Valor" << '\n';
            }
            
            for (int i = 0; i < tamOriginal; i++) {
                if (qtdComprada[i] == 0) 
                    continue;
                
                int valorCompra = qtdComprada[i] * precos[i];
                totalAportado += valorCompra;
                
                // Aplica tudo na carteira de forma eficiente fora do laço
                carteira.aporte(carteira.get(i).ticker, qtdComprada[i], precos[i]);
                
                if (!compacta) {
                    std::cout << std::left  << std::setw(7)  << carteira.get(i).ticker << std::right << std::setw(10) << qtdComprada[i]
                              << std::fixed << std::setprecision(2) << std::right << std::setw(14) << valorCompra / 100.0 << '\n';
                }
            }
            
            if (!compacta) {
                std::cout << std::left << std::setw(17) << "Total aportado:" << std::fixed << std::setprecision(2) << std::right << std::setw(14) << totalAportado / 100.0 << '\n';
                if (mostrarCabecalhos) 
                    std::cout << '\n';
            } else {
                std::cout << std::fixed << std::setprecision(2) << totalAportado / 100.0 << '\n';
            }
        }
    }

    return 0;
}