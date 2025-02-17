#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    int valor;
    int altura;
    struct No *esquerda;
    struct No *direita;
    struct No *pai;
} No;

No* buscarNo(No *raiz, int valor) {
    while (raiz != NULL) {
        if (valor < raiz->valor)
            raiz = raiz->esquerda;
        else if (valor > raiz->valor)
            raiz = raiz->direita;
        else
            return raiz;
    }
    return NULL;
}

void inserirNo(No **raiz, int valor) {
    No *novo = (No*) malloc(sizeof(No));
    novo->valor = valor;
    novo->esquerda = novo->direita = novo->pai = NULL;
    novo->altura = 0;
    
    if (*raiz == NULL) {
        *raiz = novo;
        return;
    }

    No *atual = *raiz, *pai = NULL;
    int altura = 0;

    while (atual != NULL) {
        pai = atual;
        if (valor < atual->valor)
            atual = atual->esquerda;
        else
            atual = atual->direita;
        altura++;
    }

    novo->pai = pai;
    novo->altura = altura;
    if (valor < pai->valor)
        pai->esquerda = novo;
    else
        pai->direita = novo;
}

No* encontrarSucessor(No *no) {
    No *atual = no->direita;
    while (atual->esquerda != NULL)
        atual = atual->esquerda;
    return atual;
}

void removerNo(No **raiz, int valor) {
    No *no = buscarNo(*raiz, valor);
    if (no == NULL) return;
    
    if (no->esquerda == NULL && no->direita == NULL) { // Caso folha
        if (no->pai == NULL)
            *raiz = NULL;
        else if (no->pai->esquerda == no)
            no->pai->esquerda = NULL;
        else
            no->pai->direita = NULL;
        free(no);
    } else if (no->esquerda == NULL || no->direita == NULL) { // Apenas um filho
        No *filho = (no->esquerda != NULL) ? no->esquerda : no->direita;
        if (no->pai == NULL)
            *raiz = filho;
        else if (no->pai->esquerda == no)
            no->pai->esquerda = filho;
        else
            no->pai->direita = filho;
        filho->pai = no->pai;
        free(no);
    } else {
        No *sucessor = encontrarSucessor(no);
        no->valor = sucessor->valor;
        removerNo(&(sucessor), sucessor->valor);
    }
}

void escreverEmOrdem(No *raiz, FILE *fp) {
    if (raiz) {
        escreverEmOrdem(raiz->esquerda, fp);
        fprintf(fp, "%d (%d) ", raiz->valor, raiz->altura);
        escreverEmOrdem(raiz->direita, fp);
    }
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
    FILE *entrada = abrirArquivoEntrada("L2Q3.in");
    FILE *saida = abrirArquivoSaida("L2Q3.out");
    char linha[1000];

    if (!entrada || !saida) return EXIT_FAILURE;

    while (fgets(linha, sizeof(linha), entrada)) {
        No *raiz = NULL;
        char *token = strtok(linha, " ");
        
        while (token) {
            if (token[0] == 'a') {
                token = strtok(NULL, " ");
                inserirNo(&raiz, atoi(token));
            } else if (token[0] == 'r') {
                token = strtok(NULL, " ");
                removerNo(&raiz, atoi(token));
            }
            token = strtok(NULL, " ");
        }
        
        escreverEmOrdem(raiz, saida);
        fprintf(saida, "\n");
    }

    fclose(entrada);
    fclose(saida);
    return 0;
}
