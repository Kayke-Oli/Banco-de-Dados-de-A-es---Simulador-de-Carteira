#include <iostream>
#include <string>
#include <iomanip>
#include "data.h"
#include "cotacoes.h"
#include "historicoDividendos.h"
#include "carteira.h"

int main() {
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

    // Leitura do formato de saída
    std::string formato;
    std::cin >> formato;
    bool mostrarCabecalhos = (formato == "mostrarCabecalhos");
    bool compacta = (formato == "compacta");

    // Processamento das operações                                         
    std::string operacao;
    while (std::cin >> operacao) {
        // valor                                                           
        if (operacao == "valor" || operacao == "valorFast") {
            Data data;
            std::cin >> data;

            // Calcula valor de cada ação e total
            int total = 0;
            MyVec<int> valores; // valor total de cada ação no dia

            for (int i = 0; i < carteira.tamanho(); i++) {
                const Acao& a = carteira.get(i);
                const CotacaoTicker* ct = cotacao.buscarTicker(a.ticker);
                int preco = (operacao == "valorFast");
                if (operacao == "valorFast")
                    preco = ct->buscaBinaria(data);
                else
                    preco = ct->buscaSequencial(data);
                int val = preco * a.quantidade;
                valores.push_back(val);
                total += val;
            }

            if (compacta) {
                std::cout << std::fixed << std::setprecision(2) << total / 100.0 << '\n';
            } else {
                if (mostrarCabecalhos) {
                    std::cout << "Data: " << data << '\n';
                    std::cout << std::left << std::setw(10) << "Ticker" << std::setw(12) << "Quantidade" << std::setw(12) << "Compra" << std::setw(12) << "Dividendo" << "Valor" << '\n';
                }
                for (int i = 0; i < carteira.tamanho(); i++) {
                    const Acao& a = carteira.get(i);
                    std::cout << std::left << std::setw(10) << a.ticker << std::setw(12) << a.quantidade << std::fixed << std::setprecision(2) << std::setw(12) << a.custoTotal / 100.0
                              << std::setw(12) << a.dividendoAcumulado / 100.0
                              << valores[i] / 100.0 << '\n';
                }
                std::cout << "Valor total da carteira: " << std::fixed << std::setprecision(2) << total / 100.0 << '\n';
                if (mostrarCabecalhos) std::cout << '\n';
            }
        }
        // mimax                                                          
        else if (operacao == "mimax") {
            Data inicio, fim;
            std::cin >> inicio >> fim;

            // Usa o primeiro ticker da carteira para obter os dias com cotação
            // no intervalo — todos os tickers têm cotação nos mesmos dias
            const CotacaoTicker* ct0 = cotacao.buscarTicker(carteira.get(0).ticker);
            int p = ct0->primeiro(inicio);
            int u = ct0->ultimo(fim);

            int minVal = -1, maxVal = -1;
            Data minData, maxData;

            for (int d = p; d <= u; d++) {
                const Data& dataAtual = ct0->get_registro(d).data;
                // Soma o valor de todas as ações da carteira nesse dia
                int totalDia = 0;
                for (int i = 0; i < carteira.tamanho(); i++) {
                    const Acao& a = carteira.get(i);
                    const CotacaoTicker* ct = cotacao.buscarTicker(a.ticker);
                    int preco = ct->buscaBinaria(dataAtual);
                    totalDia += preco * a.quantidade;
                }
                // Atualiza mínimo (empate: mantém primeira data)
                if (minVal == -1 || totalDia < minVal) {
                    minVal  = totalDia;
                    minData = dataAtual;
                }
                // Atualiza máximo (empate: mantém primeira data)
                if (maxVal == -1 || totalDia > maxVal) {
                    maxVal  = totalDia;
                    maxData = dataAtual;
                }
            }

            if (compacta) {
                std::cout << std::fixed << std::setprecision(2)
                          << minVal / 100.0 << '\n'
                          << maxVal / 100.0 << '\n';
            } else {
                if (mostrarCabecalhos)
                    std::cout << "Minimos e maximos no intervalo: " << inicio << " a " << fim << '\n';
                std::cout << "Valor minimo no dia " << minData << ": " << std::fixed << std::setprecision(2) << minVal / 100.0 << '\n';
                std::cout << "Valor maximo no dia " << maxData << ": " << std::fixed << std::setprecision(2) << maxVal / 100.0 << '\n';
                if (mostrarCabecalhos) 
                    std::cout << '\n';
            }
        }
        // dividendo                                                       
        else if (operacao == "dividendo") {
            Data inicio, fim;
            std::cin >> inicio >> fim;

            int totalGeral = 0;
            MyVec<int> divs; // dividendo por ação no intervalo

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
                    std::cout << std::left << std::setw(10) << "Ticker" << std::setw(12) << "Quantidade" << std::setw(12) << "Compra" << std::setw(12) << "Dividendo" << "Div.inter." << '\n';
                }
                for (int i = 0; i < carteira.tamanho(); i++) {
                    const Acao& a = carteira.get(i);
                    std::cout << std::left
                              << std::setw(10) << a.ticker
                              << std::setw(12) << a.quantidade
                              << std::fixed << std::setprecision(2)
                              << std::setw(12) << a.custoTotal / 100.0
                              << std::setw(12) << a.dividendoAcumulado / 100.0
                              << divs[i] / 100.0 << '\n';
                }
                std::cout << "Total de dividendos: " << std::fixed << std::setprecision(2) << totalGeral / 100.0 << '\n';
                if (mostrarCabecalhos) 
                    std::cout << '\n';
            }
        }
        // ordenar                                                         
        else if (operacao == "ordenar") {
            std::string criterio;
            std::cin >> criterio;
            carteira.ordenar(criterio);
        }
        // aporte                                                          
        else if (operacao == "aporte") {
            Data data;
            double valorAporteD;
            std::cin >> data >> valorAporteD;
            int saldo = valorAporteD * 100 + 0.5; // em centavos

            // Preços das ações no dia do aporte (busca binária)
            MyVec<int> precos;
            for (int i = 0; i < carteira.tamanho(); i++) {
                const CotacaoTicker* ct = cotacao.buscarTicker(carteira.get(i).ticker);
                precos.push_back(ct->buscaBinaria(data));
            }

            // Valor atual de cada ação na carteira
            MyVec<int> valoresAtual;
            for (int i = 0; i < carteira.tamanho(); i++)
                valoresAtual.push_back(precos[i] * carteira.get(i).quantidade);

            // Registra compras para imprimir depois
            MyVec<int> qtdComprada(carteira.tamanho()); // inicializado com 0

            // Algoritmo: compra 1 ação da empresa com menor valor total
            int tamOriginal = carteira.tamanho();
            while (true) {
                // Encontra a empresa com menor valor (empate: ticker menor)
                int idx = 0;
                for (int i = 0; i < carteira.tamanho(); i++) {
                    if (valoresAtual[i] < valoresAtual[idx] || (valoresAtual[i] == valoresAtual[idx] && carteira.get(i).ticker < carteira.get(idx).ticker)) {
                        idx = i;
                    }
                }
                if(saldo < precos[idx])
                    break;
                // Nenhuma empresa pode ser comprada
                if (idx == -1) 
                    break;
                // Verifica se saldo é suficiente para comprar a de menor valor
                if (saldo < precos[idx]) 
                    break;

                // Compra 1 ação
                saldo -= precos[idx];
                valoresAtual[idx] += precos[idx];
                qtdComprada[idx]++;
                carteira.aporte(carteira.get(idx).ticker, 1, precos[idx]);

                
            }

            // Imprime detalhes do aporte
            int totalAportado = 0;
            if (!compacta && mostrarCabecalhos) {
                std::cout << "Dados do aporte:\n";
                std::cout << std::left << std::setw(10) << "Ticker" << std::setw(12) << "Quantidade" << "Valor" << '\n';
            }
            for (int i = 0; i < tamOriginal; i++) {
                if (qtdComprada[i] == 0) 
                    continue;
                int valorCompra = qtdComprada[i] * precos[i];
                totalAportado += valorCompra;
                if (!compacta) {
                    std::cout << std::left << std::setw(10) << carteira.get(i).ticker << std::setw(12) << qtdComprada[i] << std::fixed << std::setprecision(2) << valorCompra / 100.0 << '\n';
                }
            }
            if (!compacta) {
                std::cout << "Total aportado: " << std::fixed << std::setprecision(2) << totalAportado / 100.0 << '\n';
                if (mostrarCabecalhos) 
                    std::cout << '\n';
            } else {
                std::cout << std::fixed << std::setprecision(2) << totalAportado / 100.0 << '\n';
            }
        }
    }

    return 0;
}