#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    double valor;
    double derivada;
} Par;

typedef struct Node {
    Par dado;
    struct Node* prox;
} Node;

typedef struct {
    Node* topo;
} Pilha;

// ---------- Funções da Pilha ----------
Pilha* criaPilha() {
    Pilha* p = (Pilha*) malloc(sizeof(Pilha));
    p->topo = NULL;
    return p;
}

int pilhaVazia(Pilha* p) {
    return (p->topo == NULL);
}

void empilha(Pilha* p, Par valor) {
    Node* novo = (Node*) malloc(sizeof(Node));
    novo->dado = valor;
    novo->prox = p->topo;
    p->topo = novo;
}

Par desempilha(Pilha* p) {
    if (pilhaVazia(p)) {
        exit(1);
    }
    Node* temp = p->topo;
    Par valor = temp->dado;
    p->topo = temp->prox;
    free(temp);
    return valor;
}

void destroiPilha(Pilha* p) {
    while (!pilhaVazia(p)) {
        desempilha(p);
    }
    free(p);
}


int ehOperador(char* token) {
    return (strcmp(token, "+") == 0 ||
            strcmp(token, "-") == 0 ||
            strcmp(token, "*") == 0 ||
            strcmp(token, "/") == 0 ||
            strcmp(token, "^") == 0);
}

int ehVariavel(char* token) {
    return (strcmp(token, "x") == 0);
}

int ehNumero(char* token) {
    if (ehOperador(token) || ehVariavel(token)) return 0;
    char* endptr;
    strtod(token, &endptr);
    return (*endptr == '\0');
}

void processaOperador(Pilha* p, char* op) {
    Par b = desempilha(p);
    Par a = desempilha(p);
    Par res;

    if (strcmp(op, "+") == 0) {
        res.valor = a.valor + b.valor;
        res.derivada = a.derivada + b.derivada;
    } else if (strcmp(op, "-") == 0) {
        res.valor = a.valor - b.valor;
        res.derivada = a.derivada - b.derivada;
    } else if (strcmp(op, "*") == 0) {
        res.valor = a.valor * b.valor;
        res.derivada = a.derivada * b.valor + a.valor * b.derivada;
    } else if (strcmp(op, "/") == 0) {
        res.valor = a.valor / b.valor;
        res.derivada = (a.derivada * b.valor - a.valor * b.derivada) / (b.valor * b.valor);
    } else if (strcmp(op, "^") == 0) {
        // Expoente é constante
        res.valor = pow(a.valor, b.valor);
        res.derivada = b.valor * pow(a.valor, b.valor - 1) * a.derivada;
    } else {
        exit(1);
    }

    empilha(p, res);
}

int main() {
    char expressao[256];
    double x0;

    // Lê a linha da expressão completa
    if (!fgets(expressao, sizeof(expressao), stdin)) {
        return 1;
    }

    // Lê o valor de x0
    if (scanf("%lf", &x0) != 1) {
        return 1;
    }

    Pilha* p = criaPilha();

    char* token = strtok(expressao, " \n");
    while (token != NULL) {
        Par novo;
        if (ehNumero(token)) {
            novo.valor = atof(token);
            novo.derivada = 0.0;
            empilha(p, novo);
        } else if (ehVariavel(token)) {
            novo.valor = x0;
            novo.derivada = 1.0;
            empilha(p, novo);
        } else if (ehOperador(token)) {
            processaOperador(p, token);
        } else {
            destroiPilha(p);
            return 1;
        }
        token = strtok(NULL, " \n");
    }

    if (pilhaVazia(p)) {
        destroiPilha(p);
        return 1;
    }

    Par resultado = desempilha(p);
    if (!pilhaVazia(p)) {
        destroiPilha(p);
        return 1;
    }

    printf("%.5lf\n%.5lf\n", resultado.valor, resultado.derivada);

    destroiPilha(p);
    return 0;
}
