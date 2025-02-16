//ALuno: João Victor OLiveira de Lima (20241160026)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{
    int valor;
    struct No *esq, *dir;
} No;

No* criarNo(int valor) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo){
        novo->valor = valor;
        novo->esq = novo->dir = NULL;
    }
    return novo;
}

No* inserir(No* raiz, int valor){
    if (raiz == NULL){
        return criarNo(valor);
    }
    if (valor < raiz->valor){
        raiz->esq = inserir(raiz->esq, valor);
    }else if (valor > raiz->valor){
        raiz->dir = inserir(raiz->dir, valor);
    }
    return raiz;
}


int somaNos(No* raiz){
    if (raiz == NULL){
        return 0;
    } 
    return raiz->valor + somaNos(raiz->esq) + somaNos(raiz->dir);
}

void imprimirBalanceamento(No* raiz, FILE* saida){
    if (raiz == NULL){
        return;
    }

    imprimirBalanceamento(raiz->esq, saida);
    int somaDir = somaNos(raiz->dir);
    int somaEsq = somaNos(raiz->esq);
    int balanceamento = somaDir - somaEsq;
    fprintf(saida, "%d (%d) ", raiz->valor, balanceamento);
    imprimirBalanceamento(raiz->dir, saida);
}

FILE* abrirArquivoEntrada(char *nomeArquivo) {
    FILE *fp = fopen(nomeArquivo, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo de entrada: %s\n", nomeArquivo);
        return NULL;
    }
    return fp;
}

FILE* abrirArquivoSaida(char *nomeArquivo) {
    FILE *fp = fopen(nomeArquivo, "w");
    if (fp == NULL) {
        printf("Erro ao criar o arquivo de saída: %s\n", nomeArquivo);
        return NULL;
    }
    return fp;
}

int main() {
    FILE *entrada = abrirArquivoEntrada("L2Q2.in");
    if (entrada == NULL) return EXIT_FAILURE;

    FILE *saida = abrirArquivoSaida("L2Q2.out");
    if (saida == NULL) {
        fclose(entrada);
        return EXIT_FAILURE;
    }
    No* raiz = NULL;
    char linha[1024];

    while (fgets(linha, sizeof(linha), entrada)) {
        int valor;
        char *ptr = linha;

        while (sscanf(ptr, "%d", &valor) == 1) {
            raiz = inserir(raiz, valor);
            ptr = strchr(ptr, ' ');
            if (!ptr) break;
            ptr++;
        }
        if (raiz != NULL) {
            imprimirBalanceamento(raiz, saida);
            fprintf(saida, "\n");
        }
        free(raiz);
        raiz = NULL;
    }

    fclose(entrada);
    fclose(saida);
    printf("Arquivo de saída gerado: L2Q2.out\n");
    return EXIT_SUCCESS;
}
