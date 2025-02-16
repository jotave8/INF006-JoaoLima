//ALuno: João Victor OLiveira de Lima (20241160026)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    int valor;
    int indice;
    struct No *esq, *dir;
} No;

No* novoNo(int valor, int indice) {
    No* no = (No*)malloc(sizeof(No));
    no->valor = valor;
    no->indice = indice;
    no->esq = no->dir = NULL;
    return no;
}

int inserir(No** raiz, int valor, int indice) {
    No* novo = novoNo(valor, indice);
    if (*raiz == NULL) {
        *raiz = novo;
        return 0;
    }

    No* atual = *raiz;
    int altura = 0;

    while (1) {
        if (valor < atual->valor || (valor == atual->valor && indice < atual->indice)) {
            if (atual->esq == NULL) {
                atual->esq = novo;
                return altura + 1;
            }
            atual = atual->esq;
        } else {
            if (atual->dir == NULL) {
                atual->dir = novo;
                return altura + 1;
            }
            atual = atual->dir;
        }
        altura++;
    }
}

No* maximo(No* raiz) {
    if (raiz == NULL) return NULL;
    while (raiz->dir != NULL) {
        raiz = raiz->dir;
    }
    return raiz;
}

int alturaMaxima(No* raiz) {
    int altura = -1;
    while (raiz != NULL) {
        altura++;
        raiz = raiz->dir;
    }
    return altura;
}

No* predecessor(No* raiz, int valor, int indice, No* pred) {
    if (raiz == NULL) return pred;
    if (valor > raiz->valor || (valor == raiz->valor && indice > raiz->indice)) {
        return predecessor(raiz->dir, valor, indice, raiz);
    } else {
        return predecessor(raiz->esq, valor, indice, pred);
    }
}

void liberarArvore(No* raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esq);
        liberarArvore(raiz->dir);
        free(raiz);
    }
}

FILE* abrirArquivoEntrada(char *nomeArquivo) {
    FILE *fp = fopen(nomeArquivo, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo de entrada: %s\n", nomeArquivo);
        exit(EXIT_FAILURE);
    }
    return fp;
}

FILE* abrirArquivoSaida(char *nomeArquivo) {
    FILE *fp = fopen(nomeArquivo, "w");
    if (fp == NULL) {
        printf("Erro ao criar o arquivo de saída: %s\n", nomeArquivo);
        exit(EXIT_FAILURE);
    }
    return fp;
}

void processarArquivo(FILE *entrada, FILE *saida) {
    char linha[1024];
    while (fgets(linha, sizeof(linha), entrada)) {
        No* raiz = NULL;
        int numero;
        char *ptr = linha;
        int indice = 1;

        while (sscanf(ptr, "%d", &numero) == 1) {
            int altura = inserir(&raiz, numero, indice);
            fprintf(saida, "%d ", altura);
            ptr = strchr(ptr, ' ');
            if (!ptr) break;
            ptr++;
            indice++;
        }

        No* maxNo = maximo(raiz);
        int hMax = alturaMaxima(raiz);
        No* predNo = NULL;
        
        if (maxNo != NULL) {
            predNo = predecessor(raiz, maxNo->valor, maxNo->indice, NULL);
        }

        if (maxNo != NULL) {
            fprintf(saida, "max %d alt %d pred ", maxNo->valor, hMax);
        }

        if (predNo != NULL) {
            fprintf(saida, "%d", predNo->valor);
        } else {
            fprintf(saida, "NaN");
        }
        fprintf(saida, "\n");

        liberarArvore(raiz);
    }
}

int main() {
    FILE *entrada = abrirArquivoEntrada("L2Q1.in");
    FILE *saida = abrirArquivoSaida("L2Q1.out");

    processarArquivo(entrada, saida);

    fclose(entrada);
    fclose(saida);

    printf("Arquivo de saída gerado: L2Q1.out\n");
    return EXIT_SUCCESS;
}
