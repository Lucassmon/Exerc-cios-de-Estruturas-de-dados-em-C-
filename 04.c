#include <stdio.h>
#include <stdlib.h>

typedef struct Elemento {
    int valor;
    int linha;
    int coluna;
    struct Elemento* prox_coluna;
    struct Elemento* prox_linha;
} Elemento;

typedef struct MatrizEsparsa {
    int n;
    Elemento* cabecalho;
    Elemento** cabecalhos_linha;
    Elemento** cabecalhos_coluna;
} MatrizEsparsa;

Elemento* cria_elemento(int valor, int linha, int coluna) {
    Elemento* elemento = (Elemento*)malloc(sizeof(Elemento));
    if (elemento != NULL) {
        elemento->valor = valor;
        elemento->linha = linha;
        elemento->coluna = coluna;
        elemento->prox_coluna = NULL;
        elemento->prox_linha = NULL;
    }
    return elemento;
}

void inicializa_matriz_esparsa(MatrizEsparsa* matriz, int tamanho) {
    matriz->n = tamanho;
    matriz->cabecalho = cria_elemento(tamanho, -1, -1);

    matriz->cabecalhos_linha = (Elemento**)malloc(tamanho * sizeof(Elemento*));
    matriz->cabecalhos_coluna = (Elemento**)malloc(tamanho * sizeof(Elemento*));

    for (int i = 0; i < tamanho; i++) {
        matriz->cabecalhos_linha[i] = cria_elemento(0, i, -1);
    }

    for (int i = 0; i < tamanho; i++) {
        matriz->cabecalhos_coluna[i] = cria_elemento(0, -1, i);
    }
}

Elemento* obtem_elemento(MatrizEsparsa* matriz, int linha, int coluna) {
    if (linha < 0 || linha >= matriz->n || coluna < 0 || coluna >= matriz->n) {
        return NULL;
    }

    Elemento* cabecalho_linha = matriz->cabecalhos_linha[linha];
    Elemento* atual = cabecalho_linha->prox_coluna;

    while (atual != NULL && atual->coluna < coluna) {
        atual = atual->prox_coluna;
    }
    if (atual != NULL && atual->coluna == coluna) {
        return atual;
    }
    return NULL;
}

void remove_elemento(MatrizEsparsa* matriz, int linha, int coluna) {
    Elemento* cabecalho_linha = matriz->cabecalhos_linha[linha];
    Elemento* prev_linha = cabecalho_linha;
    Elemento* atual_linha = cabecalho_linha->prox_coluna;
    while (atual_linha != NULL && atual_linha->coluna < coluna) {
        prev_linha = atual_linha;
        atual_linha = atual_linha->prox_coluna;
    }
    if (atual_linha != NULL && atual_linha->coluna == coluna) {
        prev_linha->prox_coluna = atual_linha->prox_coluna;
    }

    Elemento* cabecalho_coluna = matriz->cabecalhos_coluna[coluna];
    Elemento* prev_coluna = cabecalho_coluna;
    Elemento* atual_coluna = cabecalho_coluna->prox_linha;
    while (atual_coluna != NULL && atual_coluna->linha < linha) {
        prev_coluna = atual_coluna;
        atual_coluna = atual_coluna->prox_linha;
    }
    Elemento* elemento_a_remover = NULL;
    if (atual_linha != NULL && atual_linha->coluna == coluna) {
        prev_linha->prox_coluna = atual_linha->prox_coluna;
        elemento_a_remover = atual_linha;
    }

    if (atual_coluna != NULL && atual_coluna->linha == linha) {
        prev_coluna->prox_linha = atual_coluna->prox_linha;
        // Se o elemento foi encontrado e removido na lista de linhas, ele é o mesmo
        // então não precisamos liberá-lo novamente.
        if (elemento_a_remover == NULL) {
            elemento_a_remover = atual_coluna;
        }
    }

    if (elemento_a_remover != NULL) {
        free(elemento_a_remover);
    }
}

