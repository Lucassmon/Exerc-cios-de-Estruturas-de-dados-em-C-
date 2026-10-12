#include <stdio.h>

int tonari(int M, int vida[M][M], int linha, int coluna){
    int soma = 0;
    int checaLinha,checaColuna;
    int di[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dj[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int d = 0; d < 8; d++) {
        checaLinha = linha+di[d];
        checaColuna = coluna+dj[d];
        if (checaColuna >= 0 && checaLinha >= 0 && checaColuna < M && checaLinha < M)
            soma += vida[checaLinha][checaColuna];
    }
    return soma;
    }

int main(){
    int M,K;
    scanf("%d", &M);
    scanf("%d", &K);
    int i,j,Tmim,Tmax,somaT,soma=0;
    scanf("%d", &Tmim);
    scanf("%d", &Tmax);
    int matriz[M][M], copia[M][M], vida[M][M], copiaV[M][M];
//cria a matriz de tempeteraturas

    for (i = 0; i < M; i++)
        for (j = 0; j < M; j++) {
            //printf("Matriz[%d][%d]: ", i, j);
            scanf("%d", &matriz[i][j]);
        }
//cria a matriz de vidas    
     for (i = 0; i < M; i++)
        for (j = 0; j < M; j++) {
            //printf("vida[%d][%d]: ", i, j);
            scanf("%d", &vida[i][j]);
        }   

for (int L=0;L<K;L++){
//copia a matriz da temperatura
    for (i = 0; i < M; i++)
        for (j = 0; j < M; j++)
            copia[i][j] = matriz[i][j];


//soma a temperadura e faz a media
    for (i = 1; i < M-1; i++)
        for (j = 1; j < M-1; j++){
            somaT = matriz[i][j-1]+matriz[i-1][j]+matriz[i+1][j]+matriz[i][j+1];
            copia[i][j] = somaT/4;
        }
//atualiza a matriz original
    for (i = 0; i < M; i++)
        for (j = 0; j < M; j++)
            matriz[i][j] = copia[i][j];

//copia a matriz da vida
    for (i = 0; i < M; i++)
        for (j = 0; j < M; j++)
            copiaV[i][j] = vida[i][j];
//morte termica.
    for (i = 0; i < M; i++)
        for (j = 0; j < M; j++){
            if( matriz[i][j] < Tmim || matriz[i][j] > Tmax)
                copiaV[i][j]=0;
        }
//morte muita gente
for (i = 0; i < M; i++)
    for (j = 0; j < M; j++){
        int vizinhos = tonari(M,copiaV,i,j);   // <- salva o resultado
        if (vizinhos < 2 || vizinhos > 3)
            vida[i][j] = 0;
        else if (vizinhos == 3)
            vida[i][j] = 1;
         else // vizinhos == 2
            vida[i][j] = copiaV[i][j];
    }     
//faz vida = copiaV
    for (i = 0; i < M; i++)
        for (j = 0; j < M; j++)
            copiaV[i][j] = vida[i][j];

}

// prints do final do codigo   
     for (i = 0; i < M; i++) {
        for (j = 0; j < M; j++)
            printf("%d ", matriz[i][j]);
        printf("\n");
     }
     printf("\n");
    for (i = 0; i < M; i++) {
        for (j = 0; j < M; j++)
            printf("%d ", vida[i][j]);
        printf("\n");
        }
     
return 0;
}