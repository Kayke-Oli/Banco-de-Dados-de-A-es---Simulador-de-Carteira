# Banco-de-Dados-de-Acoes---Simulador-de-Carteira
Este projeto consiste na implementação de um sistema de simulação e consulta de carteira de ações em C++, desenvolvido como trabalho prático da disciplina INF213 (Estrutura de Dados) da UFV.

O programa recebe via stdin um arquivo com quatro seções: histórico de cotações diárias, histórico de dividendos, composição inicial da carteira e uma lista de operações a executar. A partir desses dados, ele responde a consultas sobre o valor da carteira em datas específicas, calcula dividendos recebidos em intervalos de tempo, ordena a carteira por diferentes critérios e simula aportes mensais com rebalanceamento automático.

Todo o armazenamento é feito em arrays dinâmicos implementados manualmente (sem uso de vector, map ou algoritmos prontos da STL), e todos os valores monetários são tratados como inteiros em centavos para evitar erros de ponto flutuante. As consultas mais frequentes utilizam busca binária sobre dados pré-ordenados, garantindo eficiência mesmo com entradas de até 500 mil linhas. A ordenação da carteira é feita com um algoritmo estável e sub-quadrático, também implementado do zero.

O projeto reforça na prática conceitos de alocação dinâmica de memória, algoritmos de ordenação e pesquisa, manipulação de strings e organização de código em classes.
