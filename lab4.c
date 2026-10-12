#include <stdio.h>
#include <stdlib.h>

typedef struct Elemento {
    int valor;
    int linha;
    int coluna;
    struct Elemento* prox_coluna;
    struct Elemento* prox_linha;
} Elemento;

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

Elemento* cria_cabeçalho(int tamanho) {
    Elemento* cabeça = cria_elemento(0, -1, -1);

    Elemento* atual = cabeça;
    Elemento* proximo = NULL;

    for (int i=0; i<tamanho;i++){
        proximo = cria_elemento(0,-1,i);
        atual->prox_coluna =  proximo;
        atual=proximo;
    }

    atual = cabeça;

    for (int i=0; i<tamanho;i++){
        proximo = cria_elemento(0,i,-1);
        atual->prox_linha =  proximo;
        atual=proximo;
    }
    return cabeça;
}



void insere(Elemento* cabeça, Elemento* temp){ 
    Elemento* atual = cabeça;

    for(int i =-1; i<temp->coluna;i++){

        if(i==temp->coluna){
            if(atual->prox_linha != NULL){
                if(temp->linha < atual->prox_linha->linha){
                    temp->prox_linha = atual->prox_linha;
                    atual->prox_linha = temp;
                }
                atual->prox_linha->prox_linha = temp;
            }
            atual->prox_linha = temp;
        }

        atual = atual->prox_coluna;
            
    }
}

int main(){
    int n,k,i,j,v; 
    scanf("%d", &n);
    scanf("%d", &k);
    Elemento* matriz = cria_elemento(0,n,n);
    for (int c=0;c<k;c++){
        scanf("%d" "%d" "%d",&i,&j,&v);
        Elemento* temp=cria_elemento(v,i,j);

    }
    return 0;
}

// L = liberdade
// G = guns 
// B = Bolsonaro
// T = Trump

