<div align="center">

# 📈 Simulador de Carteira de Ações (C++)

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Algoritmos](https://img.shields.io/badge/Algoritmos-2C3E50?style=for-the-badge)
![Estruturas de Dados](https://img.shields.io/badge/Estruturas_de_Dados-34495E?style=for-the-badge)

*Um motor financeiro de alta performance desenvolvido em C++ puro para processamento e simulação de ativos, focado no controle de memória e eficiência algorítmica.*

</div>

<br>

## 📌 Sobre o Projeto

Este projeto é um simulador de investimentos focado no acompanhamento histórico de ativos e cálculo de rendimentos. Ele processa grandes volumes de dados de entrada (históricos de cotações, aportes e distribuição de dividendos) para espelhar a evolução patrimonial de uma carteira ao longo do tempo.

O grande diferencial tecnológico deste repositório é a sua **implementação "Zero STL"**. Para garantir controle absoluto sobre a alocação de memória e a performance, todas as estruturas de dados e algoritmos de busca e ordenação foram implementados do zero.

---

## 🚀 Destaques Técnicos e Arquitetura

Em vez de utilizar as facilidades da *Standard Template Library* (STL), o motor do simulador foi construído sobre fundamentos rigorosos de Ciência da Computação:

*   **Zero STL (Standard Template Library):** Substituição de `std::vector` e algoritmos prontos por arrays dinâmicos gerenciados manualmente, garantindo um profundo entendimento de ponteiros, alocação na Heap (`new`/`delete`) e prevenção de *memory leaks*.
*   **Algoritmos Nativos:** 
    *   Implementação de **Busca Binária** $O(\log n)$ para localização ultrarrápida de cotações por data.
    *   Implementação de **Ordenação Estável** (Stable Sort) $O(n \log n)$ para organização cronológica do histórico de transações.
*   **Precisão Financeira (Integer Arithmetic):** Valores monetários não utilizam tipos de ponto flutuante (`float` ou `double`) para evitar erros de arredondamento IEEE 754. Todo o sistema financeiro opera na base de centavos utilizando números inteiros.
*   **Alta Capacidade de I/O:** O sistema é capaz de processar via entrada padrão (`stdin`) pipelines de dados massivos, testado com cargas de até **500.000 linhas** contínuas de cotações sem gargalos de processamento.

---

## ⚙️ Como Executar

O projeto foi construído para ser altamente portável, compilando nativamente em qualquer ambiente Linux, macOS ou Windows (via MSYS2/MinGW).

### Pré-requisitos
* Compilador GCC (`g++`) ou Clang compatível com C++11 ou superior.

### Compilação e Execução

1. Clone este repositório:
```bash
git clone [https://github.com/Kayke-Oli/Banco-de-Dados-de-A-es---Simulador-de-Carteira.git](https://github.com/Kayke-Oli/Banco-de-Dados-de-A-es---Simulador-de-Carteira.git)
cd Banco-de-Dados-de-A-es---Simulador-de-Carteira
