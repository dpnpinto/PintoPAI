#include <stdio.h>

int main() {
    // 1. Dados de Treino (Entrada x, Saída Esperada y)
    double x = 5.0;
    double y_esperado = 10.0; // Pois 5 * 2 = 10

    // 2. Parâmetros Iniciais
    double w = 0.0;             // Começamos com peso zero
    double taxa_aprendizagem = 0.01; 
    int iteracoes = 100;

    printf("Iniciando treino...\n");
    printf("Peso inicial: %.2f\n\n", w);

    for (int i = 0; i < iteracoes; i++) {
        // Passo A: Previsão (Forward Pass)
        double y_previsto = w * x;

        // Passo B: Calcular o Erro (Função de Custo: Erro Quadrático Médio)
        // Custo = (w*x - y_esperado)^2
        double custo = (y_previsto - y_esperado) * (y_previsto - y_esperado);

        // Passo C: Calcular a Derivada (Gradiente)
        // Usando a regra da cadeia: d(Custo)/dw = 2 * (w*x - y_esperado) * x
        double derivada = 2 * (y_previsto - y_esperado) * x;

        // Passo D: Atualizar o Peso (A fórmula que discutimos!)
        // w_novo = w_antigo - (taxa * derivada)
        w = w - (taxa_aprendizagem * derivada);

        if (i % 10 == 0) {
            printf("Iteracao %d: Peso = %.4f | Custo = %.4f\n", i, w, custo);
        }
    }

    printf("\nTreino concluido!\n");
    printf("Peso final encontrado: %.4f (Esperado era 2.0)\n", w);
    printf("Previsao para x=5: %.2f\n", w * x);

    return 0;
}
