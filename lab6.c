#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long soma_max_global = LLONG_MIN;

typedef struct No {
    int valor;
    struct No *esq;
    struct No *dir;
} No;

No* novoNo(int valor) {
    No* no = (No*)malloc(sizeof(No));
    no->valor = valor;
    no->esq = NULL;
    no->dir = NULL;
    return no;
}

int busca(int arr[], int inicio, int fim, int valor) {
    for (int i = inicio; i <= fim; i++) {
        if (arr[i] == valor)
            return i;
    }
    return -1;
}

No* montarArvore(int in[], int pos[], int inicio, int fim, int *indice_pos) {
    if (inicio > fim)
        return NULL;

    No* no = novoNo(pos[*indice_pos]);
    (*indice_pos)--;

    if (inicio == fim)
        return no;

    int indice_in = busca(in, inicio, fim, no->valor);

    no->dir = montarArvore(in, pos, indice_in + 1, fim, indice_pos);
    no->esq = montarArvore(in, pos, inicio, indice_in - 1, indice_pos);

    return no;
}

long long somaMaxCaminhoUtil(No* raiz) {
    if (raiz == NULL)
        return 0;

    long long soma_esq = somaMaxCaminhoUtil(raiz->esq);
    long long soma_dir = somaMaxCaminhoUtil(raiz->dir);

    long long soma_atual = (long long)raiz->valor + soma_esq + soma_dir;

    if (soma_atual > soma_max_global)
        soma_max_global = soma_atual;

    long long soma_continua = (long long)raiz->valor + (soma_esq > soma_dir ? soma_esq : soma_dir);

    return soma_continua > 0 ? soma_continua : 0;
}

long long somaMaxCaminho(No* raiz) {
    soma_max_global = LLONG_MIN;

    somaMaxCaminhoUtil(raiz);

    if (soma_max_global == LLONG_MIN)
        return 0;

    return soma_max_global;
}

void liberarArvore(No* raiz) {
    if (raiz == NULL) return;
    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);
    free(raiz);
}

int main() {
    int n;

    if (scanf("%d", &n) != 1)
        return 1;

    if (n <= 0) {
        printf("0\n");
        return 0;
    }

    int *in = (int*)malloc(n * sizeof(int));
    int *pos = (int*)malloc(n * sizeof(int));

    if (in == NULL || pos == NULL)
        return 1;

    for (int i = 0; i < n; i++)
        if (scanf("%d", &in[i]) != 1)
            return 1;

    for (int i = 0; i < n; i++)
        if (scanf("%d", &pos[i]) != 1)
            return 1;

    int indice_pos = n - 1;
    No* raiz = montarArvore(in, pos, 0, n - 1, &indice_pos);

    long long resultado = somaMaxCaminho(raiz);

    printf("%lld\n", resultado);

    liberarArvore(raiz);
    free(in);
    free(pos);

    return 0;
}