void insere_elemento(MatrizEsparsa* matriz, int valor, int linha, int coluna) {
    if (valor == 0) return;

    Elemento* existente = obtem_elemento(matriz, linha, coluna);
    if (existente != NULL) {
        existente->valor += valor;
        if (existente->valor == 0) {
            remove_elemento(matriz, linha, coluna);
        }
        return;
    }

    Elemento* novo_elemento = cria_elemento(valor, linha, coluna);

    Elemento* cabecalho_linha = matriz->cabecalhos_linha[linha];
    Elemento* atual_linha = cabecalho_linha;
    while (atual_linha->prox_coluna != NULL && atual_linha->prox_coluna->coluna < coluna) {
        atual_linha = atual_linha->prox_coluna;
    }
    novo_elemento->prox_coluna = atual_linha->prox_coluna;
    atual_linha->prox_coluna = novo_elemento;

    Elemento* cabecalho_coluna = matriz->cabecalhos_coluna[coluna];
    Elemento* atual_coluna = cabecalho_coluna;
    while (atual_coluna->prox_linha != NULL && atual_coluna->prox_linha->linha < linha) {
        atual_coluna = atual_coluna->prox_linha;
    }
    novo_elemento->prox_linha = atual_coluna->prox_linha;
    atual_coluna->prox_linha = novo_elemento;
}

MatrizEsparsa* multiplica_matrizes(MatrizEsparsa* A, MatrizEsparsa* B) {
    if (A->n != B->n) {
        return NULL;
    }

    MatrizEsparsa* C = (MatrizEsparsa*)malloc(sizeof(MatrizEsparsa));
    inicializa_matriz_esparsa(C, A->n);

    for (int i = 0; i < A->n; i++) {
        Elemento* el_A = A->cabecalhos_linha[i]->prox_coluna;

        while (el_A != NULL) {
            int k = el_A->coluna;
            int val_A = el_A->valor;

            Elemento* el_B = B->cabecalhos_linha[k]->prox_coluna;

            while (el_B != NULL) {
                int j = el_B->coluna;
                int val_B = el_B->valor;

                int produto_parcial = val_A * val_B;
                insere_elemento(C, produto_parcial, i, j);
                el_B = el_B->prox_coluna;
            }
            el_A = el_A->prox_coluna;
        }
    }

    return C;
}

void imprime_matriz_densa(MatrizEsparsa* matriz) {
    for (int i = 0; i < matriz->n; i++) {
        Elemento* elemento_na_linha = matriz->cabecalhos_linha[i]->prox_coluna;
        for (int j = 0; j < matriz->n; j++) {
            if (elemento_na_linha != NULL && elemento_na_linha->coluna == j) {
                printf("%d", elemento_na_linha->valor);
                elemento_na_linha = elemento_na_linha->prox_coluna;
            } else {
                printf("*");
            }
            if (j < matriz->n - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void libera_matriz(MatrizEsparsa* matriz) {
    if (matriz == NULL) return;

    for (int i = 0; i < matriz->n; i++) {
        Elemento* atual_elemento = matriz->cabecalhos_linha[i];
        while (atual_elemento != NULL) {
            Elemento* proximo_elemento = atual_elemento->prox_coluna;
            free(atual_elemento);
            atual_elemento = proximo_elemento;
        }
    }


    for (int i = 0; i < matriz->n; i++) {
        Elemento* atual_cabecalho_coluna = matriz->cabecalhos_coluna[i];
        free(atual_cabecalho_coluna);
    }

    free(matriz->cabecalhos_linha);
    free(matriz->cabecalhos_coluna);
    free(matriz->cabecalho);
    free(matriz);
}

int main(){
    int n; 
    scanf("%d", &n);

    MatrizEsparsa* A = (MatrizEsparsa*)malloc(sizeof(MatrizEsparsa));
    inicializa_matriz_esparsa(A, n);

    int k_A;
    scanf("%d", &k_A);
    for (int i = 0; i < k_A; i++) {
        int linha, coluna, valor;
        scanf("%d %d %d", &linha, &coluna, &valor);
        insere_elemento(A, valor, linha - 1, coluna - 1);
    }

    MatrizEsparsa* B = (MatrizEsparsa*)malloc(sizeof(MatrizEsparsa));
    inicializa_matriz_esparsa(B, n);

    int k_B;
    scanf("%d", &k_B);
    for (int i = 0; i < k_B; i++) {
        int linha, coluna, valor;
        scanf("%d %d %d", &linha, &coluna, &valor);
        insere_elemento(B, valor, linha - 1, coluna - 1);
    }

    MatrizEsparsa* C = multiplica_matrizes(A, B);

    if (C != NULL) {
        imprime_matriz_densa(C);
        libera_matriz(A);
        libera_matriz(B);
        libera_matriz(C);
    }

    return 0;
}