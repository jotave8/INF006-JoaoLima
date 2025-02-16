#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct No {
    int valor;
    struct No *esq, *dir;
} No;
// Função para criar um novo nó
No* criarNo(int valor) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo) {
        novo->valor = valor;
        novo->esq = novo->dir = NULL;
    }
    return novo;
}
// Função para inserir um valor na árvore binária de busca (sem duplicatas)
No* inserir(No* raiz, int valor) {
    if (raiz == NULL) return criarNo(valor);
    if (valor < raiz->valor)
        raiz->esq = inserir(raiz->esq, valor);
    else if (valor > raiz->valor)
        raiz->dir = inserir(raiz->dir, valor);
    return raiz;
}
// Função para encontrar o menor nó na subárvore (para remoção)
No* encontrarMenor(No* raiz) {
    while (raiz->esq != NULL) raiz = raiz->esq;
    return raiz;
}
// Função para remover um valor da árvore
No* remover(No* raiz, int valor, int* sucesso) {
    if (raiz == NULL) {
        *sucesso = 0; // O nó não existia
        return NULL;
    }
    if (valor < raiz->valor)
        raiz->esq = remover(raiz->esq, valor, sucesso);
    else if (valor > raiz->valor)
        raiz->dir = remover(raiz->dir, valor, sucesso);
    else {
        *sucesso = 1; // Nó encontrado e será removido
        if (raiz->esq == NULL) {
            No* temp = raiz->dir;
            free(raiz);
            return temp;
        }
        if (raiz->dir == NULL) {
            No* temp = raiz->esq;
            free(raiz);
            return temp;
        }
        No* temp = encontrarMenor(raiz->dir);
        raiz->valor = temp->valor;
        raiz->dir = remover(raiz->dir, temp->valor, sucesso);
    }
    return raiz;
}
// Função para calcular a altura de um nó
int altura(No* raiz) {
    if (raiz == NULL) return -1;
    int altEsq = altura(raiz->esq);
    int altDir = altura(raiz->dir);
    return (altEsq > altDir ? altEsq : altDir) + 1;
}
// Função para imprimir os nós em ordem com suas alturas
void imprimirEmOrdem(No* raiz, FILE* saida) {
    if (raiz == NULL) return;
    imprimirEmOrdem(raiz->esq, saida);
    fprintf(saida, "%d (%d) ", raiz->valor, altura(raiz));
    imprimirEmOrdem(raiz->dir, saida);
}
// Função para abrir arquivo de entrada
FILE* abrirArquivoEntrada(char *nomeArquivo) {
    FILE *fp = fopen(nomeArquivo, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo de entrada: %s\n", nomeArquivo);
        return NULL;
    }
    return fp;
}
// Função para abrir arquivo de saída
FILE* abrirArquivoSaida(char *nomeArquivo) {
    FILE *fp = fopen(nomeArquivo, "w");
    if (fp == NULL) {
        printf("Erro ao criar o arquivo de saída: %s\n", nomeArquivo);
        return NULL;
    }
    return fp;
}
// Função principal
int main() {
    FILE *entrada = abrirArquivoEntrada("L2Q3.in");
    if (entrada == NULL) return EXIT_FAILURE;
    FILE *saida = abrirArquivoSaida("L2Q3.out");
    if (saida == NULL) {
        fclose(entrada);
        return EXIT_FAILURE;
    }
    No* raiz = NULL;
    char operacao;
    int valor;
    char linha[1024];
    // Lendo cada linha do arquivo
    while (fgets(linha, sizeof(linha), entrada)) {
        char *ptr = linha;
        while (sscanf(ptr, " %c %d", &operacao, &valor) == 2) {
            if (operacao == 'a') {
                raiz = inserir(raiz, valor);
            } else if (operacao == 'r') {
                int sucesso = 0;
                raiz = remover(raiz, valor, &sucesso);
                if (!sucesso) raiz = inserir(raiz, valor); // Se não existia, adiciona
            }
            ptr = strchr(ptr, ' ');
            if (!ptr) break;
            ptr++;
        }
        if (raiz != NULL) {
            imprimirEmOrdem(raiz, saida);
            fprintf(saida, "\n");
        }
        // Liberar a árvore para a próxima linha
        free(raiz);
        raiz = NULL;
    }
    fclose(entrada);
    fclose(saida);
    printf("Arquivo de saída gerado: L2Q3.out\n");
    return EXIT_SUCCESS;
}