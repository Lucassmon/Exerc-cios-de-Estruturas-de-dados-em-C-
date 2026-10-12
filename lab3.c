#include <stdio.h>
#include <stdlib.h>
//faz o L
long long memoria[101][8][8];

long long resolver(int movimentos_restantes, int linha_atual, int coluna_atual, int linha_alvo, int coluna_alvo) {
    if (linha_atual < 0 || linha_atual >= 8 || coluna_atual < 0 || coluna_atual >= 8) {
        return 0;
    }
    if (memoria[movimentos_restantes][linha_atual][coluna_atual] != -1) {
        return memoria[movimentos_restantes][linha_atual][coluna_atual];
    }
    if (movimentos_restantes == 0) {
        return (linha_atual == linha_alvo && coluna_atual == coluna_alvo) ? 1 : 0;
    }

    long long total_trajetorias = 0;
    int delta_linha[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int delta_coluna[] = {-1, 1, -2, 2, -2, 2, -1, 1};

    for (int i = 0; i < 8; i++) {
        int proxima_linha = linha_atual + delta_linha[i];
        int proxima_coluna = coluna_atual + delta_coluna[i];
        total_trajetorias += resolver(movimentos_restantes - 1, proxima_linha, proxima_coluna, linha_alvo, coluna_alvo);
    }

    memoria[movimentos_restantes][linha_atual][coluna_atual] = total_trajetorias;
    return total_trajetorias;
}

long long contar_trajetorias(int linha_origem, int coluna_origem, int linha_alvo, int coluna_alvo, int movimentos) {
    if (movimentos < 0) {
        return -1;
    }

    for (int i = 0; i <= movimentos; i++) {
        for (int j = 0; j < 8; j++) {
            for (int k = 0; k < 8; k++) {
                memoria[i][j][k] = -1;
            }
        }
    }

    return resolver(movimentos, linha_origem, coluna_origem, linha_alvo, coluna_alvo);
}

int main() {
    int linha_origem, coluna_origem, linha_alvo, coluna_alvo, movimentos;

    if (scanf("%d %d %d %d %d", &linha_origem, &coluna_origem, &linha_alvo, &coluna_alvo, &movimentos) != 5) {
        fprintf(stderr, "Erro ao ler a entrada.\n");
        return 1;
    }

    if (movimentos < 0) {
        printf("-1\n");
        return 0;
    }

    long long resultado = contar_trajetorias(linha_origem, coluna_origem, linha_alvo, coluna_alvo, movimentos);
    printf("%lld\n", resultado);

    return 0;
}
//L feito



